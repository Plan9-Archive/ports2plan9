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
/*
    Return values: 0 for a normal exit, 1 for environmental problems
    (file not found, invalid flags, I/O errors, etc), 2 to indicate a
    corrupt or invalid input file, 3 for an internal consistency error
    (eg, bug) which caused clzip to panic.
*/

#define _FILE_OFFSET_BITS 64

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <utime.h>
#include <sys/stat.h>
#if defined(__MSVCRT__)
#include <io.h>
#define fchmod(x,y) 0
#define fchown(x,y,z) 0
#define SIGHUP SIGTERM
#define S_ISSOCK(x) 0
#define S_IRGRP 0
#define S_IWGRP 0
#define S_IROTH 0
#define S_IWOTH 0
#endif
#if defined(__OS2__)
#include <io.h>
#endif

/* Plan9 hacks */
#define PROGVERSION "1.2"
#define fchmod(x,y) 0
#define fchown(x,y,z) 0
#define S_ISSOCK(x) 0
/* end of plan9 hacks */
/* linking: llabs undefined
in APE stdlib: int abs(int) or labs(long)
*/


#include "carg_parser.h"
#include "clzip.h"
#include "decoder.h"
#include "encoder.h"

#if CHAR_BIT != 8
#error "Environments where CHAR_BIT != 8 are not supported."
#endif

#ifndef LLONG_MAX
#define LLONG_MAX  0x7FFFFFFFFFFFFFFFLL
#endif
#ifndef LLONG_MIN
#define LLONG_MIN  (-LLONG_MAX - 1LL)
#endif
#ifndef ULLONG_MAX
#define ULLONG_MAX 0xFFFFFFFFFFFFFFFFULL
#endif

/* Plan9 APE has abs and labs but not llabs */
/* reference implementation can be found at
/sys/src/ape/lib/ap/gen/abs.c */
long long int llabs( long long int number ) {
	if(number < 0)
			return -number;
	return number;
};


const char * const Program_name = "Clzip";
const char * const program_name = "clzip";
const char * const program_year = "2011";
const char * invocation_name = 0;

#ifdef O_BINARY
const int o_binary = O_BINARY;
#else
const int o_binary = 0;
#endif

struct { const char * from; const char * to; } const known_extensions[] = {
  { ".lz",  ""     },
  { ".tlz", ".tar" },
  { 0,      0      } };

struct Lzma_options
  {
  int dictionary_size;		/* 4KiB..512MiB */
  int match_len_limit;		/* 5..273 */
  };

enum Mode { m_compress, m_decompress, m_test };

char * output_filename = 0;
int outfd = -1;
int verbosity = 0;
mode_t outfd_mode = S_IRUSR | S_IWUSR;
bool delete_output_on_interrupt = false;


/* assure at least a minimum size for buffer `buf' */
static void * resize_buffer( void * buf, const int min_size )
  {
  if( buf ) buf = realloc( buf, min_size );
  else buf = malloc( min_size );
  if( !buf )
    {
    show_error( "Not enough memory.", 0, false );
    cleanup_and_fail( 1 );
    }
  return buf;
  }


static void show_help(void)
  {
  printf( "%s - Data compressor based on the LZMA algorithm.\n", Program_name );
  printf( "\nUsage: %s [options] [files]\n", invocation_name );
  printf( "\nOptions:\n" );
  printf( "  -h, --help                 display this help and exit\n" );
  printf( "  -V, --version              output version information and exit\n" );
  printf( "  -b, --member-size=<n>      set member size limit in bytes\n" );
  printf( "  -c, --stdout               send output to standard output\n" );
  printf( "  -d, --decompress           decompress\n" );
  printf( "  -f, --force                overwrite existing output files\n" );
  printf( "  -F, --recompress           force recompression of compressed files\n" );
  printf( "  -k, --keep                 keep (don't delete) input files\n" );
  printf( "  -m, --match-length=<n>     set match length limit in bytes [36]\n" );
  printf( "  -o, --output=<file>        if reading stdin, place the output into <file>\n" );
  printf( "  -q, --quiet                suppress all messages\n" );
  printf( "  -s, --dictionary-size=<n>  set dictionary size limit in bytes [8MiB]\n" );
  printf( "  -S, --volume-size=<n>      set volume size limit in bytes\n" );
  printf( "  -t, --test                 test compressed file integrity\n" );
  printf( "  -v, --verbose              be verbose (a 2nd -v gives more)\n" );
  printf( "  -1 .. -9                   set compression level [default 6]\n" );
  printf( "      --fast                 alias for -1\n" );
  printf( "      --best                 alias for -9\n" );
  printf( "If no file names are given, %s compresses or decompresses\n", program_name );
  printf( "from standard input to standard output.\n" );
  printf( "Numbers may be followed by a multiplier: k = kB = 10^3 = 1000,\n" );
  printf( "Ki = KiB = 2^10 = 1024, M = 10^6, Mi = 2^20, G = 10^9, Gi = 2^30, etc...\n" );
  printf( "\nReport bugs to lzip-bug@nongnu.org\n" );
  printf( "Clzip home page: http://www.nongnu.org/lzip/clzip.html\n" );
  }


static void show_version(void)
  {
  printf( "%s %s\n", Program_name, PROGVERSION );
  printf( "Copyright (C) %s Antonio Diaz Diaz.\n", program_year );
  printf( "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n" );
  printf( "This is free software: you are free to change and redistribute it.\n" );
  printf( "There is NO WARRANTY, to the extent permitted by law.\n" );
  }


static const char * format_num( long long num )
  {
  const char * const prefix[8] =
    { "Ki", "Mi", "Gi", "Ti", "Pi", "Ei", "Zi", "Yi" };
  enum { buf_size = 16, factor = 1024 };
  static char buf[buf_size];
  const char *p = "";
  int i;

  for( i = 0; i < 8 && ( llabs( num ) > 9999 ||
       ( llabs( num ) >= factor && num % factor == 0 ) ); ++i )
    { num /= factor; p = prefix[i]; }
  snprintf( buf, buf_size, "%lld %s", num, p );
  return buf;
  }


static long long getnum( const char * const ptr,
                         const long long llimit, const long long ulimit )
  {
  long long result;
  char *tail;
  errno = 0;
  result = strtoll( ptr, &tail, 0 );
  if( tail == ptr )
    {
    show_error( "Bad or missing numerical argument.", 0, true );
    exit( 1 );
    }

  if( !errno && tail[0] )
    {
    int factor = ( tail[1] == 'i' ) ? 1024 : 1000;
    int exponent = 0;
    int i;
    bool bad_multiplier = false;
    switch( tail[0] )
      {
      case ' ': break;
      case 'Y': exponent = 8; break;
      case 'Z': exponent = 7; break;
      case 'E': exponent = 6; break;
      case 'P': exponent = 5; break;
      case 'T': exponent = 4; break;
      case 'G': exponent = 3; break;
      case 'M': exponent = 2; break;
      case 'K': if( factor == 1024 ) exponent = 1; else bad_multiplier = true;
                break;
      case 'k': if( factor == 1000 ) exponent = 1; else bad_multiplier = true;
                break;
      default : bad_multiplier = true;
      }
    if( bad_multiplier )
      {
      show_error( "Bad multiplier in numerical argument.", 0, true );
      exit( 1 );
      }
    for( i = 0; i < exponent; ++i )
      {
      if( LLONG_MAX / factor >= llabs( result ) ) result *= factor;
      else { errno = ERANGE; break; }
      }
    }
  if( !errno && ( result < llimit || result > ulimit ) ) errno = ERANGE;
  if( errno )
    {
    show_error( "Numerical argument out of limits.", 0, false );
    exit( 1 );
    }
  return result;
  }


static int get_dict_size( const char * const arg )
  {
  char *tail;
  int bits = strtol( arg, &tail, 0 );
  if( bits >= min_dictionary_bits &&
      bits <= max_dictionary_bits && *tail == 0 )
    return ( 1 << bits );
  return getnum( arg, min_dictionary_size, max_dictionary_size );
  }


static int open_instream( const char * const name, struct stat * const in_statsp,
                          const enum Mode program_mode, const int eindex,
                          const bool recompress, const bool to_stdout )
  {
  int infd = -1;
  if( program_mode == m_compress && !recompress && eindex >= 0 )
    {
    if( verbosity >= 0 )
      fprintf( stderr, "%s: Input file `%s' already has `%s' suffix.\n",
               program_name, name, known_extensions[eindex].from );
    }
  else
    {
    infd = open( name, O_RDONLY | o_binary );
    if( infd < 0 )
      {
      if( verbosity >= 0 )
        fprintf( stderr, "%s: Can't open input file `%s': %s.\n",
                 program_name, name, strerror( errno ) );
      }
    else
      {
      const int i = fstat( infd, in_statsp );
      const mode_t mode = in_statsp->st_mode;
      const bool can_read = ( i == 0 &&
                              ( S_ISBLK( mode ) || S_ISCHR( mode ) ||
                                S_ISFIFO( mode ) || S_ISSOCK( mode ) ) );
      if( i != 0 || ( !S_ISREG( mode ) && ( !to_stdout || !can_read ) ) )
        {
        if( verbosity >= 0 )
          fprintf( stderr, "%s: Input file `%s' is not a regular file%s.\n",
                   program_name, name,
                   ( can_read && !to_stdout ) ?
                   " and `--stdout' was not specified" : "" );
        close( infd );
        infd = -1;
        }
      }
    }
  return infd;
  }


static void set_c_outname( const char * const name, const bool multifile )
  {
  output_filename = resize_buffer( output_filename, strlen( name ) + 5 +
                                   strlen( known_extensions[0].from ) + 1 );
  strcpy( output_filename, name );
  if( multifile ) strcat( output_filename, "00001" );
  strcat( output_filename, known_extensions[0].from );
  }


static int extension_index( const char * const name )
  {
  int i;
  for( i = 0; known_extensions[i].from; ++i )
    {
    const char * const ext = known_extensions[i].from;
    if( strlen( name ) > strlen( ext ) &&
        strncmp( name + strlen( name ) - strlen( ext ), ext, strlen( ext ) ) == 0 )
      return i;
    }
  return -1;
  }


static void set_d_outname( const char * const name, const int i )
  {
  if( i >= 0 )
    {
    const char * const from = known_extensions[i].from;
    if( strlen( name ) > strlen( from ) )
      {
      output_filename = resize_buffer( output_filename, strlen( name ) +
                                       strlen( known_extensions[0].to ) + 1 );
      strcpy( output_filename, name );
      strcpy( output_filename + strlen( name ) - strlen( from ),
              known_extensions[i].to );
      return;
      }
    }
  output_filename = resize_buffer( output_filename, strlen( name ) + 4 + 1 );
  strcpy( output_filename, name );
  strcat( output_filename, ".out" );
  if( verbosity >= 1 )
    fprintf( stderr, "%s: Can't guess original name for `%s' -- using `%s'.\n",
             program_name, name, output_filename );
  }


static bool open_outstream( const bool force )
  {
  int flags = O_CREAT | O_WRONLY | o_binary;
  if( force ) flags |= O_TRUNC; else flags |= O_EXCL;

  outfd = open( output_filename, flags, outfd_mode );
  if( outfd < 0 && verbosity >= 0 )
    {
    if( errno == EEXIST )
      fprintf( stderr, "%s: Output file %s already exists, skipping.\n",
               program_name, output_filename );
    else
      fprintf( stderr, "%s: Can't create output file `%s': %s.\n",
               program_name, output_filename, strerror( errno ) );
    }
  return ( outfd >= 0 );
  }


static bool check_tty( const int infd, const enum Mode program_mode )
  {
  if( program_mode == m_compress && outfd >= 0 && isatty( outfd ) )
    {
    show_error( "I won't write compressed data to a terminal.", 0, true );
    return false;
    }
  if( ( program_mode == m_decompress || program_mode == m_test ) &&
      isatty( infd ) )
    {
    show_error( "I won't read compressed data from a terminal.", 0, true );
    return false;
    }
  return true;
  }


void cleanup_and_fail( const int retval )
  {
  if( delete_output_on_interrupt )
    {
    delete_output_on_interrupt = false;
    if( verbosity >= 0 )
      fprintf( stderr, "%s: Deleting output file `%s', if it exists.\n",
               program_name, output_filename );
    if( outfd >= 0 ) { close( outfd ); outfd = -1; }
    if( remove( output_filename ) != 0 && errno != ENOENT )
      show_error( "WARNING: deletion of output file (apparently) failed.", 0, false );
    }
  exit( retval );
  }


     /* Set permissions, owner and times. */
static void close_and_set_permissions( const struct stat * const in_statsp )
  {
  bool error = false;
  if( in_statsp )
    {
    if( ( fchown( outfd, in_statsp->st_uid, in_statsp->st_gid ) != 0 &&
          errno != EPERM ) ||
        fchmod( outfd, in_statsp->st_mode ) != 0 )
      error = true;
    /* fchown will in many cases return with EPERM, which can be safely ignored. */
    }
  if( close( outfd ) == 0 ) outfd = -1;
  else cleanup_and_fail( 1 );
  delete_output_on_interrupt = false;
  if( !in_statsp ) return;
  if( !error )
    {
    struct utimbuf t;
    t.actime = in_statsp->st_atime;
    t.modtime = in_statsp->st_mtime;
    if( utime( output_filename, &t ) != 0 ) error = true;
    }
  if( error )
    {
    show_error( "Can't change output file attributes.", 0, false );
    cleanup_and_fail( 1 );
    }
  }


static bool next_filename(void)
  {
  const unsigned int len = strlen( known_extensions[0].from );
  int i, j;

  if( strlen( output_filename ) >= len + 5 )		/* "*00001.lz" */
    for( i = strlen( output_filename ) - len - 1, j = 0; j < 5; --i, ++j )
      {
      if( output_filename[i] < '9' ) { ++output_filename[i]; return true; }
      else output_filename[i] = '0';
      }
  return false;
  }


static int compress( const long long member_size, const long long volume_size,
                     const struct Lzma_options * const encoder_options,
                     const int infd, struct Pretty_print * const pp,
                     const struct stat * const in_statsp )
  {
  long long in_size = 0, out_size = 0, partial_volume_size = 0;
  int retval = 0;
  File_header header;
  struct Matchfinder matchfinder;

  if( verbosity >= 1 ) Pp_show_msg( pp, 0 );
  Fh_set_magic( header );
  if( !Fh_set_dictionary_size( header, encoder_options->dictionary_size ) ||
      encoder_options->match_len_limit < min_match_len_limit ||
      encoder_options->match_len_limit > max_match_len )
    internal_error( "invalid argument to encoder" );

  Mf_init( &matchfinder, Fh_get_dictionary_size( header ),
           encoder_options->match_len_limit, infd );
  Fh_set_dictionary_size( header, Mf_dictionary_size( &matchfinder ) );

  while( true )		/* encode one member per iteration */
    {
    struct LZ_encoder encoder;
    const long long size = min(member_size, (volume_size - partial_volume_size));
    LZe_init( &encoder, &matchfinder, header, outfd );
    if( !LZe_encode_member( &encoder, size ) )
      { Pp_show_msg( pp, "Encoder error" ); retval = 1; break; }
    in_size += Mf_data_position( &matchfinder );
    out_size += LZe_member_position( &encoder );
    partial_volume_size += LZe_member_position( &encoder );
    LZe_free( &encoder );
    if( Mf_finished( &matchfinder ) ) break;
    if( partial_volume_size >= volume_size - min_dictionary_size )
      {
      partial_volume_size = 0;
      if( delete_output_on_interrupt )
        {
        close_and_set_permissions( in_statsp );
        if( !next_filename() )
          { Pp_show_msg( pp, "Too many volume files" ); retval = 1; break; }
        if( !open_outstream( true ) ) { retval = 1; break; }
        delete_output_on_interrupt = true;
        }
      }
    Mf_reset( &matchfinder );
    }

  if( retval == 0 && verbosity >= 1 )
    {
    if( in_size <= 0 || out_size <= 0 )
      fprintf( stderr, "No data compressed.\n" );
    else
      fprintf( stderr, "%6.3f:1, %6.3f bits/byte, "
                       "%5.2f%% saved, %lld in, %lld out.\n",
               (double)in_size / out_size,
               ( 8.0 * out_size ) / in_size,
               100.0 * ( 1.0 - ( (double)out_size / in_size ) ),
               in_size, out_size );
    }
  Mf_free( &matchfinder );
  return retval;
  }


static int decompress( const int infd, struct Pretty_print * const pp,
                       const bool testing )
  {
  long long partial_file_pos = 0;
  struct Range_decoder rdec;
  int retval = 0, i, result;
  bool first_member;
  Rd_init( &rdec, infd );

  for( first_member = true; ; first_member = false, Pp_reset( pp ) )
    {
    File_header header;
    struct LZ_decoder decoder;
    Rd_reset_member_position( &rdec );
    for( i = 0; i < Fh_size; ++i )
      header[i] = Rd_get_byte( &rdec );
    if( Rd_finished( &rdec ) )		/* End Of File */
      {
      if( first_member )
        { Pp_show_msg( pp, "Error reading member header" ); retval = 1; }
      break;
      }
    if( !Fh_verify_magic( header ) )
      {
      if( !first_member ) break;		/* trailing garbage */
      Pp_show_msg( pp, "Bad magic number (file not in lzip format)" );
      retval = 2; break;
      }
    if( !Fh_verify_version( header ) )
      {
      if( verbosity >= 0 )
        { Pp_show_msg( pp, 0 );
          fprintf( stderr, "Version %d member format not supported.\n",
                   Fh_version( header ) ); }
      retval = 2; break;
      }
    if( Fh_get_dictionary_size( header ) < min_dictionary_size ||
        Fh_get_dictionary_size( header ) > max_dictionary_size )
      { Pp_show_msg( pp, "Invalid dictionary size in member header" );
        retval = 2; break; }

    if( verbosity >= 2 || ( verbosity == 1 && first_member ) )
      {
      Pp_show_msg( pp, 0 );
      if( verbosity >= 2 )
        fprintf( stderr, "version %d, dictionary size %7sB.  ",
                 Fh_version( header ),
                 format_num( Fh_get_dictionary_size( header ) ) );
      }
    LZd_init( &decoder, header, &rdec, outfd );

    result = LZd_decode_member( &decoder, pp );
    partial_file_pos += Rd_member_position( &rdec );
    LZd_free( &decoder );
    if( result != 0 )
      {
      if( verbosity >= 0 && result <= 2 )
        {
        Pp_show_msg( pp, 0 );
        if( result == 2 )
          fprintf( stderr, "File ends unexpectedly at pos %lld\n",
                   partial_file_pos );
        else
          fprintf( stderr, "Decoder error at pos %lld\n", partial_file_pos );
        }
      retval = 2; break;
      }
    if( verbosity >= 2 )
      { if( testing ) fprintf( stderr, "ok\n" );
        else fprintf( stderr, "done\n" ); }
    }
  Rd_free( &rdec );
  if( verbosity == 1 && retval == 0 )
    { if( testing ) fprintf( stderr, "ok\n" );
      else fprintf( stderr, "done\n" ); }
  return retval;
  }


void signal_handler( int sig )
  {
  sig = 0;			/* keep compiler happy */
  show_error( "Control-C or similar caught, quitting.", 0, false );
  cleanup_and_fail( 1 );
  }


static void set_signals(void)
  {
  signal( SIGHUP, signal_handler );
  signal( SIGINT, signal_handler );
  signal( SIGTERM, signal_handler );
  }


void Pp_init( struct Pretty_print * const pp, const char * const filenames[],
              const int num_filenames, const int v )
  {
  unsigned int stdin_name_len;
  int i;
  pp->name_ = 0;
  pp->stdin_name = "(stdin)";
  pp->longest_name = 0;
  pp->verbosity = v;
  pp->first_post = false;
  stdin_name_len = strlen( pp->stdin_name );

  for( i = 0; i < num_filenames; ++i )
    {
    const char * const s = filenames[i];
    const int len = ( !strcmp( s, "-" ) ? stdin_name_len : strlen( s ) );
    if( len > pp->longest_name ) pp->longest_name = len;
    }
  if( pp->longest_name == 0 ) pp->longest_name = stdin_name_len;
  }


void Pp_show_msg( struct Pretty_print * const pp, const char * const msg )
  {
  if( verbosity >= 0 )
    {
    if( pp->first_post )
      {
      int i, len;
      pp->first_post = false;
      fprintf( stderr, "  %s: ", pp->name_ );
      len = pp->longest_name - strlen( pp->name_ );
      for( i = 0; i < len; ++i ) fprintf( stderr, " " );
      if( !msg ) fflush( stderr );
      }
    if( msg ) fprintf( stderr, "%s.\n", msg );
    }
  }


void show_error( const char * const msg, const int errcode, const bool help )
  {
  if( verbosity >= 0 )
    {
    if( msg && msg[0] )
      {
      fprintf( stderr, "%s: %s", program_name, msg );
      if( errcode > 0 ) fprintf( stderr, ": %s", strerror( errcode ) );
      fprintf( stderr, "\n" );
      }
    if( help && invocation_name && invocation_name[0] )
      fprintf( stderr, "Try `%s --help' for more information.\n",
               invocation_name );
    }
  }


void internal_error( const char * const msg )
  {
  if( verbosity >= 0 )
    fprintf( stderr, "%s: internal error: %s.\n", program_name, msg );
  exit( 3 );
  }


int main( const int argc, const char * const argv[] )
  {
  /* Mapping from gzip/bzip2 style 1..9 compression modes
     to the corresponding LZMA compression modes. */
  const struct Lzma_options option_mapping[] =
    {
    { 1 << 20,   5 },		/* -0 */
    { 1 << 20,   5 },		/* -1 */
    { 3 << 19,   6 },		/* -2 */
    { 1 << 21,   8 },		/* -3 */
    { 3 << 20,  12 },		/* -4 */
    { 1 << 22,  20 },		/* -5 */
    { 1 << 23,  36 },		/* -6 */
    { 1 << 24,  68 },		/* -7 */
    { 3 << 23, 132 },		/* -8 */
    { 1 << 25, 273 } };		/* -9 */
  struct Lzma_options encoder_options = option_mapping[6];  /* default = "-6" */
  long long member_size = LLONG_MAX;
  long long volume_size = LLONG_MAX;
  const char * input_filename = "";
  const char * default_output_filename = "";
  const char ** filenames = 0;
  int num_filenames = 0;
  int infd = -1;
  enum Mode program_mode = m_compress;
  int argind = 0;
  int retval = 0;
  int i;
  bool filenames_given = false;
  bool force = false;
  bool keep_input_files = false;
  bool recompress = false;
  bool to_stdout = false;
  struct Pretty_print pp;

  const struct ap_Option options[] =
    {
    { '0', "fast",            ap_no  },
    { '1',  0,                ap_no  },
    { '2',  0,                ap_no  },
    { '3',  0,                ap_no  },
    { '4',  0,                ap_no  },
    { '5',  0,                ap_no  },
    { '6',  0,                ap_no  },
    { '7',  0,                ap_no  },
    { '8',  0,                ap_no  },
    { '9', "best",            ap_no  },
    { 'b', "member-size",     ap_yes },
    { 'c', "stdout",          ap_no  },
    { 'd', "decompress",      ap_no  },
    { 'e', "extreme",         ap_no  },
    { 'f', "force",           ap_no  },
    { 'F', "recompress",      ap_no  },
    { 'h', "help",            ap_no  },
    { 'k', "keep",            ap_no  },
    { 'm', "match-length",    ap_yes },
    { 'o', "output",          ap_yes },
    { 'q', "quiet",           ap_no  },
    { 's', "dictionary-size", ap_yes },
    { 'S', "volume-size",     ap_yes },
    { 't', "test",            ap_no  },
    { 'v', "verbose",         ap_no  },
    { 'V', "version",         ap_no  },
    {  0 ,  0,                ap_no  } };

  struct Arg_parser parser;

  invocation_name = argv[0];
  CRC32_init();
  if( !ap_init( &parser, argc, argv, options, 0 ) )
    { show_error( "Memory exhausted.", 0, false ); return 1; }
  if( ap_error( &parser ) )				/* bad option */
    { show_error( ap_error( &parser ), 0, true ); return 1; }

  for( ; argind < ap_arguments( &parser ); ++argind )
    {
    const int code = ap_code( &parser, argind );
    const char * const arg = ap_argument( &parser, argind );
    if( !code ) break;				/* no more options */
    switch( code )
      {
      case '0':
      case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
                encoder_options = option_mapping[code-'0']; break;
      case 'b': member_size = getnum( arg, 100000, LLONG_MAX / 2 ); break;
      case 'c': to_stdout = true; break;
      case 'd': program_mode = m_decompress; break;
      case 'e': break;				/* ignored by now */
      case 'f': force = true; break;
      case 'F': recompress = true; break;
      case 'h': show_help(); return 0;
      case 'k': keep_input_files = true; break;
      case 'm': encoder_options.match_len_limit =
                  getnum( arg, min_match_len_limit, max_match_len ); break;
      case 'o': default_output_filename = arg; break;
      case 'q': verbosity = -1; break;
      case 's': encoder_options.dictionary_size = get_dict_size( arg );
                break;
      case 'S': volume_size = getnum( arg, 100000, LLONG_MAX / 2 ); break;
      case 't': program_mode = m_test; break;
      case 'v': if( verbosity < 4 ) ++verbosity; break;
      case 'V': show_version(); return 0;
      default : internal_error( "uncaught option" );
      }
    } /* end process options */

#if defined(__MSVCRT__) || defined(__OS2__)
  _setmode( STDIN_FILENO, O_BINARY );
  _setmode( STDOUT_FILENO, O_BINARY );
#endif

  for( ; argind < ap_arguments( &parser ); ++argind )
    {
    if( strcmp( ap_argument( &parser, argind ), "-" ) )
      filenames_given = true;
    ++num_filenames;
    filenames = resize_buffer( filenames, num_filenames * sizeof (char *) );
    filenames[num_filenames-1] = ap_argument( &parser, argind );
    }

  if( num_filenames == 0 )
    {
    ++num_filenames;
    filenames = resize_buffer( filenames, sizeof (char *) );
    filenames[num_filenames-1] = "-";
    }
  if( !to_stdout && program_mode != m_test &&
      ( filenames_given || default_output_filename[0] ) )
    set_signals();

  Pp_init( &pp, filenames, num_filenames, verbosity );
  if( program_mode == m_test )
    outfd = -1;
  else if( program_mode == m_compress )
    {
    Dis_slots_init();
    Prob_prices_init();
    }

  output_filename = resize_buffer( output_filename, 1 );
  for( i = 0; i < num_filenames; ++i )
    {
    int tmp;
    struct stat in_stats;
    const struct stat * in_statsp;
    output_filename[0] = 0;

    if( !filenames[i][0] || !strcmp( filenames[i], "-" ) )
      {
      input_filename = "";
      infd = STDIN_FILENO;
      if( program_mode != m_test )
        {
        if( to_stdout || !default_output_filename[0] )
          outfd = STDOUT_FILENO;
        else
          {
          if( program_mode == m_compress )
            set_c_outname( default_output_filename, volume_size != LLONG_MAX );
          else
            {
            output_filename = resize_buffer( output_filename,
                                             strlen( default_output_filename ) + 1 );
            strcpy( output_filename, default_output_filename );
            }
          outfd_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
          if( !open_outstream( force ) )
            {
            if( outfd == -1 && retval < 1 ) retval = 1;
            close( infd ); infd = -1;
            continue;
            }
          }
        }
      }
    else
      {
      const int eindex = extension_index( filenames[i] );
      input_filename = filenames[i];
      infd = open_instream( input_filename, &in_stats, program_mode,
                            eindex, recompress, to_stdout );
      if( infd < 0 ) { if( retval < 1 ) retval = 1; continue; }
      if( program_mode != m_test )
        {
        if( to_stdout ) outfd = STDOUT_FILENO;
        else
          {
          if( program_mode == m_compress )
            set_c_outname( input_filename, volume_size != LLONG_MAX );
          else set_d_outname( input_filename, eindex );
          outfd_mode = S_IRUSR | S_IWUSR;
          if( !open_outstream( force ) )
            {
            if( outfd == -1 && retval < 1 ) retval = 1;
            close( infd ); infd = -1;
            continue;
            }
          }
        }
      }

    if( !check_tty( infd, program_mode ) ) return 1;

    if( output_filename[0] && !to_stdout && program_mode != m_test )
      delete_output_on_interrupt = true;
    in_statsp = input_filename[0] ? &in_stats : 0;
    Pp_set_name( &pp, input_filename );
    if( program_mode == m_compress )
      tmp = compress( member_size, volume_size, &encoder_options, infd,
                      &pp, in_statsp );
    else
      tmp = decompress( infd, &pp, program_mode == m_test );
    if( tmp > retval ) retval = tmp;
    if( tmp && program_mode != m_test ) cleanup_and_fail( retval );

    if( delete_output_on_interrupt )
      close_and_set_permissions( in_statsp );
    if( input_filename[0] )
      {
      close( infd ); infd = -1;
      if( !keep_input_files && !to_stdout && program_mode != m_test )
        remove( input_filename );
      }
    }
  if( outfd >= 0 && close( outfd ) != 0 )
    {
    show_error( "Can't close stdout", errno, false );
    if( retval < 1 ) retval = 1;
    }
  free( output_filename );
  free( filenames );
  ap_free( &parser );
  return retval;
  }
