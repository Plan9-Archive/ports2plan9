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

static utf8_mbstate_t internal;

size_t wcsrtombs (char* dest, const wchar_t** srcp, size_t len, mbstate_t* ops)
{
  utf8_mbstate_t* ps = (utf8_mbstate_t*) ops;
  if (ps == NULL)
    ps = &internal;
  {
    const wchar_t* src = *srcp;
    if (!locale_is_utf8) {
      /* Ignore ps, since there is only the initial state. */
      if (dest != NULL) {
        char* destptr = dest;
        for (;; src++) {
          u_wchar_t wc = *src;
          if (wc < 0x100) {
            if (len == 0) {
              *srcp = src;
              break;
            }
            len--;
            *destptr = (unsigned char) wc;
            if (wc == (wchar_t)'\0') {
              *srcp = NULL;
              break;
            }
            destptr++;
          } else {
            *srcp = src;
            errno = EILSEQ;
            return (size_t)(-1);
          }
        }
        return destptr - dest;
      } else {
        /* Ignore dest and len. */
        int totalcount = 0;
        for (;; src++) {
          u_wchar_t wc = *src;
          if (wc < 0x100) {
            if (wc == (wchar_t)'\0')
              break;
            totalcount++;
          } else {
            errno = EILSEQ;
            return (size_t)(-1);
          }
        }
        return totalcount;
      }
    } else {
      if (dest != NULL) {
        char* destptr = dest;
        if (ps->count > 0) {
          unsigned int wc = ps->value;
          size_t count = ps->count;
          do {
            if (len == 0) {
              ps->count = count;
              return destptr - dest;
            }
            len--;
            *destptr++ = (unsigned char)(((wc >> (6 * --count)) & 0x3F) | 0x80);
          } while (count > 0);
          ps->count = 0;
        }
        for (;; src++) {
          u_wchar_t wc = *src;
          size_t count;
          unsigned char c;
          if (wc < 0x80) {
            if (wc == (wchar_t)'\0') {
              if (len == 0) {
                *srcp = src;
                break;
              }
              *destptr = '\0';
              *srcp = NULL;
              break;
            }
            count = 0;
            c = (unsigned char) wc;
          } else if (wc < 0x800) {
            count = 1;
            c = (unsigned char) ((wc >> 6) | 0xC0);
          } else
#if WCHAR_T_BITS == 32
                 if (wc < 0x10000)
#endif
                                   {
            count = 2;
            c = (unsigned char) ((wc >> 12) | 0xE0);
          }
#if WCHAR_T_BITS == 32
            else if (wc < 0x200000) {
            count = 3;
            c = (unsigned char) ((wc >> 18) | 0xF0);
          } else if (wc < 0x4000000) {
            count = 4;
            c = (unsigned char) ((wc >> 24) | 0xF8);
          } else if (wc < 0x80000000) {
            count = 5;
            c = (unsigned char) ((wc >> 30) | 0xFC);
          } else {
            *srcp = src;
            errno = EILSEQ;
            return (size_t)(-1);
          }
#endif
          if (len == 0) {
            *srcp = src;
            break;
          }
          len--;
          *destptr++ = c;
          if (count > 0)
            do {
              if (len == 0) {
                ps->count = count;
                ps->value = wc;
                *srcp = src+1;
                return destptr - dest;
              }
              len--;
              *destptr++ = (unsigned char)(((wc >> (6 * --count)) & 0x3F) | 0x80);
            } while (count > 0);
        }
        return destptr - dest;
      } else {
        /* Ignore dest and len. */
        size_t totalcount = ps->count;
        ps->count = 0;
        for (;; src++) {
          u_wchar_t wc = *src;
          size_t count;
          if (wc < 0x80) {
            if (wc == (wchar_t)'\0') {
              *srcp = NULL;
              break;
            }
            count = 1;
          } else if (wc < 0x800) {
            count = 2;
          } else
#if WCHAR_T_BITS == 32
                 if (wc < 0x10000)
#endif
                                   {
            count = 3;
          }
#if WCHAR_T_BITS == 32
            else if (wc < 0x200000) {
            count = 4;
          } else if (wc < 0x4000000) {
            count = 5;
          } else if (wc < 0x80000000) {
            count = 6;
          } else {
            *srcp = src;
            errno = EILSEQ;
            return (size_t)(-1);
          }
#endif
          totalcount += count;
        }
        return totalcount;
      }
    }
  }
}
