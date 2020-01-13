/* Copyright (C) 1999 Free Software Foundation, Inc.
   This file is part of the GNU UTF-8 Library.

   The GNU UTF-8 Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU UTF-8 Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU UTF-8 Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */


#include "config.h"  /* for LIBUTF8_HAVE_* macros */
#include <utf8/wchar.h>
#include <stdarg.h>


/* Maximum number of arguments. */
#define MAX_ARGUMENTS	256

/* Argument types */
typedef enum {
  TYPE_NONE,
  TYPE_SCHAR,
  TYPE_UCHAR,
  TYPE_SHORT,
  TYPE_USHORT,
  TYPE_INT,
  TYPE_UINT,
  TYPE_LONGINT,
  TYPE_ULONGINT,
#ifdef HAVE_LONG_LONG
  TYPE_LONGLONGINT,
  TYPE_ULONGLONGINT,
#endif
  TYPE_DOUBLE,
#ifdef HAVE_LONG_DOUBLE
  TYPE_LONGDOUBLE,
#endif
  TYPE_CHAR,
  TYPE_WIDE_CHAR,
  TYPE_STRING,
  TYPE_WIDE_STRING,
  TYPE_POINTER,
  TYPE_COUNT_SCHAR_POINTER,
  TYPE_COUNT_SHORT_POINTER,
  TYPE_COUNT_INT_POINTER,
  TYPE_COUNT_LONGINT_POINTER
#ifdef HAVE_LONG_LONG
 ,TYPE_COUNT_LONGLONGINT_POINTER
#endif
} arg_type;

/* Polymorphic argument */
typedef struct {
  arg_type type;
  union {
    signed char			a_schar;
    unsigned char		a_uchar;
    short			a_short;
    unsigned short		a_ushort;
    int				a_int;
    unsigned int		a_uint;
    long int			a_longint;
    unsigned long int		a_ulongint;
#ifdef HAVE_LONG_LONG
    long long int		a_longlongint;
    unsigned long long int	a_ulonglongint;
#endif
    float			a_float;
    double			a_double;
#ifdef HAVE_LONG_DOUBLE
    long double			a_longdouble;
#endif
    int				a_char;
    wint_t			a_wide_char;
    const char*			a_string;
    const wchar_t*		a_wide_string;
    void*			a_pointer;
    signed char *		a_count_schar_pointer;
    short *			a_count_short_pointer;
    int *			a_count_int_pointer;
    long int *			a_count_longint_pointer;
#ifdef HAVE_LONG_LONG
    long long int *		a_count_longlongint_pointer;
#endif
  } a;
} argument;

typedef struct {
  unsigned int count;
  argument arg[MAX_ARGUMENTS];
} arguments;


/* Fetch the arguments, putting them into a. */
extern int utf8_printf_fetchargs (va_list args, arguments* a);
