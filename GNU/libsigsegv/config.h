/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* The name of the include file describing the fault handler. */
#define CFG_FAULT "fault-none.h"

/* The name of the file implementing the handler functionality. */
#define CFG_HANDLER "handler-none.c"

/* The name of the file implementing sigsegv_reset_onstack_flag. */
#define CFG_LEAVE "leave-none.c"

/* The name of the include file describing the Mach fault handler. */
#define CFG_MACHFAULT "fault-none.h"

/* The name of the include file describing the fault signals. */
#define CFG_SIGNALS "signals.h"

/* The name of the file determining the stack virtual memory area. */
#define CFG_STACKVMA "stackvma-none.c"

/* Define to 1 if attempting to make system calls fail with error EFAULT */
/* #undef ENABLE_EFAULT */

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if system calls detect invalid memory references and return
   error EFAULT. */
/* #undef HAVE_EFAULT_SUPPORT */

/* Define if getpagesize() is available as a function or a macro. */
/* #undef HAVE_GETPAGESIZE */

/* Define to 1 if you have the `getrlimit' function. */
/* #undef HAVE_GETRLIMIT */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define to 1 if you have the `mincore' function. */
/* #undef HAVE_MINCORE */

/* Define if <sys/mman.h> defines MAP_ANON and mmaping with MAP_ANON works. */
/* #undef HAVE_MMAP_ANON */

/* Define if <sys/mman.h> defines MAP_ANONYMOUS and mmaping with MAP_ANONYMOUS
   works. */
/* #undef HAVE_MMAP_ANONYMOUS */

/* Define if mmaping of the special device /dev/zero works. */
/* #undef HAVE_MMAP_DEVZERO */

/* Define to 1 if you have the `mquery' function. */
/* #undef HAVE_MQUERY */

/* Define if PAGESIZE is available as a macro. */
/* #undef HAVE_PAGESIZE */

/* Define to 1 if you have the `setrlimit' function. */
/* #undef HAVE_SETRLIMIT */

/* Define to 1 if you have the `sigaltstack' function. */
/* #undef HAVE_SIGALTSTACK */

/* Define if CFG_STACKVMA is set to a nontrivial source file. */
/* #undef HAVE_STACKVMA */

/* Define to 1 if you have the <stdint.h> header file. */
/* #undef HAVE_STDINT_H */

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define if sysconf(_SC_PAGESIZE) is available as a function or a macro. */
/* #undef HAVE_SYSCONF_PAGESIZE */

/* Define to 1 if you have the <sys/signal.h> header file. */
/* #undef HAVE_SYS_SIGNAL_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <ucontext.h> header file. */
/* #undef HAVE_UCONTEXT_H */

/* Define to 1 if the system has the type `uintptr_t'. */
#define HAVE_UINTPTR_T 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if you have the sigaltstack() function and it works. */
/* #undef HAVE_WORKING_SIGALTSTACK */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 on Cygwin versions older than 1.7. */
/* #undef OLD_CYGWIN_WORKAROUND */

/* Name of package */
#define PACKAGE "libsigsegv"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define if sigaltstack() interprets the stack_t.ss_sp field incorrectly, as
   the highest address of the alternate stack range rather than as the lowest
   address. */
/* #undef SIGALTSTACK_SS_REVERSED */

/* Define as the direction of stack growth for your system. STACK_DIRECTION >
   0 => grows toward higher addresses STACK_DIRECTION < 0 => grows toward
   lower addresses STACK_DIRECTION = 0 => spaghetti stack. */
#define STACK_DIRECTION -1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "2.10"

/* Define to 'struct sigaltstack' if that's the type of the argument to
   sigaltstack */
/* #undef stack_t */

/* Define to the type of an unsigned integer type wide enough to hold a
   pointer, if such a type exists, and if the system does not define it. */
/* #undef uintptr_t */
