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

#include "sysdep-alloca.h"

#include <utf8/wchar.h>

#include <utf8/wctype.h>
#include "number-parse.h"

double wcstod (const wchar_t* nptr, wchar_t** endptr)
{
  const wchar_t* eptr;
  size_t n;
  char* tmp;
  double result;

  /* Skip whitespace. */
  for (; *nptr != (wchar_t)'\0' && iswspace(*nptr); nptr++);

  /* Parse number. */
  eptr = utf8_number_parse(nptr);

  /* Fill it into a char* string. */
  n = eptr - nptr;
  tmp = alloca(n+1);
  {
    const wchar_t* p1;
    char* p2 = tmp;
    for (p1 = nptr; p1 < eptr; p1++)
      *p2++ = wctob(*p1);
    *p2 = '\0';
  }

  /* Convert to number. */
  result = strtod(tmp,NULL);

  freea(tmp);
  if (endptr)
    *endptr = (wchar_t*) eptr;
  return result;
}
