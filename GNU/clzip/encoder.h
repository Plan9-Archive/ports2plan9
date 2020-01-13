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

enum { max_num_trials = 1 << 12,
       price_shift = 6 };

typedef unsigned char Dis_slots[1<<12];

extern Dis_slots dis_slots;

static inline void Dis_slots_init(void)
  {
  int i, size, slot;
  for( slot = 0; slot < 4; ++slot ) dis_slots[slot] = slot;
  for( i = 4, size = 2, slot = 4; slot < 24; slot += 2 )
    {
    memset( &dis_slots[i], slot, size );
    memset( &dis_slots[i+size], slot + 1, size );
    size <<= 1;
    i += size;
    }
  }

static inline int get_slot( const uint32_t dis )
  {
  if( dis < (1 << 12) ) return dis_slots[dis];
  if( dis < (1 << 23) ) return dis_slots[dis>>11] + 22;
  return dis_slots[dis>>22] + 44;
  }


typedef int Prob_prices[bit_model_total >> 2];

extern Prob_prices prob_prices;

static inline void Prob_prices_init(void)
  {
  const int num_bits = ( bit_model_total_bits - 2 );
  int i, j = 1, end = 2;
  prob_prices[0] = bit_model_total_bits << price_shift;
  for( i = num_bits - 1; i >= 0; --i, end <<= 1 )
    {
    for( ; j < end; ++j )
      prob_prices[j] = ( i << price_shift ) +
                       ( ((end - j) << price_shift) >> (num_bits - i - 1) );
    }
  }

static inline int get_price( const int probability )
  { return prob_prices[probability >> 2]; }


static inline int price0( const Bit_model probability )
  { return get_price( probability ); }

static inline int price1( const Bit_model probability )
  { return get_price( bit_model_total-probability ); }

static inline int price_bit( const Bit_model bm, const int bit )
  { if( bit ) return price1( bm ); else return price0( bm ); }


static inline int price_symbol( const Bit_model bm[], int symbol,
                                const int num_bits )
  {
  int price = 0;
  symbol |= ( 1 << num_bits );
  while( symbol > 1 )
    {
    const int bit = symbol & 1;
    symbol >>= 1;
    price += price_bit( bm[symbol], bit );
    }
  return price;
  }


static inline int price_symbol_reversed( const Bit_model bm[], int symbol,
                                         const int num_bits )
  {
  int price = 0;
  int model = 1;
  int i;
  for( i = num_bits; i > 0; --i )
    {
    const int bit = symbol & 1;
    symbol >>= 1;
    price += price_bit( bm[model], bit );
    model = ( model << 1 ) | bit;
    }
  return price;
  }


static inline int price_matched( const Bit_model bm[], const int symbol,
                                 const int match_byte )
  {
  int price = 0;
  int model = 1;
  int i;

  for( i = 7; i >= 0; --i )
    {
    const int match_bit = ( match_byte >> i ) & 1;
    int bit = ( symbol >> i ) & 1;
    price += price_bit( bm[(match_bit<<8)+model+0x100], bit );
    model = ( model << 1 ) | bit;
    if( match_bit != bit )
      {
      while( --i >= 0 )
        {
        bit = ( symbol >> i ) & 1;
        price += price_bit( bm[model], bit );
        model = ( model << 1 ) | bit;
        }
      break;
      }
    }
  return price;
  }


enum { /* bytes to keep in buffer before dictionary */
       before_size = max_num_trials + 1,
       /* bytes to keep in buffer after pos */
       after_size = max_match_len,
       num_prev_positions4 = 1 << 20,
       num_prev_positions3 = 1 << 18,
       num_prev_positions2 = 1 << 16,
       num_prev_positions = num_prev_positions4 + num_prev_positions3 +
                               num_prev_positions2 };

struct Matchfinder
  {
  long long partial_data_pos;
  uint8_t * buffer;		/* input buffer */
  int32_t * prev_positions;	/* last seen position of key */
  int32_t * prev_pos_tree;
  int dictionary_size_;		/* bytes to keep in buffer before pos */
  int buffer_size;
  int pos;			/* current pos in buffer */
  int cyclic_pos;		/* current pos in dictionary */
  int stream_pos;		/* first byte not yet read from file */
  int pos_limit;		/* when reached, a new block must be read */
  int match_len_limit_;
  int cycles;
  int infd;			/* input file descriptor */
  bool at_stream_end;		/* stream_pos shows real end of file */
  };

bool Mf_read_block( struct Matchfinder * const mf );

void Mf_init( struct Matchfinder * const mf,
              const int dict_size, const int len_limit, const int ifd );

static inline void Mf_free( struct Matchfinder * const mf )
  {
  free( mf->prev_pos_tree ); mf->prev_pos_tree = 0;
  free( mf->prev_positions ); mf->prev_positions = 0;
  free( mf->buffer ); mf->buffer = 0;
  }

static inline uint8_t Mf_peek( struct Matchfinder * const mf, const int i )
  { return mf->buffer[mf->pos+i]; }
static inline int Mf_available_bytes( struct Matchfinder * const mf )
  { return mf->stream_pos - mf->pos; }
static inline long long Mf_data_position( struct Matchfinder * const mf )
  { return mf->partial_data_pos + mf->pos; }
static inline int Mf_dictionary_size( struct Matchfinder * const mf )
  { return mf->dictionary_size_; }
static inline bool Mf_finished( struct Matchfinder * const mf )
  { return mf->at_stream_end && mf->pos >= mf->stream_pos; }
static inline int Mf_match_len_limit( struct Matchfinder * const mf )
  { return mf->match_len_limit_; }
static inline const uint8_t * Mf_ptr_to_current_pos( struct Matchfinder * const mf )
  { return mf->buffer + mf->pos; }

static inline bool Mf_dec_pos( struct Matchfinder * const mf,
                               const int ahead )
  {
  if( ahead < 0 || mf->pos < ahead ) return false;
  mf->pos -= ahead;
  mf->cyclic_pos -= ahead;
  if( mf->cyclic_pos < 0 ) mf->cyclic_pos += mf->dictionary_size_;
  return true;
  }

static inline int Mf_true_match_len( struct Matchfinder * const mf,
                                     const int index, const int distance,
                                     int len_limit )
  {
  const uint8_t * const data = mf->buffer + mf->pos + index - distance;
  int i = 0;

  if( index + len_limit > Mf_available_bytes( mf ) )
    len_limit = Mf_available_bytes( mf ) - index;
  while( i < len_limit && data[i] == data[i+distance] ) ++i;
  return i;
  }

void Mf_reset( struct Matchfinder * const mf );
void Mf_move_pos( struct Matchfinder * const mf );
int Mf_longest_match_len( struct Matchfinder * const mf, int * const distances );


enum { re_buffer_size = 65536 };

struct Range_encoder
  {
  uint64_t low;
  long long partial_member_pos;
  uint8_t * buffer;		/* output buffer */
  int pos;			/* current pos in buffer */
  uint32_t range;
  int ff_count;
  int outfd;			/* output file descriptor */
  uint8_t cache;
  };

void Re_flush_data( struct Range_encoder * const range_encoder );

static inline void Re_put_byte( struct Range_encoder * const range_encoder,
                                const uint8_t b )
  {
  range_encoder->buffer[range_encoder->pos] = b;
  if( ++range_encoder->pos >= re_buffer_size ) Re_flush_data( range_encoder );
  }

static inline void Re_shift_low( struct Range_encoder * const range_encoder )
  {
  const uint32_t carry = range_encoder->low >> 32;
  if( range_encoder->low < 0xFF000000U || carry == 1 )
    {
    Re_put_byte( range_encoder, range_encoder->cache + carry );
    for( ; range_encoder->ff_count > 0; --range_encoder->ff_count )
      Re_put_byte( range_encoder, 0xFF + carry );
    range_encoder->cache = range_encoder->low >> 24;
    }
  else ++range_encoder->ff_count;
  range_encoder->low = ( range_encoder->low & 0x00FFFFFFU ) << 8;
  }

static inline void Re_init( struct Range_encoder * const range_encoder,
                            const int ofd )
  {
  range_encoder->low = 0;
  range_encoder->partial_member_pos = 0;
  range_encoder->buffer = (uint8_t *)malloc( re_buffer_size );
  if( !range_encoder->buffer )
    {
    show_error( "Not enough memory. Try a smaller dictionary size.", 0, false );
    cleanup_and_fail( 1 );
    }
  range_encoder->pos = 0;
  range_encoder->range = 0xFFFFFFFFU;
  range_encoder->ff_count = 0;
  range_encoder->outfd = ofd;
  range_encoder->cache = 0;
  }

static inline void Re_free( struct Range_encoder * const range_encoder )
  { free( range_encoder->buffer ); range_encoder->buffer = 0; }

static inline long long Re_member_position( struct Range_encoder * const range_encoder )
  { return range_encoder->partial_member_pos + range_encoder->pos + range_encoder->ff_count; }

static inline void Re_flush( struct Range_encoder * const range_encoder )
  { int i; for( i = 0; i < 5; ++i ) Re_shift_low( range_encoder ); }

static inline void Re_encode( struct Range_encoder * const range_encoder,
                              const int symbol, const int num_bits )
  {
  int i;
  for( i = num_bits - 1; i >= 0; --i )
    {
    range_encoder->range >>= 1;
    if( (symbol >> i) & 1 ) range_encoder->low += range_encoder->range;
    if( range_encoder->range <= 0x00FFFFFFU )
      { range_encoder->range <<= 8; Re_shift_low( range_encoder ); }
    }
  }

static inline void Re_encode_bit( struct Range_encoder * const range_encoder,
                                  Bit_model * const probability, const int bit )
  {
  const uint32_t bound = ( range_encoder->range >> bit_model_total_bits ) * *probability;
  if( !bit )
    {
    range_encoder->range = bound;
    *probability += (bit_model_total - *probability) >> bit_model_move_bits;
    }
  else
    {
    range_encoder->low += bound;
    range_encoder->range -= bound;
    *probability -= *probability >> bit_model_move_bits;
    }
  if( range_encoder->range <= 0x00FFFFFFU )
    { range_encoder->range <<= 8; Re_shift_low( range_encoder ); }
  }

static inline void Re_encode_tree( struct Range_encoder * const range_encoder,
                                   Bit_model bm[], const int symbol, const int num_bits )
  {
  int mask = ( 1 << ( num_bits - 1 ) );
  int model = 1;
  int i;
  for( i = num_bits; i > 0; --i, mask >>= 1 )
    {
    const int bit = ( symbol & mask );
    Re_encode_bit( range_encoder, &bm[model], bit );
    model <<= 1;
    if( bit ) model |= 1;
    }
  }

static inline void Re_encode_tree_reversed( struct Range_encoder * const range_encoder,
                                            Bit_model bm[], int symbol, const int num_bits )
  {
  int model = 1;
  int i;
  for( i = num_bits; i > 0; --i )
    {
    const int bit = symbol & 1;
    Re_encode_bit( range_encoder, &bm[model], bit );
    model = ( model << 1 ) | bit;
    symbol >>= 1;
    }
  }

static inline void Re_encode_matched( struct Range_encoder * const range_encoder,
                                      Bit_model bm[], int symbol, int match_byte )
  {
  int model = 1;
  int i;
  for( i = 7; i >= 0; --i )
    {
    const int match_bit = ( match_byte >> i ) & 1;
    int bit = ( symbol >> i ) & 1;
    Re_encode_bit( range_encoder, &bm[(match_bit<<8)+model+0x100], bit );
    model = ( model << 1 ) | bit;
    if( match_bit != bit )
      {
      while( --i >= 0 )
        {
        bit = ( symbol >> i ) & 1;
        Re_encode_bit( range_encoder, &bm[model], bit );
        model = ( model << 1 ) | bit;
        }
      break;
      }
    }
  }


struct Len_encoder
  {
  Bit_model choice1;
  Bit_model choice2;
  Bit_model bm_low[pos_states][len_low_symbols];
  Bit_model bm_mid[pos_states][len_mid_symbols];
  Bit_model bm_high[len_high_symbols];
  int prices[pos_states][max_len_symbols];
  int len_symbols;
  int counters[pos_states];
  };

static inline void Lee_update_prices( struct Len_encoder * const len_encoder,
                                      const int pos_state )
  {
  int * const pps = len_encoder->prices[pos_state];
  int tmp = price0( len_encoder->choice1 );
  int len = 0;
  for( ; len < len_low_symbols && len < len_encoder->len_symbols; ++len )
    pps[len] = tmp +
               price_symbol( len_encoder->bm_low[pos_state], len, len_low_bits );
  tmp = price1( len_encoder->choice1 );
  for( ; len < len_low_symbols + len_mid_symbols && len < len_encoder->len_symbols; ++len )
    pps[len] = tmp + price0( len_encoder->choice2 ) +
               price_symbol( len_encoder->bm_mid[pos_state], len - len_low_symbols, len_mid_bits );
  for( ; len < len_encoder->len_symbols; ++len )
      /* using 4 slots per value makes "Lee_price" faster */
      len_encoder->prices[3][len] = len_encoder->prices[2][len] =
      len_encoder->prices[1][len] = len_encoder->prices[0][len] =
               tmp + price1( len_encoder->choice2 ) +
               price_symbol( len_encoder->bm_high, len - len_low_symbols - len_mid_symbols, len_high_bits );
  len_encoder->counters[pos_state] = len_encoder->len_symbols;
  }

static inline void Lee_init( struct Len_encoder * const len_encoder,
                             const int len_limit )
  {
  int i, j;
  Bm_init( &len_encoder->choice1 );
  Bm_init( &len_encoder->choice2 );
  for( i = 0; i < pos_states; ++i )
    for( j = 0; j < len_low_symbols; ++j )
      Bm_init( &len_encoder->bm_low[i][j] );
  for( i = 0; i < pos_states; ++i )
    for( j = 0; j < len_mid_symbols; ++j )
      Bm_init( &len_encoder->bm_mid[i][j] );
  for( i = 0; i < len_high_symbols; ++i )
    Bm_init( &len_encoder->bm_high[i] );
  len_encoder->len_symbols = len_limit + 1 - min_match_len;
  for( i = 0; i < pos_states; ++i ) Lee_update_prices( len_encoder, i );
  }

void Lee_encode( struct Len_encoder * const len_encoder,
                 struct Range_encoder * const range_encoder, int symbol,
                 const int pos_state );

static inline int Lee_price( struct Len_encoder * const len_encoder,
                             const int symbol, const int pos_state )
  { return len_encoder->prices[pos_state][symbol - min_match_len]; }


struct Literal_encoder
  {
  Bit_model bm_literal[1<<literal_context_bits][0x300];
  };

static inline int Lie_state( const uint8_t prev_byte )
  { return ( prev_byte >> ( 8 - literal_context_bits ) ); }

static inline void Lie_init( struct Literal_encoder * const literal_encoder )
  {
  int i, j;
  for( i = 0; i < 1<<literal_context_bits; ++i )
    for( j = 0; j < 0x300; ++j )
      Bm_init( &literal_encoder->bm_literal[i][j] );
  }

static inline void Lie_encode( struct Literal_encoder * const literal_encoder,
                               struct Range_encoder * const range_encoder,
                               uint8_t prev_byte, uint8_t symbol )
  { Re_encode_tree( range_encoder, literal_encoder->bm_literal[Lie_state(prev_byte)], symbol, 8 ); }

static inline void Lie_encode_matched( struct Literal_encoder * const literal_encoder,
                                       struct Range_encoder * const range_encoder,
                                       uint8_t prev_byte, uint8_t symbol, uint8_t match_byte )
  { Re_encode_matched( range_encoder, literal_encoder->bm_literal[Lie_state(prev_byte)], symbol, match_byte ); }

static inline int Lie_price_symbol( struct Literal_encoder * const literal_encoder,
                                    uint8_t prev_byte, uint8_t symbol )
  { return price_symbol( literal_encoder->bm_literal[Lie_state(prev_byte)], symbol, 8 ); }

static inline int Lie_price_matched( struct Literal_encoder * const literal_encoder,
                                     uint8_t prev_byte, uint8_t symbol, uint8_t match_byte )
  { return price_matched( literal_encoder->bm_literal[Lie_state(prev_byte)], symbol, match_byte ); }


enum { infinite_price = 0x0FFFFFFF,
       max_marker_size = 16,
       num_rep_distances = 4 };		/* must be 4 */

struct Trial
  {
  State state;
  int dis;
  int prev_index;	/* index of prev trial in trials[] */
  int price;		/* dual use var; cumulative price, match length */
  int reps[num_rep_distances];
  };

static inline void Tr_update( struct Trial * const trial,
                              const int d, const int p_i, const int pr )
  {
  if( pr < trial->price )
    { trial->dis = d; trial->prev_index = p_i; trial->price = pr; }
  }


struct LZ_encoder
  {
  int longest_match_found;
  uint32_t crc_;

  Bit_model bm_match[states][pos_states];
  Bit_model bm_rep[states];
  Bit_model bm_rep0[states];
  Bit_model bm_rep1[states];
  Bit_model bm_rep2[states];
  Bit_model bm_len[states][pos_states];
  Bit_model bm_dis_slot[max_dis_states][1<<dis_slot_bits];
  Bit_model bm_dis[modeled_distances-end_dis_model+1];
  Bit_model bm_align[dis_align_size];

  struct Matchfinder * matchfinder;
  struct Range_encoder range_encoder;
  struct Len_encoder len_encoder;
  struct Len_encoder rep_match_len_encoder;
  struct Literal_encoder literal_encoder;

  int num_dis_slots;
  int match_distances[max_match_len+1];
  struct Trial trials[max_num_trials];

  int dis_slot_prices[max_dis_states][2*max_dictionary_bits];
  int dis_prices[max_dis_states][modeled_distances];
  int align_prices[dis_align_size];
  int align_price_count;
  };

void LZe_fill_align_prices( struct LZ_encoder * const encoder );
void LZe_fill_distance_prices( struct LZ_encoder * const encoder );

static inline uint32_t LZe_crc( struct LZ_encoder * const encoder )
  { return encoder->crc_ ^ 0xFFFFFFFFU; }

       /* move-to-front dis in/into reps */
static inline void LZe_mtf_reps( const int dis, int reps[num_rep_distances] )
  {
  int i;
  if( dis >= num_rep_distances )
    {
    for( i = num_rep_distances - 1; i > 0; --i ) reps[i] = reps[i-1];
    reps[0] = dis - num_rep_distances;
    }
  else if( dis > 0 )
    {
    const int distance = reps[dis];
    for( i = dis; i > 0; --i ) reps[i] = reps[i-1];
    reps[0] = distance;
    }
  }

static inline int LZe_price_rep_len1( struct LZ_encoder * const encoder,
                                      const State state, const int pos_state )
  {
  return price0( encoder->bm_rep0[state] ) + price0( encoder->bm_len[state][pos_state] );
  }

static inline int LZe_price_rep( struct LZ_encoder * const encoder, const int rep,
                                 const State state, const int pos_state )
  {
  int price;
  if( rep == 0 ) return price0( encoder->bm_rep0[state] ) +
                        price1( encoder->bm_len[state][pos_state] );
  price = price1( encoder->bm_rep0[state] );
  if( rep == 1 )
    price += price0( encoder->bm_rep1[state] );
  else
    {
    price += price1( encoder->bm_rep1[state] );
    price += price_bit( encoder->bm_rep2[state], rep - 2 );
    }
  return price;
  }

static inline int LZe_price_dis( struct LZ_encoder * const encoder,
                                 const int dis, const int dis_state )
  {
  if( dis < modeled_distances )
    return encoder->dis_prices[dis_state][dis];
  else
    return encoder->dis_slot_prices[dis_state][get_slot( dis )] +
           encoder->align_prices[dis & (dis_align_size - 1)];
  }

static inline int LZe_price_pair( struct LZ_encoder * const encoder,
                                  const int dis, const int len,
                                  const int pos_state )
  {
  if( len <= min_match_len && dis >= modeled_distances )
    return infinite_price;
  return Lee_price( &encoder->len_encoder, len, pos_state ) +
         LZe_price_dis( encoder, dis, get_dis_state( len ) );
  }

static inline void LZe_encode_pair( struct LZ_encoder * const encoder,
                                    const uint32_t dis, const int len,
                                    const int pos_state )
  {
  const int dis_slot = get_slot( dis );
  Lee_encode( &encoder->len_encoder, &encoder->range_encoder, len, pos_state );
  Re_encode_tree( &encoder->range_encoder,
                  encoder->bm_dis_slot[get_dis_state(len)],
                  dis_slot, dis_slot_bits );

  if( dis_slot >= start_dis_model )
    {
    const int direct_bits = ( dis_slot >> 1 ) - 1;
    const uint32_t base = ( 2 | ( dis_slot & 1 ) ) << direct_bits;
    const uint32_t direct_dis = dis - base;

    if( dis_slot < end_dis_model )
      Re_encode_tree_reversed( &encoder->range_encoder, encoder->bm_dis + base - dis_slot,
                                          direct_dis, direct_bits );
    else
      {
      Re_encode( &encoder->range_encoder, direct_dis >> dis_align_bits, direct_bits - dis_align_bits );
      Re_encode_tree_reversed( &encoder->range_encoder, encoder->bm_align, direct_dis, dis_align_bits );
      if( --encoder->align_price_count <= 0 ) LZe_fill_align_prices( encoder );
      }
    }
  }

static inline int LZe_read_match_distances( struct LZ_encoder * const encoder )
  {
  int len = Mf_longest_match_len( encoder->matchfinder, encoder->match_distances );
  if( len == Mf_match_len_limit( encoder->matchfinder ) )
    len += Mf_true_match_len( encoder->matchfinder, len, encoder->match_distances[len] + 1, max_match_len - len );
  return len;
  }

static inline void LZe_move_pos( struct LZ_encoder * const encoder,
                                 int n, bool skip )
  {
  while( --n >= 0 )
    {
    if( skip ) skip = false;
    else Mf_longest_match_len( encoder->matchfinder, 0 );
    Mf_move_pos( encoder->matchfinder );
    }
  }

static inline void LZe_backward( struct LZ_encoder * const encoder, int cur )
  {
  int * const dis = &encoder->trials[cur].dis;
  while( cur > 0 )
    {
    const int prev_index = encoder->trials[cur].prev_index;
    struct Trial * const prev_trial = &encoder->trials[prev_index];
    prev_trial->price = cur - prev_index;			/* len */
    cur = *dis; *dis = prev_trial->dis; prev_trial->dis = cur;
    cur = prev_index;
    }
  }

int LZe_sequence_optimizer( struct LZ_encoder * const encoder,
                            const int reps[num_rep_distances], const State state );

void LZe_full_flush( struct LZ_encoder * const encoder, const State state );

void LZe_init( struct LZ_encoder * const encoder, struct Matchfinder * const mf,
               const File_header header, const int outfd );

static inline void LZe_free( struct LZ_encoder * const encoder )
  {
  Re_free( &encoder->range_encoder );
  }

bool LZe_encode_member( struct LZ_encoder * const encoder, const long long member_size );

static inline long long LZe_member_position( struct LZ_encoder * const encoder )
  { return Re_member_position( &encoder->range_encoder ); }
