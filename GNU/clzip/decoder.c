/*  Clzip - Data compressor based on the LZMA algorithm
    Copyright (C) 2010, 2011 Antonio Diaz Diaz.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _FILE_OFFSET_BITS 64

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "clzip.h"
#include "decoder.h"


CRC32 crc32;


/* Returns the number of bytes really read.
   If (returned value < size) and (errno == 0), means EOF was reached.
*/
int readblock( const int fd, uint8_t * const buf, const int size )
  {
  int rest = size;
  while( true )
    {
    int n;
    errno = 0;
    if( rest <= 0 ) break;
    n = read( fd, buf + size - rest, rest );
    if( n > 0 ) rest -= n;
    else if( n == 0 ) break;
    else if( errno != EINTR && errno != EAGAIN ) break;
    }
  return ( rest > 0 ) ? size - rest : size;
  }


/* Returns the number of bytes really written.
   If (returned value < size), it is always an error.
*/
int writeblock( const int fd, const uint8_t * const buf, const int size )
  {
  int rest = size;
  while( true )
    {
    int n;
    errno = 0;
    if( rest <= 0 ) break;
    n = write( fd, buf + size - rest, rest );
    if( n > 0 ) rest -= n;
    else if( errno && errno != EINTR && errno != EAGAIN ) break;
    }
  return ( rest > 0 ) ? size - rest : size;
  }


bool Rd_read_block( struct Range_decoder * const rdec )
  {
  if( !rdec->at_stream_end )
    {
    rdec->stream_pos = readblock( rdec->infd, rdec->buffer, rd_buffer_size );
    if( rdec->stream_pos != rd_buffer_size && errno )
      { show_error( "Read error", errno, false ); cleanup_and_fail( 1 ); }
    rdec->at_stream_end = ( rdec->stream_pos < rd_buffer_size );
    rdec->partial_member_pos += rdec->pos;
    rdec->pos = 0;
    }
  return rdec->pos < rdec->stream_pos;
  }


void LZd_flush_data( struct LZ_decoder * const decoder )
  {
  const int size = decoder->pos - decoder->stream_pos;
  if( size > 0 )
    {
    CRC32_update_buf( &decoder->crc_, decoder->buffer + decoder->stream_pos, size );
    if( decoder->outfd >= 0 &&
        writeblock( decoder->outfd, decoder->buffer + decoder->stream_pos, size ) != size )
      { show_error( "Write error", errno, false ); cleanup_and_fail( 1 ); }
    if( decoder->pos >= decoder->buffer_size )
      { decoder->partial_data_pos += decoder->pos; decoder->pos = 0; }
    decoder->stream_pos = decoder->pos;
    }
  }


bool LZd_verify_trailer( struct LZ_decoder * const decoder,
                         struct Pretty_print * const pp )
  {
  int i;
  File_trailer trailer;
  const int trailer_size = Ft_versioned_size( decoder->member_version );
  const long long member_size =
    Rd_member_position( decoder->range_decoder ) + trailer_size;
  bool error = false;

  for( i = 0; i < trailer_size && !error; ++i )
    {
    if( !Rd_finished( decoder->range_decoder ) )
      trailer[i] = Rd_get_byte( decoder->range_decoder );
    else
      {
      error = true;
      if( pp->verbosity >= 0 )
        {
        Pp_show_msg( pp, 0 );
        fprintf( stderr, "Trailer truncated at trailer position %d;"
                         " some checks may fail.\n", i );
        }
      for( ; i < trailer_size; ++i ) trailer[i] = 0;
      }
    }
  if( decoder->member_version == 0 ) Ft_set_member_size( trailer, member_size );
  if( !Rd_code_is_zero( decoder->range_decoder ) )
    {
    error = true;
    Pp_show_msg( pp, "Range decoder final code is not zero" );
    }
  if( Ft_get_data_crc( trailer ) != LZd_crc( decoder ) )
    {
    error = true;
    if( pp->verbosity >= 0 )
      {
      Pp_show_msg( pp, 0 );
      fprintf( stderr, "CRC mismatch; trailer says %08X, data CRC is %08X.\n",
               (unsigned int)Ft_get_data_crc( trailer ),
               (unsigned int)LZd_crc( decoder ) );
      }
    }
  if( Ft_get_data_size( trailer ) != LZd_data_position( decoder ) )
    {
    error = true;
    if( pp->verbosity >= 0 )
      {
      Pp_show_msg( pp, 0 );
      fprintf( stderr, "Data size mismatch; trailer says %lld, data size is %lld (0x%llX).\n",
               Ft_get_data_size( trailer ), LZd_data_position( decoder ), LZd_data_position( decoder ) );
      }
    }
  if( Ft_get_member_size( trailer ) != member_size )
    {
    error = true;
    if( pp->verbosity >= 0 )
      {
      Pp_show_msg( pp, 0 );
      fprintf( stderr, "Member size mismatch; trailer says %lld, member size is %lld (0x%llX).\n",
               Ft_get_member_size( trailer ), member_size, member_size );
      }
    }
  if( !error && pp->verbosity >= 3 && LZd_data_position( decoder ) > 0 && member_size > 0 )
    fprintf( stderr, "%6.3f:1, %6.3f bits/byte, %5.2f%% saved.  ",
             (double)LZd_data_position( decoder ) / member_size,
             ( 8.0 * member_size ) / LZd_data_position( decoder ),
             100.0 * ( 1.0 - ( (double)member_size / LZd_data_position( decoder ) ) ) );
  if( !error && pp->verbosity >= 4 )
    fprintf( stderr, "data CRC %08X, data size %9lld, member size %8lld.  ",
             (unsigned int)Ft_get_data_crc( trailer ),
             Ft_get_data_size( trailer ), Ft_get_member_size( trailer ) );
  return !error;
  }


/* Return value: 0 = OK, 1 = decoder error, 2 = unexpected EOF,
                 3 = trailer error, 4 = unknown marker found. */
int LZd_decode_member( struct LZ_decoder * const decoder,
                       struct Pretty_print * const pp )
  {
  unsigned int rep0 = 0;	/* rep[0-3] latest four distances */
  unsigned int rep1 = 0;	/* used for efficient coding of */
  unsigned int rep2 = 0;	/* repeated distances */
  unsigned int rep3 = 0;
  State state = 0;
  Rd_load( decoder->range_decoder );

  while( true )
    {
    const int pos_state = LZd_data_position( decoder ) & pos_state_mask;
    if( Rd_finished( decoder->range_decoder ) )
      { LZd_flush_data( decoder ); return 2; }
    if( Rd_decode_bit( decoder->range_decoder, &decoder->bm_match[state][pos_state] ) == 0 )
      {
      const uint8_t prev_byte = LZd_get_prev_byte( decoder );
      if( St_is_char( state ) )
        LZd_put_byte( decoder, Lid_decode( &decoder->literal_decoder,
          decoder->range_decoder, prev_byte ) );
      else
        LZd_put_byte( decoder, Lid_decode_matched( &decoder->literal_decoder,
          decoder->range_decoder, prev_byte, LZd_get_byte( decoder, rep0 ) ) );
      St_set_char( &state );
      }
    else
      {
      int len;
      if( Rd_decode_bit( decoder->range_decoder, &decoder->bm_rep[state] ) == 1 )
        {
        len = 0;
        if( Rd_decode_bit( decoder->range_decoder, &decoder->bm_rep0[state] ) == 1 )
          {
          unsigned int distance;
          if( Rd_decode_bit( decoder->range_decoder, &decoder->bm_rep1[state] ) == 0 )
            distance = rep1;
          else
            {
            if( Rd_decode_bit( decoder->range_decoder, &decoder->bm_rep2[state] ) == 0 )
              distance = rep2;
            else { distance = rep3; rep3 = rep2; }
            rep2 = rep1;
            }
          rep1 = rep0;
          rep0 = distance;
          }
        else
          {
          if( Rd_decode_bit( decoder->range_decoder, &decoder->bm_len[state][pos_state] ) == 0 )
            { St_set_short_rep( &state ); len = 1; }
          }
        if( len == 0 )
          {
          St_set_rep( &state );
          len = min_match_len + Led_decode( &decoder->rep_match_len_decoder, decoder->range_decoder, pos_state );
          }
        }
      else
        {
        int dis_slot;
        const unsigned int rep0_saved = rep0;
        len = min_match_len + Led_decode( &decoder->len_decoder, decoder->range_decoder, pos_state );
        dis_slot = Rd_decode_tree( decoder->range_decoder, decoder->bm_dis_slot[get_dis_state(len)], dis_slot_bits );
        if( dis_slot < start_dis_model ) rep0 = dis_slot;
        else
          {
          const int direct_bits = ( dis_slot >> 1 ) - 1;
          rep0 = ( 2 | ( dis_slot & 1 ) ) << direct_bits;
          if( dis_slot < end_dis_model )
            rep0 += Rd_decode_tree_reversed( decoder->range_decoder, decoder->bm_dis + rep0 - dis_slot, direct_bits );
          else
            {
            rep0 += Rd_decode( decoder->range_decoder, direct_bits - dis_align_bits ) << dis_align_bits;
            rep0 += Rd_decode_tree_reversed( decoder->range_decoder, decoder->bm_align, dis_align_bits );
            if( rep0 == 0xFFFFFFFFU )		/* Marker found */
              {
              rep0 = rep0_saved;
              Rd_normalize( decoder->range_decoder );
              LZd_flush_data( decoder );
              if( len == min_match_len )	/* End Of Stream marker */
                {
                if( LZd_verify_trailer( decoder, pp ) ) return 0; else return 3;
                }
              if( len == min_match_len + 1 )	/* Sync Flush marker */
                {
                Rd_load( decoder->range_decoder ); continue;
                }
              if( pp->verbosity >= 0 )
                {
                Pp_show_msg( pp, 0 );
                fprintf( stderr, "Unsupported marker code `%d'.\n", len );
                }
              return 4;
              }
            }
          }
        rep3 = rep2; rep2 = rep1; rep1 = rep0_saved;
        St_set_match( &state );
        if( rep0 >= (unsigned int)decoder->dictionary_size ||
            ( rep0 >= (unsigned int)decoder->pos && !decoder->partial_data_pos ) )
          { LZd_flush_data( decoder ); return 1; }
        }
      LZd_copy_block( decoder, rep0, len );
      }
    }
  }
