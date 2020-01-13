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

#include <utf8/locale.h>
#include <errno.h>

size_t mbrtowc (wchar_t* pwc, const char* s, size_t n, mbstate_t* ps)
{
  (void)ps; /* Ignore ps, since there is only the initial state. */
  if (s == NULL) {
    return 0;
  } else {
    const char* start = s;
    if (n == 0)
      return (size_t)(-2);
    if (!locale_is_utf8) {
      unsigned char c = (unsigned char) *s;
      if (pwc != NULL)
        *pwc = (wchar_t) c;
      return (c != 0);
    } else {
      unsigned char c;
      c = (unsigned char) *s;
      if (c < 0x80) {
        if (pwc != NULL)
          *pwc = (wchar_t) c;
        return (c != 0);
      } else if (c < 0xC0) {
        /* Spurious 10XXXXXX byte is invalid. */
        goto bad_input;
      } else {
        wchar_t wc;
        size_t count;
        if (c < 0xE0) {
          wc = (wchar_t)(c & 0x1F) << 6;
          count = 1;
          if (c < 0xC2) goto bad_input;
        } else if (c < 0xF0) {
          wc = (wchar_t)(c & 0x0F) << 12;
          count = 2;
        }
#if WCHAR_T_BITS == 32
          else if (c < 0xF8) {
          wc = (wchar_t)(c & 0x07) << 18;
          count = 3;
        } else if (c < 0xFC) {
          wc = (wchar_t)(c & 0x03) << 24;
          count = 4;
        } else if (c < 0xFE) {
          wc = (wchar_t)(c & 0x01) << 30;
          count = 5;
        }
#endif
          else goto bad_input;
        if (n <= count)
          return (size_t)(-2);
        s++;
        c = (unsigned char) *s++ ^ 0x80;
        if (!(c < 0x40)) goto bad_input;
        wc |= (wchar_t) c << (6 * --count);
        if (count > 0) {
          if ((u_wchar_t) wc < ((u_wchar_t) 1 << (5 * count + 6)))
            goto bad_input;
          do {
            c = (unsigned char) *s++ ^ 0x80;
            if (!(c < 0x40)) goto bad_input;
            wc |= (wchar_t) c << (6 * --count);
          } while (count > 0);
        }
        if (pwc != NULL)
          *pwc = wc;
        return s - start;
      }
    }
  }
bad_input:
  errno = EILSEQ;
  return (size_t)(-1);
}
