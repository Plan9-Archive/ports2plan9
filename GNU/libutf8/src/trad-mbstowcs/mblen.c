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

#include <utf8/stdlib.h>

#include <utf8/locale.h>
#include <utf8/wchar.h>

int mblen (const char* s, size_t n)
{
#if 0
  /* Do the equivalent of mbtowc(NULL, s, n). */
  mbstate_t state;
  /* If s == NULL, mbrtowc will return 0, which is what we want, because
     the encoding is not state dependent. */
  int result = mbrtowc(NULL, s, n, &state);
  if (result >= 0)
    return result;
  else
    return -1;
#else /* Avoid a function call. */
  if (s == NULL) {
    return 0;
  } else {
    if (n == 0)
      return -1;
    if (!locale_is_utf8) {
      unsigned char c = (unsigned char) *s;
      return (c != 0);
    } else {
      unsigned char c;
      c = (unsigned char) *s;
      if (c < 0x80) {
        return (c != 0);
      } else if (c < 0xC0) {
        /* Spurious 10XXXXXX byte is invalid. */
        goto bad_input;
      } else {
        const char* start = s;
        size_t count;
        int check_unsafe;
        if (c < 0xE0) {
          count = 1;
          if (c < 0xC2) goto bad_input;
          check_unsafe = 0;
        } else if (c < 0xF0) {
          count = 2;
          check_unsafe = (c == 0xE0);
        }
#if WCHAR_T_BITS == 32
          else if (c < 0xF8) {
          count = 3;
          check_unsafe = (c == 0xF0);
        } else if (c < 0xFC) {
          count = 4;
          check_unsafe = (c == 0xF8);
        } else if (c < 0xFE) {
          count = 5;
          check_unsafe = (c == 0xFC);
        }
#endif
          else goto bad_input;
        if (n <= count)
          return -1;
        s++;
        c = (unsigned char) *s++ ^ 0x80;
        if (!(c < 0x40)) goto bad_input;
        if (--count > 0) {
          if (check_unsafe && ((c >> (6 - count)) == 0)) goto bad_input;
          do {
            c = (unsigned char) *s++ ^ 0x80;
            if (!(c < 0x40)) goto bad_input;
          } while (--count > 0);
        }
        return s - start;
      }
    }
  }
bad_input:
  errno = EILSEQ;
  return -1;
#endif
}
