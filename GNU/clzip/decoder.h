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

enum { rd_buffer_size = 16384 };

struct Range_decoder
  {
  long long partial_member_pos;
  uint8_t * buffer;		/* input buffer */
  int pos;			/* current pos in buffer */
  int stream_pos;		/* when reached, a new block must be read */
  uint32_t code;
  uint32_t range;
  int infd;			/* input file descriptor */
  bool at_stream_end;
  };

bool Rd_read_block( struct Range_decoder * const rdec );

static inline void Rd_init( struct Range_decoder * const rdec, const int ifd )
  {
  rdec->partial_member_pos = 0;
  rdec->buffer = (uint8_t *)malloc( rd_buffer_size );
  if( !rdec->buffer )
    {
    show_error( "Not enough memory. Find a machine with more memory.", 0, false );
    cleanup_and_fail( 1 );
    }
  rdec->pos = 0;
  rdec->stream_pos = 0;
  rdec->code = 0;
  rdec->range = 0xFFFFFFFFU;
  rdec->infd = ifd;
  rdec->at_stream_end = false;
  }

static inline void Rd_free( struct Range_decoder * const rdec )
  { free( rdec->buffer ); rdec->buffer = 0; }

static inline bool Rd_code_is_zero( struct Range_decoder * const rdec )
  { return ( rdec->code == 0 ); }

static inline bool Rd_finished( struct Range_decoder * const rdec )
  { return rdec->pos >= rdec->stream_pos && !Rd_read_block( rdec ); }

static inline long long Rd_member_position( struct Range_decoder * const rdec )
  { return rdec->partial_member_pos + rdec->pos; }

static inline void Rd_reset_member_position( struct Range_decoder * const rdec )
  { rdec->partial_member_pos = -rdec->pos; }

static inline uint8_t Rd_get_byte( struct Range_decoder * const rdec )
  {
  if( Rd_finished( rdec ) ) return 0x55;	/* make code != 0 */
  return rdec->buffer[rdec->pos++];
  }

static inline void Rd_load( struct Range_decoder * const rdec )
  {
  int i;
  rdec->code = 0;
  rdec->range = 0xFFFFFFFFU;
  for( i = 0; i < 5; ++i )
    rdec->code = (rdec->code << 8) | Rd_get_byte( rdec );
  }

static inline void Rd_normalize( struct Range_decoder * const rdec )
  {
  if( rdec->range <= 0x00FFFFFFU )
    {
    rdec->range <<= 8;
    rdec->code = (rdec->code << 8) | Rd_get_byte( rdec );
    }
  }

static inline int Rd_decode( struct Range_decoder * const rdec,
                             const int num_bits )
  {
  int symbol = 0;
  int i;
  for( i = num_bits; i > 0; --i )
    {
    symbol <<= 1;
    if( rdec->range <= 0x00FFFFFFU )
      {
      rdec->range <<= 7;
      rdec->code = (rdec->code << 8) | Rd_get_byte( rdec );
      if( rdec->code >= rdec->range )
        { rdec->code -= rdec->range; symbol |= 1; }
      }
    else
      {
      rdec->range >>= 1;
      if( rdec->code >= rdec->range )
        { rdec->code -= rdec->range; symbol |= 1; }
      }
    }
  return symbol;
  }

static inline int Rd_decode_bit( struct Range_decoder * const rdec,
                                 Bit_model * const probability )
  {
  uint32_t bound;
  Rd_normalize( rdec );
  bound = ( rdec->range >> bit_model_total_bits ) * *probability;
  if( rdec->code < bound )
    {
    rdec->range = bound;
    *probability += (bit_model_total - *probability) >> bit_model_move_bits;
    return 0;
    }
  else
    {
    rdec->range -= bound;
    rdec->code -= bound;
    *probability -= *probability >> bit_model_move_bits;
    return 1;
    }
  }

static inline int Rd_decode_tree( struct Range_decoder * const rdec,
                                  Bit_model bm[], const int num_bits )
  {
  int model = 1;
  int i;
  for( i = num_bits; i > 0; --i )
    model = ( model << 1 ) | Rd_decode_bit( rdec, &bm[model] );
  return model - (1 << num_bits);
  }

static inline int Rd_decode_tree_reversed( struct Range_decoder * const rdec,
                                           Bit_model bm[], const int num_bits )
  {
  int model = 1;
  int symbol = 0;
  int i;
  for( i = 0; i < num_bits; ++i )
    {
    const int bit = Rd_decode_bit( rdec, &bm[model] );
    model <<= 1;
    if( bit ) { model |= 1; symbol |= (1 << i); }
    }
  return symbol;
  }

static inline int Rd_decode_matched( struct Range_decoder * const rdec,
                                     Bit_model bm[], const int match_byte )
  {
  Bit_model * const bm1 = bm + 0x100;
  int symbol = 1;
  int i;
  for( i = 7; i >= 0; --i )
    {
    const int match_bit = ( match_byte >> i ) & 1;
    const int bit = Rd_decode_bit( rdec, &bm1[(match_bit<<8)+symbol] );
    symbol = ( symbol << 1 ) | bit;
    if( match_bit != bit )
      {
      while( --i >= 0 )
        symbol = ( symbol << 1 ) | Rd_decode_bit( rdec, &bm[symbol] );
      break;
      }
    }
  return symbol & 0xFF;
  }


struct Len_decoder
  {
  Bit_model choice1;
  Bit_model choice2;
  Bit_model bm_low[pos_states][len_low_symbols];
  Bit_model bm_mid[pos_states][len_mid_symbols];
  Bit_model bm_high[len_high_symbols];
  };

static inline void Led_init( struct Len_decoder * const len_decoder )
  {
  int i, j;
  Bm_init( &len_decoder->choice1 );
  Bm_init( &len_decoder->choice2 );
  for( i = 0; i < pos_states; ++i )
    for( j = 0; j < len_low_symbols; ++j )
      Bm_init( &len_decoder->bm_low[i][j] );
  for( i = 0; i < pos_states; ++i )
    for( j = 0; j < len_mid_symbols; ++j )
      Bm_init( &len_decoder->bm_mid[i][j] );
  for( i = 0; i < len_high_symbols; ++i )
    Bm_init( &len_decoder->bm_high[i] );
  }

static inline int Led_decode( struct Len_decoder * const len_decoder,
                              struct Range_decoder * const rdec,
                              const int pos_state )
  {
  if( Rd_decode_bit( rdec, &len_decoder->choice1 ) == 0 )
    return Rd_decode_tree( rdec, len_decoder->bm_low[pos_state], len_low_bits );
  if( Rd_decode_bit( rdec, &len_decoder->choice2 ) == 0 )
    return len_low_symbols +
           Rd_decode_tree( rdec, len_decoder->bm_mid[pos_state], len_mid_bits );
  return len_low_symbols + len_mid_symbols +
         Rd_decode_tree( rdec, len_decoder->bm_high, len_high_bits );
  }


struct Literal_decoder
  {
  Bit_model bm_literal[1<<literal_context_bits][0x300];
  };

static inline void Lid_init( struct Literal_decoder * const literal_decoder )
  {
  int i, j;
  for( i = 0; i < 1<<literal_context_bits; ++i )
    for( j = 0; j < 0x300; ++j )
      Bm_init( &literal_decoder->bm_literal[i][j] );
  }

static inline int Lid_state( const int prev_byte )
  { return ( prev_byte >> ( 8 - literal_context_bits ) ); }

static inline uint8_t Lid_decode( struct Literal_decoder * const literal_decoder,
                                  struct Range_decoder * const rdec,
                                  const uint8_t prev_byte )
  { return Rd_decode_tree( rdec, literal_decoder->bm_literal[Lid_state(prev_byte)], 8 ); }

static inline uint8_t Lid_decode_matched( struct Literal_decoder * const literal_decoder,
                                          struct Range_decoder * const rdec,
                                          const uint8_t prev_byte,
                                          const uint8_t match_byte )
  { return Rd_decode_matched( rdec, literal_decoder->bm_literal[Lid_state(prev_byte)], match_byte ); }


struct LZ_decoder
  {
  long long partial_data_pos;
  int dictionary_size;
  int buffer_size;
  uint8_t * buffer;		/* output buffer */
  int pos;			/* current pos in buffer */
  int stream_pos;		/* first byte not yet written to file */
  uint32_t crc_;
  int outfd;			/* output file descriptor */
  int member_version;

  Bit_model bm_match[states][pos_states];
  Bit_model bm_rep[states];
  Bit_model bm_rep0[states];
  Bit_model bm_rep1[states];
  Bit_model bm_rep2[states];
  Bit_model bm_len[states][pos_states];
  Bit_model bm_dis_slot[max_dis_states][1<<dis_slot_bits];
  Bit_model bm_dis[modeled_distances-end_dis_model+1];
  Bit_model bm_align[dis_align_size];

  struct Range_decoder * range_decoder;
  struct Len_decoder len_decoder;
  struct Len_decoder rep_match_len_decoder;
  struct Literal_decoder literal_decoder;
  };

void LZd_flush_data( struct LZ_decoder * const decoder );

bool LZd_verify_trailer( struct LZ_decoder * const decoder,
                         struct Pretty_print * const pp );

static inline uint8_t LZd_get_prev_byte( struct LZ_decoder * const decoder )
    {
    const int i =
      ( ( decoder->pos > 0 ) ? decoder->pos : decoder->buffer_size ) - 1;
    return decoder->buffer[i];
    }

static inline uint8_t LZd_get_byte( struct LZ_decoder * const decoder,
                                    const int distance )
  {
  int i = decoder->pos - distance - 1;
  if( i < 0 ) i += decoder->buffer_size;
  return decoder->buffer[i];
  }

static inline void LZd_put_byte( struct LZ_decoder * const decoder,
                                 const uint8_t b )
  {
  decoder->buffer[decoder->pos] = b;
  if( ++decoder->pos >= decoder->buffer_size ) LZd_flush_data( decoder );
  }

static inline void LZd_copy_block( struct LZ_decoder * const decoder,
                                   const int distance, int len )
  {
  int i = decoder->pos - distance - 1;
  if( i < 0 ) i += decoder->buffer_size;
  if( len < decoder->buffer_size - max( decoder->pos, i ) &&
      len <= abs( decoder->pos - i ) )
    {
    memcpy( decoder->buffer + decoder->pos, decoder->buffer + i, len );
    decoder->pos += len;
    }
  else for( ; len > 0 ; --len )
    {
    decoder->buffer[decoder->pos] = decoder->buffer[i];
    if( ++decoder->pos >= decoder->buffer_size ) LZd_flush_data( decoder );
    if( ++i >= decoder->buffer_size ) i = 0;
    }
  }

static inline void LZd_init( struct LZ_decoder * const decoder,
                             const File_header header,
                             struct Range_decoder * const rdec, const int ofd )
  {
  int i, j;
  decoder->partial_data_pos = 0;
  decoder->dictionary_size = Fh_get_dictionary_size( header );
  decoder->buffer_size = max( 65536, decoder->dictionary_size );
  decoder->buffer = (uint8_t *)malloc( decoder->buffer_size );
  if( !decoder->buffer )
    {
    show_error( "Not enough memory. Find a machine with more memory.", 0, false );
    cleanup_and_fail( 1 );
    }
  decoder->pos = 0;
  decoder->stream_pos = 0;
  decoder->crc_ = 0xFFFFFFFFU;
  decoder->outfd = ofd;
  decoder->member_version = Fh_version( header );

  for( i = 0; i < states; ++i )
    {
    for( j = 0; j < pos_states; ++j )
      {
      Bm_init( &decoder->bm_match[i][j] );
      Bm_init( &decoder->bm_len[i][j] );
      }
    Bm_init( &decoder->bm_rep[i] );
    Bm_init( &decoder->bm_rep0[i] );
    Bm_init( &decoder->bm_rep1[i] );
    Bm_init( &decoder->bm_rep2[i] );
    }
  for( i = 0; i < max_dis_states; ++i )
    for( j = 0; j < 1<<dis_slot_bits; ++j )
      Bm_init( &decoder->bm_dis_slot[i][j] );
  for( i = 0; i < modeled_distances-end_dis_model+1; ++i )
    Bm_init( &decoder->bm_dis[i] );
  for( i = 0; i < dis_align_size; ++i )
    Bm_init( &decoder->bm_align[i] );

  decoder->range_decoder = rdec;
  Led_init( &decoder->len_decoder );
  Led_init( &decoder->rep_match_len_decoder );
  Lid_init( &decoder->literal_decoder );
  decoder->buffer[decoder->buffer_size-1] = 0;	/* prev_byte of first_byte */
  }

static inline void LZd_free( struct LZ_decoder * const decoder )
  { free( decoder->buffer ); decoder->buffer = 0; }

static inline uint32_t LZd_crc( struct LZ_decoder * const decoder )
  { return decoder->crc_ ^ 0xFFFFFFFFU; }

static inline long long LZd_data_position( struct LZ_decoder * const decoder )
  { return decoder->partial_data_pos + decoder->pos; }

int LZd_decode_member( struct LZ_decoder * const decoder,
                       struct Pretty_print * const pp );
