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

#include <utf8/wchar.h>

int mbtowc (wchar_t* pwc, const char* s, size_t n)
{
  mbstate_t state;
  /* If s == NULL, mbrtowc will return 0, which is what we want, because
     the encoding is not state dependent. */
  int result = mbrtowc(pwc, s, n, &state);
  if (result >= 0)
    return result;
  else
    return -1;
}
