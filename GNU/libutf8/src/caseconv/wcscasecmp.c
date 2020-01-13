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

int wcscasecmp (const wchar_t* s1, const wchar_t* s2)
{
  for (;;) {
    wchar_t wc1 = towlower(*s1++);
    wchar_t wc2 = towlower(*s2++);
    if (wc1 != (wchar_t)'\0' && wc1 == wc2)
      continue;
    /* Note that wc1 and wc2 each have at most 31 bits. */
    return (int)wc1 - (int)wc2;
    /* > 0 if wc1 > wc2, < 0 if wc1 < wc2, = 0 if wc1 and wc2 are both '\0'. */
  }
}
