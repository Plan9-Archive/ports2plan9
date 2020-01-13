/* manually generated from grepping sources to find important conditionals */

#define HAVE_INTTYPES_H 1
#define HAVE_UINT32_T 1
#define HAVE_UINT16_T 1
#define HAVE_INT16_T 1
#define HAVE_UINT8_T 1
#define HAVE_INT8_T 1

#define HAVE_UNISTD_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_STDLIB_H 1
#define STDC_HEADERS 1

#define HAVE_UTIME 1
#define HAVE_GMTIME_R 1
#define HAVE_LOCALTIME_R 1

#define HAVE_DECL_STRERROR_R 1
#define STRERROR_R_CHAR_P 1

#define SQLITE_VERSION "3.7.15.1"

#define DNDEBUG 1
#define SQLITE_THREADSAFE 1

#define SQLITE_SYSTEM_MALLOC 1
#define SQLITE_HAVE_ISNAN 1
#define SQLITE_OMIT_FLOATING_POINT 1 /* causes build to crash */
#define SQLITE_OMIT_LOAD_EXTENSION 1
#define SQLITE_OMIT_WAL 1 /* we don't have sys/mman.h */
#define SQLITE_OMIT_TRACE 1

/* #define SQLITE_ASCII */

/* mostly about right...*/
#define st_blksize st_size/512

/*
linking errors:
open_db: undefined: sqlite3_enable_load_extension
do_meta_command: undefined: sqlite3_load_extension
do_meta_command: undefined: sqlite3_trace
posixFchown: undefined: fchown
*/
#include <sys/types.h>
/* stubs */
int fchown(int x, uid_t y, gid_t z) {
	return 0;
}

/* the other functions get defined in sqlite3.h since they are called in sqlite-dependent prograps */

#define SQLITE_API











