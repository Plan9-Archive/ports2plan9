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

#include "integer-parse.h"

#include <utf8/wctype.h>

const wchar_t* utf8_integer_parse (const wchar_t* nptr, int base)
{
  const wchar_t* ptr;

  ptr = nptr;

  /* Skip optional plus or minus sign. */
  if (*ptr == '+' || *ptr == '-')
    ptr++;
  if (base == 0) {
    /* Skip either of
         [0] [0-7]*
         [0] [xX] [0-9A-Fa-f]+
         [1-9] [0-9]*
     */
    if (*ptr == '0') {
      ptr++;
      if (towlower(*ptr) == 'x') {
        const wchar_t* start = (ptr += 1);
        for (; *ptr != (wchar_t)'\0' && iswdigit(*ptr); ptr++);
        if (ptr > start)
          ; /* OK, keep ptr */
        else
          /* Go back to the 'x'. */
          ptr = start - 1;
      } else {
        for (; *ptr >= '0' && *ptr <= '7'; ptr++);
      }
    } else if (iswdigit(*ptr)) {
      ptr++;
      for (; *ptr != (wchar_t)'\0' && iswdigit(*ptr); ptr++);
    } else
      ptr = nptr;
    /* FIXME: ISO C 99 seems to indicate that we should also eat a possible
       L LL U UL ULL LU LLU postfix, but glibc-2.1 does not do this. */
  } else if (base == 16) {
    /* Skip ( [0] [xX] | ) [0-9A-Fa-f]+ */
    if (*ptr == '0' && towlower(ptr[1]) == 'x') {
      const wchar_t* start = (ptr += 2);
      for (; *ptr != (wchar_t)'\0' && iswxdigit(*ptr); ptr++);
      if (ptr > start)
        ; /* OK, keep ptr */
      else
        /* Go back to the 'x'. */
        ptr = start - 1;
    } else {
      const wchar_t* start = ptr;
      for (; *ptr != (wchar_t)'\0' && iswxdigit(*ptr); ptr++);
      if (ptr > start)
        ; /* OK, keep ptr */
      else
        ptr = nptr;
    }
  } else if (base >= 2 && base <= 36) {
    /* Skip [digit<base]+ */
    const wchar_t* start = ptr;
    if (base <= 10)
      for (; *ptr != (wchar_t)'\0' && (*ptr >= '0' && *ptr < '0'+base); ptr++);
    else
      for (; *ptr != (wchar_t)'\0' && ((*ptr >= '0' && *ptr <= '9') || (*ptr >= 'A' && *ptr < 'A'-10+base) || (*ptr >= 'a' && *ptr < 'a'-10+base)); ptr++);
    if (ptr > start)
      ; /* OK, keep ptr */
    else
      ptr = nptr;
  } else
    ptr = nptr;
  return ptr;
}
