/* config.h.in.  Generated from configure.in by autoheader.  */
/* config.h manually edited to fit Plan9/APE */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 0

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
#define HAVE_DOPRNT 0

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define HAVE_MALLOC 0

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 0

/* Define to 1 if you have the `open' function. */
#define HAVE_OPEN 1

/* Define to 1 if your system has a GNU libc compatible `realloc' function,
   and to 0 otherwise. */
#define HAVE_REALLOC 0

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 0

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 0

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 0

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 0

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 0

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vasprintf' function. */
#define HAVE_VASPRINTF 0

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `vsyslog' function. */
#define HAVE_VSYSLOG 0

/* Name of package */
#define PACKAGE json-c

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#define PACKAGE_NAME json-c

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "json-c 0.9"

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the version of this package. */
#define PACKAGE_VERSION 0.9

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION 0.9

/* Define to empty if `const' does not conform to ANSI C. */
#undef const

/* Define to rpl_malloc if the replacement function should be used. */
#define malloc rpl_malloc

/* Define to rpl_realloc if the replacement function should be used. */
#define realloc rpl_realloc

/* Define to `unsigned int' if <sys/types.h> does not define. */
#undef size_t

/*hacking: trying to avoid compilation errors */

/* in json_object.c row 31: 
#define REFCOUNT_DEBUG 0
ended up commenting out every ifdef for this debug in the sources.
*/

/* in json_tokener.c
error related to MC_DEBUG that can be found in debug.h
The error indicates that pcc gets confused by ##__VA_ARGS__
changed them all to plain __VA_ARGS__.
*/

#define MC_MANTAINER_MODE 1 /* needed? only seen in debug.h */

/* printbuf.c demands that stdarg.h is present on the system so compilation with HAVE_STDARG_H 0 fails at row 21. 
because of this stdarg.h is copied from opensource.apple.com if it ever gets needed.
after commenting out the hard dependency of HAVE_STDARG_H, two errors cropped up relating to a type incompatibility where chars(int) = vsnprintf(void)
After some swearing I found that stdio.h defines both an extern int vsnprintf and an extern void vsnprintf, which can be defined with _C99_SNPRINTF_EXTENSION.
*/




