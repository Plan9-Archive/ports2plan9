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


#include "printf-args.h"


/* Maximum number of directives in a format string. */
#define MAX_DIRECTIVES	256

/* Flags */
#define FLAG_GROUP	 1	/* ' flag */
#define FLAG_LEFT	 2	/* - flag */
#define FLAG_SHOWSIGN	 4	/* + flag */
#define FLAG_SPACE	 8	/* space flag */
#define FLAG_ALT	16	/* # flag */
#define FLAG_ZERO	32

/* A parsed directive. */
typedef struct {
  const wchar_t* dir_start;
  const wchar_t* dir_end;
  int flags;
  const wchar_t* width_start;
  const wchar_t* width_end;
  int width_arg_index;
  const wchar_t* precision_start;
  const wchar_t* precision_end;
  int precision_arg_index;
  wchar_t conversion; /* d i o u x X f e E g G c s p n % but not C S */
  int arg_index;
} directive;

typedef struct {
  unsigned int count;
  directive dir[MAX_DIRECTIVES];
} directives;


/* Parses the format string. Fills in the number N of directives, and fills
   in directives[0], ..., directives[N-1], and sets directives[N].dir_start
   to the end of the format string. Also fills in the arg_type fields of the
   arguments and the needed count of arguments. */
extern int utf8_wprintf_parse (const wchar_t* format, directives* d, arguments* a);
