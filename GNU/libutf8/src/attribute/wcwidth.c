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

#include <utf8/wctype.h>
#include <utf8/locale.h>
#include "nonspacing.h"

#if defined(LIBUTF8_PLUG) && defined(__sun)
int wcwidth (const wchar_t c)
#else
int wcwidth (wint_t c)
#endif
{
  if (c == (wchar_t)'\0')
    return 0;
  if (!iswprint(c))
    return -1;
  if (!locale_is_utf8) {
    return 1;
  } else {
    /* Test for non-spacing (combining) character. */
    if ((unsigned int) c <= 0xffffu) {
      unsigned int u = (unsigned int) c;
      const unsigned char * page = nonspacing_table[u >> 10];
      if (page != NULL && (page[(u >> 3) & 127] & (1 << (u & 7))) != 0)
        return 0;
    }
    /* Generated from "grep '^....;[WF]' EastAsianWidth.txt"
       and            "grep '^....;[^WF]' EastAsianWidth.txt" */
    if (c >= 0x1100
        && ((c < 0x1160) /* Hangul Jamo */
            || (c >= 0x2e80 && c < 0xa4d0  /* CJK ... Yi */
                && !((c & ~0x0011) == 0x300a || c == 0x303f))
            || (c >= 0xac00 && c < 0xd7a4) /* Hangul Syllables */
            || (c >= 0xf900 && c < 0xfb00) /* CJK Compatibility Ideographs */
            || (c >= 0xfe30 && c < 0xfe70) /* CJK Compatibility Forms */
            || (c >= 0xff00 && c < 0xff60) /* Fullwidth Forms */
            || (c >= 0xffe0 && c < 0xffe7)
       )   )
      return 2;
    return 1;
  }
}
