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

#include <utf8/wchar.h>

#include <utf8/limits.h>
#include <utf8/stdlib.h>
#include <stdio.h>

wint_t ungetwc (wint_t wc, FILE* stream)
{
  if (wc == WEOF)
    return WEOF;
  else {
    char buf[MB_LEN_MAX];
    int n = wctomb(buf, wc);
    if (n < 0)
      return WEOF;
    /* glibc allows to ungetc multiple bytes in a row. */
    while (--n >= 0) {
      if (ungetc(buf[n], stream) == EOF) {
        /* If it fails, try to get it right on seekable streams nevertheless. */
        if (fseek(stream,-(n+1),SEEK_CUR) < 0)
          return WEOF;
        else
          break;
      }
    }
    return wc;
  }
}
