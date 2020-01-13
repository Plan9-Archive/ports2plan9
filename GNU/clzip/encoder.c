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
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "clzip.h"
#include "encoder.h"


Dis_slots dis_slots;
Prob_prices prob_prices;


bool Mf_read_block( struct Matchfinder * const mf )
  {
  if( !mf->at_stream_end && mf->stream_pos < mf->buffer_size )
    {
    const int size = mf->buffer_size - mf->stream_pos;
    const int rd = readblock( mf->infd, mf->buffer + mf->stream_pos, size );
    mf->stream_pos += rd;
    if( rd != size && errno )
      { show_error( "Read error", errno, false ); cleanup_and_fail( 1 ); }
    mf->at_stream_end = ( rd < size );
    }
  return mf->pos < mf->stream_pos;
  }


void Mf_init( struct Matchfinder * const mf,
              const int dict_size, const int len_limit, const int ifd )
  {
  const int buffer_size_limit = ( 2 * dict_size ) + before_size + after_size;
  int i;
  mf->partial_data_pos = 0;
  mf->prev_positions =
    (int32_t *)malloc( num_prev_positions * sizeof (int32_t) );
  if( !mf->prev_positions )
    {
    show_error( "Not enough memory. Try a smaller dictionary size.", 0, false );
    cleanup_and_fail( 1 );
    }
  mf->pos = 0;
  mf->cyclic_pos = 0;
  mf->stream_pos = 0;
  mf->match_len_limit_ = len_limit;
  mf->cycles = ( len_limit < max_match_len ) ? 16 + ( len_limit / 2 ) : 256;
  mf->infd = ifd;
  mf->at_stream_end = false;

  mf->buffer_size = max( 65536, dict_size );
  mf->buffer = (uint8_t *)malloc( mf->buffer_size );
  if( !mf->buffer )
    {
    show_error( "Not enough memory. Try a smaller dictionary size.", 0, false );
    cleanup_and_fail( 1 );
    }
  if( Mf_read_block( mf ) && !mf->at_stream_end &&
      mf->buffer_size < buffer_size_limit )
    {
    mf->buffer_size = buffer_size_limit;
    mf->buffer = (uint8_t *)realloc( mf->buffer, mf->buffer_size );
    if( !mf->buffer )
      {
      show_error( "Not enough memory. Try a smaller dictionary size.", 0, false );
      cleanup_and_fail( 1 );
      }
    Mf_read_block( mf );
    }
  if( mf->at_stream_end && mf->stream_pos < dict_size )
    mf->dictionary_size_ = max( min_dictionary_size, mf->stream_pos );
  else mf->dictionary_size_ = dict_size;
  mf->pos_limit = mf->buffer_size;
  if( !mf->at_stream_end ) mf->pos_limit -= after_size;
  mf->prev_pos_tree =
    (int32_t *)malloc( 2 * mf->dictionary_size_ * sizeof (int32_t) );
  if( !mf->prev_pos_tree )
    {
    show_error( "Not enough memory. Try a smaller dictionary size.", 0, false );
    cleanup_and_fail( 1 );
    }
  for( i = 0; i < num_prev_positions; ++i ) mf->prev_positions[i] = -1;
  }


void Mf_reset( struct Matchfinder * const mf )
  {
  int i;
  const int size = mf->stream_pos - mf->pos;
  if( size > 0 ) memmove( mf->buffer, mf->buffer + mf->pos, size );
  mf->partial_data_pos = 0;
  mf->stream_pos -= mf->pos;
  mf->pos = 0;
  mf->cyclic_pos = 0;
  for( i = 0; i < num_prev_positions; ++i ) mf->prev_positions[i] = -1;
  Mf_read_block( mf );
  }


void Mf_move_pos( struct Matchfinder * const mf )
  {
  if( ++mf->cyclic_pos >= mf->dictionary_size_ ) mf->cyclic_pos = 0;
  if( ++mf->pos >= mf->pos_limit )
    {
    if( mf->pos > mf->stream_pos )
      internal_error( "pos > stream_pos in Mf_move_pos" );
    if( !mf->at_stream_end )
      {
      int i;
      const int offset = mf->pos - mf->dictionary_size_ - before_size;
      const int size = mf->stream_pos - offset;
      memmove( mf->buffer, mf->buffer + offset, size );
      mf->partial_data_pos += offset;
      mf->pos -= offset;
      mf->stream_pos -= offset;
      for( i = 0; i < num_prev_positions; ++i )
        if( mf->prev_positions[i] >= 0 ) mf->prev_positions[i] -= offset;
      for( i = 0; i < 2 * mf->dictionary_size_; ++i )
        if( mf->prev_pos_tree[i] >= 0 ) mf->prev_pos_tree[i] -= offset;
      Mf_read_block( mf );
      }
    }
  }


int Mf_longest_match_len( struct Matchfinder * const mf, int * const distances )
  {
  int32_t * ptr0 = mf->prev_pos_tree + ( mf->cyclic_pos << 1 );
  int32_t * ptr1 = ptr0 + 1;
  int32_t * newptr;
  const uint8_t * newdata;
  int len = 0, len0 = 0, len1 = 0;
  int maxlen = min_match_len - 1;
  const int min_pos = (mf->pos >= mf->dictionary_size_) ?
                      (mf->pos - mf->dictionary_size_ + 1) : 0;
  const uint8_t * const data = mf->buffer + mf->pos;
  int count, delta, key2, key3, key4, newpos, tmp;
  int len_limit = mf->match_len_limit_;

  if( len_limit > Mf_available_bytes( mf ) )
    {
    len_limit = Mf_available_bytes( mf );
    if( len_limit < 4 ) return 0;
    }

  key2 = num_prev_positions4 + num_prev_positions3 +
         ( ( (int)data[0] << 8 ) | data[1] );
  tmp = crc32[data[0]] ^ data[1] ^ ( (uint32_t)data[2] << 8 );
  key3 = num_prev_positions4 + (int)( tmp & ( num_prev_positions3 - 1 ) );
  key4 = (int)( ( tmp ^ ( crc32[data[3]] << 5 ) ) &
                ( num_prev_positions4 - 1 ) );

  if( distances )
    {
    int np = mf->prev_positions[key2];
    if( np >= min_pos )
      { distances[2] = mf->pos - np - 1; maxlen = 2; }
    else distances[2] = 0x7FFFFFFF;
    np = mf->prev_positions[key3];
    if( np >= min_pos && mf->buffer[np] == data[0] )
      { distances[3] = mf->pos - np - 1; maxlen = 3; }
    else distances[3] = 0x7FFFFFFF;
    distances[4] = 0x7FFFFFFF;
    }

  mf->prev_positions[key2] = mf->pos;
  mf->prev_positions[key3] = mf->pos;
  newpos = mf->prev_positions[key4];
  mf->prev_positions[key4] = mf->pos;


  for( count = mf->cycles; ; )
    {
    if( newpos < min_pos || --count < 0 ) { *ptr0 = *ptr1 = -1; break; }
    newdata = mf->buffer + newpos;
    while( len < len_limit && newdata[len] == data[len] ) ++len;

    delta = mf->pos - newpos;
    if( distances ) while( maxlen < len ) distances[++maxlen] = delta - 1;

    newptr = mf->prev_pos_tree +
      ( ( mf->cyclic_pos - delta +
          ( ( mf->cyclic_pos >= delta ) ? 0 : mf->dictionary_size_ ) ) << 1 );

    if( len < len_limit )
      {
      if( newdata[len] < data[len] )
        {
        *ptr0 = newpos;
        ptr0 = newptr + 1;
        newpos = *ptr0;
        len0 = len; if( len1 < len ) len = len1;
        }
      else
        {
        *ptr1 = newpos;
        ptr1 = newptr;
        newpos = *ptr1;
        len1 = len; if( len0 < len ) len = len0;
        }
      }
    else
      {
      *ptr0 = newptr[0];
      *ptr1 = newptr[1];
      break;
      }
    }
  if( distances )
    {
    if( distances[3] > distances[4] ) distances[3] = distances[4];
    if( distances[2] > distances[3] ) distances[2] = distances[3];
    }
  return maxlen;
  }


void Re_flush_data( struct Range_encoder * const range_encoder )
  {
  if( range_encoder->pos > 0 )
    {
    if( range_encoder->outfd >= 0 &&
        writeblock( range_encoder->outfd, range_encoder->buffer,
                    range_encoder->pos ) != range_encoder->pos )
      { show_error( "Write error", errno, false ); cleanup_and_fail( 1 ); }
    range_encoder->partial_member_pos += range_encoder->pos;
    range_encoder->pos = 0;
    }
  }


void Lee_encode( struct Len_encoder * const len_encoder,
                 struct Range_encoder * const range_encoder,
                 int symbol, const int pos_state )
  {
  symbol -= min_match_len;
  if( symbol < len_low_symbols )
    {
    Re_encode_bit( range_encoder, &len_encoder->choice1, 0 );
    Re_encode_tree( range_encoder, len_encoder->bm_low[pos_state], symbol, len_low_bits );
    }
  else
    {
    Re_encode_bit( range_encoder, &len_encoder->choice1, 1 );
    if( symbol < len_low_symbols + len_mid_symbols )
      {
      Re_encode_bit( range_encoder, &len_encoder->choice2, 0 );
      Re_encode_tree( range_encoder, len_encoder->bm_mid[pos_state], symbol - len_low_symbols, len_mid_bits );
      }
    else
      {
      Re_encode_bit( range_encoder, &len_encoder->choice2, 1 );
      Re_encode_tree( range_encoder, len_encoder->bm_high, symbol - len_low_symbols - len_mid_symbols, len_high_bits );
      }
    }
  if( --len_encoder->counters[pos_state] <= 0 )
    Lee_update_prices( len_encoder, pos_state );
  }


void LZe_fill_align_prices( struct LZ_encoder * const encoder )
  {
  int i;
  for( i = 0; i < dis_align_size; ++i )
    encoder->align_prices[i] = price_symbol_reversed( encoder->bm_align, i, dis_align_bits );
  encoder->align_price_count = dis_align_size;
  }


void LZe_fill_distance_prices( struct LZ_encoder * const encoder )
  {
  int dis, dis_state;
  for( dis = start_dis_model; dis < modeled_distances; ++dis )
    {
    const int dis_slot = dis_slots[dis];
    const int direct_bits = ( dis_slot >> 1 ) - 1;
    const int base = ( 2 | ( dis_slot & 1 ) ) << direct_bits;
    const int price =
      price_symbol_reversed( encoder->bm_dis + base - dis_slot, dis - base, direct_bits );
    for( dis_state = 0; dis_state < max_dis_states; ++dis_state )
      encoder->dis_prices[dis_state][dis] = price;
    }

  for( dis_state = 0; dis_state < max_dis_states; ++dis_state )
    {
    int * const dsp = encoder->dis_slot_prices[dis_state];
    int * const dp = encoder->dis_prices[dis_state];
    const Bit_model * const bmds = encoder->bm_dis_slot[dis_state];
    int slot = 0;
    for( ; slot < end_dis_model && slot < encoder->num_dis_slots; ++slot )
      dsp[slot] = price_symbol( bmds, slot, dis_slot_bits );
    for( ; slot < encoder->num_dis_slots; ++slot )
      dsp[slot] = price_symbol( bmds, slot, dis_slot_bits ) +
                  (((( slot >> 1 ) - 1 ) - dis_align_bits ) << price_shift );

    for( dis = 0; dis < start_dis_model; ++dis )
      dp[dis] = dsp[dis];
    for( ; dis < modeled_distances; ++dis )
      dp[dis] += dsp[dis_slots[dis]];
    }
  }


/* Return value == number of bytes advanced (ahead).
   trials[0]..trials[retval-1] contain the steps to encode.
   ( trials[0].dis == -1 && trials[0].price == 1 ) means literal. */
int LZe_sequence_optimizer( struct LZ_encoder * const encoder,
                            const int reps[num_rep_distances], const State state )
  {
  int main_len, i, rep, cur = 0, num_trials;
  int replens[num_rep_distances];
  int rep_index = 0;

  if( encoder->longest_match_found > 0 )		/* from previous call */
    {
    main_len = encoder->longest_match_found;
    encoder->longest_match_found = 0;
    }
  else main_len = LZe_read_match_distances( encoder );

  for( i = 0; i < num_rep_distances; ++i )
    {
    replens[i] = Mf_true_match_len( encoder->matchfinder, 0, reps[i] + 1, max_match_len );
    if( replens[i] > replens[rep_index] ) rep_index = i;
    }
  if( replens[rep_index] >= Mf_match_len_limit( encoder->matchfinder ) )
    {
    encoder->trials[0].dis = rep_index;
    encoder->trials[0].price = replens[rep_index];
    LZe_move_pos( encoder, replens[rep_index], true );
    return replens[rep_index];
    }

  if( main_len >= Mf_match_len_limit( encoder->matchfinder ) )
    {
    encoder->trials[0].dis = encoder->match_distances[Mf_match_len_limit( encoder->matchfinder )] +
                             num_rep_distances;
    encoder->trials[0].price = main_len;
    LZe_move_pos( encoder, main_len, true );
    return main_len;
    }

  {
  const int pos_state = Mf_data_position( encoder->matchfinder ) & pos_state_mask;
  const int match_price = price1( encoder->bm_match[state][pos_state] );
  const int rep_match_price = match_price + price1( encoder->bm_rep[state] );
  const uint8_t prev_byte = Mf_peek( encoder->matchfinder, -1 );
  const uint8_t cur_byte = Mf_peek( encoder->matchfinder, 0 );
  const uint8_t match_byte = Mf_peek( encoder->matchfinder, -reps[0]-1 );

  encoder->trials[0].state = state;
  for( i = 0; i < num_rep_distances; ++i ) encoder->trials[0].reps[i] = reps[i];
  encoder->trials[1].dis = -1;
  encoder->trials[1].prev_index = 0;
  encoder->trials[1].price = price0( encoder->bm_match[state][pos_state] );
  if( St_is_char( state ) )
    encoder->trials[1].price += Lie_price_symbol( &encoder->literal_encoder, prev_byte, cur_byte );
  else
    encoder->trials[1].price += Lie_price_matched( &encoder->literal_encoder, prev_byte, cur_byte, match_byte );

  if( match_byte == cur_byte )
    Tr_update( &encoder->trials[1], 0, 0, rep_match_price + LZe_price_rep_len1( encoder, state, pos_state ) );

  if( main_len < min_match_len )
    {
    encoder->trials[0].dis = encoder->trials[1].dis;
    encoder->trials[0].price = 1;
    Mf_move_pos( encoder->matchfinder );
    return 1;
    }

  if( main_len <= replens[rep_index] )
    {
    int len;
    main_len = replens[rep_index];
    for( len = min_match_len; len <= main_len; ++len )
      encoder->trials[len].price = infinite_price;
    }
  else
    {
    int len;
    const int normal_match_price = match_price + price0( encoder->bm_rep[state] );
    for( len = min_match_len; len <= main_len; ++len )
      {
      encoder->trials[len].dis = encoder->match_distances[len] + num_rep_distances;
      encoder->trials[len].prev_index = 0;
      encoder->trials[len].price = normal_match_price +
                                   LZe_price_pair( encoder, encoder->match_distances[len], len, pos_state );
      }
    }

  for( rep = 0; rep < num_rep_distances; ++rep )
    {
    const int price = rep_match_price +
                      LZe_price_rep( encoder, rep, state, pos_state );
    int len;
    for( len = min_match_len; len <= replens[rep]; ++len )
      Tr_update( &encoder->trials[len], rep, 0, price +
                 Lee_price( &encoder->rep_match_len_encoder, len, pos_state ) );
    }
  }

  num_trials = main_len;
  Mf_move_pos( encoder->matchfinder );

  while( true )
    {
    struct Trial *cur_trial, *next_trial;
    int newlen, pos_state, prev_index, len_limit;
    int next_price, match_price, rep_match_price;
    uint8_t prev_byte, cur_byte, match_byte;

    if( ++cur >= num_trials )		/* no more initialized trials */
      {
      LZe_backward( encoder, cur );
      return cur;
      }
    newlen = LZe_read_match_distances( encoder );
    if( newlen >= Mf_match_len_limit( encoder->matchfinder ) )
      {
      encoder->longest_match_found = newlen;
      LZe_backward( encoder, cur );
      return cur;
      }

    cur_trial = &encoder->trials[cur];
    prev_index = cur_trial->prev_index;

    cur_trial->state = encoder->trials[prev_index].state;

    for( i = 0; i < num_rep_distances; ++i )
      cur_trial->reps[i] = encoder->trials[prev_index].reps[i];
    if( prev_index == cur - 1 )
      {
      if( cur_trial->dis == 0 ) St_set_short_rep( &cur_trial->state );
      else St_set_char( &cur_trial->state );
      }
    else
      {
      if( cur_trial->dis < num_rep_distances ) St_set_rep( &cur_trial->state );
      else St_set_match( &cur_trial->state );
      LZe_mtf_reps( cur_trial->dis, cur_trial->reps );
      }

    pos_state = Mf_data_position( encoder->matchfinder ) & pos_state_mask;
    prev_byte = Mf_peek( encoder->matchfinder, -1 );
    cur_byte = Mf_peek( encoder->matchfinder, 0 );
    match_byte = Mf_peek( encoder->matchfinder, -cur_trial->reps[0]-1 );

    next_price = cur_trial->price + price0( encoder->bm_match[cur_trial->state][pos_state] );
    if( St_is_char( cur_trial->state ) )
      next_price += Lie_price_symbol( &encoder->literal_encoder, prev_byte, cur_byte );
    else
      next_price += Lie_price_matched( &encoder->literal_encoder, prev_byte, cur_byte, match_byte );
    Mf_move_pos( encoder->matchfinder );

    next_trial = &encoder->trials[cur+1];

    Tr_update( next_trial, -1, cur, next_price );

    match_price = cur_trial->price + price1( encoder->bm_match[cur_trial->state][pos_state] );
    rep_match_price = match_price + price1( encoder->bm_rep[cur_trial->state] );

    if( match_byte == cur_byte && next_trial->dis != 0 )
      Tr_update( next_trial, 0, cur, rep_match_price +
                 LZe_price_rep_len1( encoder, cur_trial->state, pos_state ) );

    len_limit = min( min( max_num_trials - 1 - cur,
                          Mf_available_bytes( encoder->matchfinder ) ),
                     Mf_match_len_limit( encoder->matchfinder ) );
    if( len_limit < min_match_len ) continue;

    for( rep = 0; rep < num_rep_distances; ++rep )
      {
      const int dis = cur_trial->reps[rep] + 1;
      int len = 0;
      const uint8_t * const data = Mf_ptr_to_current_pos( encoder->matchfinder ) - 1;
      while( len < len_limit && data[len] == data[len-dis] ) ++len;
      if( len >= min_match_len )
        {
        const int price = rep_match_price +
                          LZe_price_rep( encoder, rep, cur_trial->state, pos_state );
        while( num_trials < cur + len )
          encoder->trials[++num_trials].price = infinite_price;
        for( ; len >= min_match_len; --len )
          Tr_update( &encoder->trials[cur+len], rep, cur, price +
                     Lee_price( &encoder->rep_match_len_encoder, len, pos_state ) );
        }
      }

    if( newlen <= len_limit &&
        ( newlen > min_match_len ||
          ( newlen == min_match_len &&
            encoder->match_distances[min_match_len] < modeled_distances ) ) )
      {
      const int normal_match_price = match_price +
                                     price0( encoder->bm_rep[cur_trial->state] );
      int len;
      int dis = encoder->match_distances[min_match_len];
      int dis_state = get_dis_state( min_match_len );
      int dis_price = infinite_price;

      while( num_trials < cur + newlen )
        encoder->trials[++num_trials].price = infinite_price;

      if( dis < modeled_distances )
        Tr_update( &encoder->trials[cur+min_match_len], dis + num_rep_distances,
                   cur, normal_match_price + encoder->dis_prices[dis_state][dis] +
                   Lee_price( &encoder->len_encoder, min_match_len, pos_state ) );

      for( len = min_match_len + 1; len <= newlen; ++len )
        {
        if( dis != encoder->match_distances[len] ||
            dis_state < max_dis_states - 1 )
          {
          dis = encoder->match_distances[len];
          dis_state = get_dis_state( len );
          dis_price = LZe_price_dis( encoder, dis, dis_state );
          }
        Tr_update( &encoder->trials[cur+len], dis + num_rep_distances, cur,
                   normal_match_price + dis_price +
                   Lee_price( &encoder->len_encoder, len, pos_state ) );
        }
      }
    }
  }


     /* End Of Stream mark => (dis == 0xFFFFFFFFU, len == min_match_len) */
void LZe_full_flush( struct LZ_encoder * const encoder, const State state )
  {
  int i;
  const int pos_state = Mf_data_position( encoder->matchfinder ) & pos_state_mask;
  File_trailer trailer;
  Re_encode_bit( &encoder->range_encoder, &encoder->bm_match[state][pos_state], 1 );
  Re_encode_bit( &encoder->range_encoder, &encoder->bm_rep[state], 0 );
  LZe_encode_pair( encoder, 0xFFFFFFFFU, min_match_len, pos_state );
  Re_flush( &encoder->range_encoder );
  Ft_set_data_crc( trailer, LZe_crc( encoder ) );
  Ft_set_data_size( trailer, Mf_data_position( encoder->matchfinder ) );
  Ft_set_member_size( trailer, LZe_member_position( encoder ) + Ft_size );
  for( i = 0; i < Ft_size; ++i )
    Re_put_byte( &encoder->range_encoder, trailer[i] );
  Re_flush_data( &encoder->range_encoder );
  }


void LZe_init( struct LZ_encoder * const encoder, struct Matchfinder * const mf,
               const File_header header, const int outfd )
  {
  int i, j;
  encoder->longest_match_found = 0;
  encoder->crc_ = 0xFFFFFFFFU;

  for( i = 0; i < states; ++i )
    {
    for( j = 0; j < pos_states; ++j )
      {
      Bm_init( &encoder->bm_match[i][j] );
      Bm_init( &encoder->bm_len[i][j] );
      }
    Bm_init( &encoder->bm_rep[i] );
    Bm_init( &encoder->bm_rep0[i] );
    Bm_init( &encoder->bm_rep1[i] );
    Bm_init( &encoder->bm_rep2[i] );
    }
  for( i = 0; i < max_dis_states; ++i )
    for( j = 0; j < 1<<dis_slot_bits; ++j )
      Bm_init( &encoder->bm_dis_slot[i][j] );
  for( i = 0; i < modeled_distances-end_dis_model+1; ++i )
    Bm_init( &encoder->bm_dis[i] );
  for( i = 0; i < dis_align_size; ++i )
    Bm_init( &encoder->bm_align[i] );

  encoder->matchfinder = mf;
  Re_init( &encoder->range_encoder, outfd );
  Lee_init( &encoder->len_encoder, Mf_match_len_limit( encoder->matchfinder ) ),
  Lee_init( &encoder->rep_match_len_encoder, Mf_match_len_limit( encoder->matchfinder ) ),
  Lie_init( &encoder->literal_encoder );
  encoder->num_dis_slots = 2 * real_bits( Mf_dictionary_size( encoder->matchfinder ) - 1 );

  LZe_fill_align_prices( encoder );

  for( i = 0; i < Fh_size; ++i )
    Re_put_byte( &encoder->range_encoder, header[i] );
  }


bool LZe_encode_member( struct LZ_encoder * const encoder,
                        const long long member_size )
  {
  const long long member_size_limit =
    member_size - Ft_size - max_marker_size;
  const int fill_count =
    ( Mf_match_len_limit( encoder->matchfinder ) > 12 ) ? 512 : 2048;
  int fill_counter = 0;
  int ahead;
  int i;
  int rep_distances[num_rep_distances];
  State state = 0;
  for( i = 0; i < num_rep_distances; ++i ) rep_distances[i] = 0;

  if( Mf_data_position( encoder->matchfinder ) != 0 ||
      LZe_member_position( encoder ) != Fh_size )
    return false;			/* can be called only once */

  if( !Mf_finished( encoder->matchfinder ) )	/* encode first byte */
    {
    const uint8_t prev_byte = 0;
    const uint8_t cur_byte = Mf_peek( encoder->matchfinder, 0 );
    Re_encode_bit( &encoder->range_encoder, &encoder->bm_match[state][0], 0 );
    Lie_encode( &encoder->literal_encoder, &encoder->range_encoder, prev_byte, cur_byte );
    CRC32_update_byte( &encoder->crc_, cur_byte );
    LZe_move_pos( encoder, 1, false );
    }

  while( true )
    {
    if( Mf_finished( encoder->matchfinder ) )
      { LZe_full_flush( encoder, state ); return true; }
    if( fill_counter <= 0 )
      { LZe_fill_distance_prices( encoder ); fill_counter = fill_count; }

    ahead = LZe_sequence_optimizer( encoder, rep_distances, state );
    if( ahead <= 0 ) return false;
    fill_counter -= ahead;

    for( i = 0; ; )
      {
      const int pos_state = ( Mf_data_position( encoder->matchfinder ) - ahead ) & pos_state_mask;
      const int dis = encoder->trials[i].dis;
      const int len = encoder->trials[i].price;

      bool bit = ( dis < 0 && len == 1 );
      Re_encode_bit( &encoder->range_encoder, &encoder->bm_match[state][pos_state], !bit );
      if( bit )				/* literal byte */
        {
        const uint8_t prev_byte = Mf_peek( encoder->matchfinder, -ahead-1 );
        const uint8_t cur_byte = Mf_peek( encoder->matchfinder, -ahead );
        CRC32_update_byte( &encoder->crc_, cur_byte );
        if( St_is_char( state ) )
          Lie_encode( &encoder->literal_encoder, &encoder->range_encoder, prev_byte, cur_byte );
        else
          {
          const uint8_t match_byte = Mf_peek( encoder->matchfinder, -ahead-rep_distances[0]-1 );
          Lie_encode_matched( &encoder->literal_encoder, &encoder->range_encoder, prev_byte, cur_byte, match_byte );
          }
        St_set_char( &state );
        }
      else				/* match or repeated match */
        {
        CRC32_update_buf( &encoder->crc_, Mf_ptr_to_current_pos( encoder->matchfinder ) - ahead, len );
        LZe_mtf_reps( dis, rep_distances );
        bit = ( dis < num_rep_distances );
        Re_encode_bit( &encoder->range_encoder, &encoder->bm_rep[state], bit );
        if( bit )
          {
          bit = ( dis == 0 );
          Re_encode_bit( &encoder->range_encoder, &encoder->bm_rep0[state], !bit );
          if( bit )
            Re_encode_bit( &encoder->range_encoder, &encoder->bm_len[state][pos_state], len > 1 );
          else
            {
            Re_encode_bit( &encoder->range_encoder, &encoder->bm_rep1[state], dis > 1 );
            if( dis > 1 )
              Re_encode_bit( &encoder->range_encoder, &encoder->bm_rep2[state], dis > 2 );
            }
          if( len == 1 ) St_set_short_rep( &state );
          else
            {
            Lee_encode( &encoder->rep_match_len_encoder, &encoder->range_encoder, len, pos_state );
            St_set_rep( &state );
            }
          }
        else
          {
          LZe_encode_pair( encoder, dis - num_rep_distances, len, pos_state );
          St_set_match( &state );
          }
        }
      ahead -= len; i += len;
      if( LZe_member_position( encoder ) >= member_size_limit )
        {
        if( !Mf_dec_pos( encoder->matchfinder, ahead ) ) return false;
        LZe_full_flush( encoder, state );
        return true;
        }
      if( ahead <= 0 ) break;
      }
    }
  }
