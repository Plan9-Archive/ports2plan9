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

wchar_t* wcstok (wchar_t* wcs, const wchar_t* delim, wchar_t** ptr)
{
  if (wcs == NULL) {
    wcs = *ptr;
    if (wcs == NULL)
      return NULL; /* reminder that end of token sequence has been reached */
  }
  /* Skip leading delimiters. */
  wcs += wcsspn(wcs, delim);
  /* Found a token? */
  if (*wcs == (wchar_t)'\0') {
    *ptr = NULL;
    return NULL;
  }
  /* Move past the token. */
  {
    wchar_t* token_end = wcspbrk(wcs, delim);
    if (token_end) {
      /* NUL-terminate the token. */
      *token_end = (wchar_t)'\0';
      *ptr = token_end+1;
    } else
      *ptr = NULL;
  }
  return wcs;
}
