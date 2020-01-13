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

#include <utf8/stdlib.h>

#include <utf8/locale.h>

int wctomb (char* s, wchar_t swc)
{
  u_wchar_t wc = swc; /* since we don't know whether wchar_t is unsigned */
  if (s == NULL)
    return 0; /* we have no state dependent encodings */
  if (!locale_is_utf8) {
    /* Ignore ps, since there is only the initial state. */
    if (wc < 0x100) {
      *s = (unsigned char) wc;
      return 1;
    } else {
      return -1;
    }
  } else {
    size_t count;
    int result;
    if (wc < 0x80) {
      *s = (unsigned char) wc;
      return 1;
    }
    if (wc < 0x800) {
      count = 1;
      *s = (unsigned char) ((wc >> 6) | 0xC0);
    } else
#if WCHAR_T_BITS == 32
           if (wc < 0x10000)
#endif
                             {
      count = 2;
      *s = (unsigned char) ((wc >> 12) | 0xE0);
    }
#if WCHAR_T_BITS == 32
      else if (wc < 0x200000) {
      count = 3;
      *s = (unsigned char) ((wc >> 18) | 0xF0);
    } else if (wc < 0x4000000) {
      count = 4;
      *s = (unsigned char) ((wc >> 24) | 0xF8);
    } else if (wc < 0x80000000) {
      count = 5;
      *s = (unsigned char) ((wc >> 30) | 0xFC);
    } else {
      return -1;
    }
#endif
    result = count + 1;
    do {
      *++s = (unsigned char)(((wc >> (6 * --count)) & 0x3F) | 0x80);
    } while (count > 0);
    return result;
  }
}
