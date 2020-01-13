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

#include "number-parse.h"

#include <utf8/wctype.h>
#include <utf8/stdlib.h>
#ifdef HAVE_LANGINFO_H
#include <langinfo.h>
#else
#include <locale.h>
#endif
#include <string.h>

#if !defined(DECIMAL_POINT) && defined(RADIXCHAR)
#define DECIMAL_POINT RADIXCHAR
#endif

const wchar_t* utf8_number_parse (const wchar_t* nptr)
{
  const wchar_t* ptr;
  wchar_t decimal_point;

  {
    const char * decimal_string =
#ifdef HAVE_LANGINFO_H
      nl_langinfo(DECIMAL_POINT);
#else
      localeconv()->decimal_point;
#endif
    if (!(decimal_string != NULL
          && (mbtowc(NULL,NULL,0), mbtowc(&decimal_point,decimal_string,strlen(decimal_string)) > 0)))
      decimal_point = '.';
  }

  ptr = nptr;

  /* Skip optional plus or minus sign. */
  if (*ptr == '+' || *ptr == '-')
    ptr++;
  /* Skip either of
       ([0-9]* [.] [0-9]+ | [0-9]+ [.]) ( [Ee] ([+-]|) [0-9]+ | )
       [0] [xX] ([0-9A-Fa-f]* [.] [0-9A-Fa-f]+ | [0-9A-Fa-f]+ [.]) ( [Pp] ([+-]|) [0-9]+ | )
       [Ii][Nn][Ff] ( [Ii][Nn][Ii][Tt][Yy] | )
       [Nn][Aa][Nn] ( [(] [0-9A-Za-z_]* [)] | )
   */
  if (*ptr == '0' && towlower(ptr[1]) == 'x') {
    const wchar_t* start_mantissa = (ptr += 2);
    int nonempty_mantissa;
    for (; *ptr != (wchar_t)'\0' && iswxdigit(*ptr); ptr++);
    if (*ptr != (wchar_t)'\0' && *ptr == decimal_point) {
      ptr++;
      for (; *ptr != (wchar_t)'\0' && iswxdigit(*ptr); ptr++);
      nonempty_mantissa = (ptr - start_mantissa > 1);
    } else
      nonempty_mantissa = (ptr - start_mantissa > 0);
    if (nonempty_mantissa) {
      const wchar_t* end_mantissa = ptr;
      if (towlower(*ptr) == 'p') {
        const wchar_t* start_exponent;
        int nonempty_exponent;
        ptr++;
        if (*ptr == '+' || *ptr == '-')
          ptr++;
        start_exponent = ptr;
        for (; *ptr != (wchar_t)'\0' && iswdigit(*ptr); ptr++);
        nonempty_exponent = (ptr - start_exponent > 0);
        if (nonempty_exponent)
          ; /* OK, keep ptr */
        else
          ptr = end_mantissa;
      }
      /* Now keep ptr */
    } else
      /* Go back to the 'x'. */
      ptr = start_mantissa - 1;
    goto parse_done;
  }
  if (iswdigit(*ptr) || *ptr == decimal_point) {
    const wchar_t* start_mantissa = ptr;
    int nonempty_mantissa;
    for (; *ptr != (wchar_t)'\0' && iswdigit(*ptr); ptr++);
    if (*ptr != (wchar_t)'\0' && *ptr == decimal_point) {
      ptr++;
      for (; *ptr != (wchar_t)'\0' && iswdigit(*ptr); ptr++);
      nonempty_mantissa = (ptr - start_mantissa > 1);
    } else
      nonempty_mantissa = (ptr - start_mantissa > 0);
    if (nonempty_mantissa) {
      const wchar_t* end_mantissa = ptr;
      if (towlower(*ptr) == 'e') {
        const wchar_t* start_exponent;
        int nonempty_exponent;
        ptr++;
        if (*ptr == '+' || *ptr == '-')
          ptr++;
        start_exponent = ptr;
        for (; *ptr != (wchar_t)'\0' && iswdigit(*ptr); ptr++);
        nonempty_exponent = (ptr - start_exponent > 0);
        if (nonempty_exponent)
          ; /* OK, keep ptr */
        else
          ptr = end_mantissa;
      }
      /* Now keep ptr */
      goto parse_done;
    }
    ptr = start_mantissa;
  }
  if (towlower(*ptr) == 'i'
      && towlower(ptr[1]) == 'n'
      && towlower(ptr[2]) == 'f') {
    if (   towlower(ptr[3]) == 'i'
        && towlower(ptr[4]) == 'n'
        && towlower(ptr[5]) == 'i'
        && towlower(ptr[6]) == 't'
        && towlower(ptr[7]) == 'y')
      ptr += 8;
    else
      ptr += 3;
    goto parse_done;
  }
  if (towlower(*ptr) == 'n'
      && towlower(ptr[1]) == 'a'
      && towlower(ptr[2]) == 'n') {
    const wchar_t* start_paren = ptr;
    if (*ptr == '(') {
      ptr++;
      for (; *ptr != (wchar_t)'\0' && (iswalnum(*ptr) || (*ptr == '_')); ptr++);
      if (*ptr == ')') {
        ptr++;
        goto parse_done;
      }
    }
    ptr = start_paren;
    goto parse_done;
  }
  ptr = nptr;
 parse_done:
  return ptr;
}
