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

size_t mbsnrtowcs (wchar_t* dest, const char** srcp, size_t nms, size_t len, mbstate_t* ps)
{
  (void)ps; /* Ignore ps, since there is only the initial state. */
  {
    const char* src = *srcp;
    if (!locale_is_utf8) {
      if (dest != NULL) {
        wchar_t* destptr = dest;
        for (; nms > 0 && len > 0; src++, nms--, destptr++, len--) {
          unsigned char c = (unsigned char) *src;
          *destptr = (wchar_t) c;
          if (c == 0) {
            src = NULL;
            break;
          }
        }
        *srcp = src;
        return destptr-dest;
      } else {
        /* Ignore dest and len. */
        size_t totalcount = 0;
        for (; nms > 0; src++, nms--, totalcount++) {
          unsigned char c = (unsigned char) *src;
          if (c == 0) {
            src = NULL;
            break;
          }
        }
        *srcp = src;
        return totalcount;
      }
    } else {
      if (dest != NULL) {
        wchar_t* destptr = dest;
        for (; nms > 0 && len > 0; destptr++, len--) {
          const char* backup_src = src;
          unsigned char c = (unsigned char) *src;
          if (c < 0x80) {
            *destptr = (wchar_t) c;
            if (c == 0) {
              src = NULL;
              break;
            }
            src++;
            nms--;
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
            if (nms <= count)
              break;
            nms -= count+1;
            src++;
            c = (unsigned char) *src++ ^ 0x80;
            if (!(c < 0x40)) goto bad_input_backup;
            wc |= (wchar_t) c << (6 * --count);
            if (count > 0) {
              if ((u_wchar_t) wc < ((u_wchar_t) 1 << (5 * count + 6)))
                goto bad_input_backup;
              do {
                c = (unsigned char) *src++ ^ 0x80;
                if (!(c < 0x40)) goto bad_input_backup;
                wc |= (wchar_t) c << (6 * --count);
              } while (count > 0);
            }
            *destptr = wc;
          }
          continue;
        bad_input_backup:
          src = backup_src;
          goto bad_input;
        }
        *srcp = src;
        return destptr-dest;
      } else {
        /* Ignore dest and len. */
        size_t totalcount = 0;
        for (; nms > 0; totalcount++) {
          const char* backup_src = src;
          unsigned char c = (unsigned char) *src;
          if (c < 0x80) {
            if (c == 0) {
              src = NULL;
              break;
            }
            src++;
            nms--;
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
            if (nms <= count)
              break;
            nms -= count+1;
            src++;
            c = (unsigned char) *src++ ^ 0x80;
            if (!(c < 0x40)) goto bad_input_backup2;
            wc |= (wchar_t) c << (6 * --count);
            if (count > 0) {
              if ((u_wchar_t) wc < ((u_wchar_t) 1 << (5 * count + 6)))
                goto bad_input_backup2;
              do {
                c = (unsigned char) *src++ ^ 0x80;
                if (!(c < 0x40)) goto bad_input_backup2;
              } while (--count > 0);
            }
          }
          continue;
        bad_input_backup2:
          src = backup_src;
          goto bad_input;
        }
        *srcp = src;
        return totalcount;
      }
    bad_input:
      *srcp = src;
      errno = EILSEQ;
      return (size_t)(-1);
    }
  }
}
