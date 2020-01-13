/* Copyright (C) 1999-2000 Free Software Foundation, Inc.
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

#include <utf8/wchar.h>

#include <utf8/stdlib.h>
#include <string.h>
#include <stdio.h>

wint_t fgetwc (FILE* stream)
{
  wchar_t wc;
  mbstate_t state;
  char buf[1];
  memset(&state, 0, sizeof(mbstate_t));
  for (;;) {
    int c = getc(stream);
    if (c == EOF)
      return WEOF;
    buf[0] = (unsigned char) c;
    switch (mbrtowc(&wc, buf, 1, &state)) {
      case (size_t)(-2): break;
      case (size_t)(-1): return WEOF;
      default: return wc;
    }
  }
}
