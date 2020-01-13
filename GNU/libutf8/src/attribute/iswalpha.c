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

#include <utf8/wctype.h>

#include <utf8/locale.h>
#include <ctype.h>
#include "iswbits.h"

int iswalpha (wint_t wc)
#undef iswctype /* identifier used inside isalpha macro on OSF/1 4.0 */
{
  if (!locale_is_utf8) {
    if ((u_wchar_t) wc < 0x100)
      return isalpha((unsigned char) wc);
    else
      return 0;
  } else {
    if ((unsigned int) wc <= 0xffffu) {
      unsigned char attributes = attribute_table[((unsigned int) wc) >> 8][((unsigned int) wc) & 0xff];
      return ((attributes & wmask_incl(wctype_alpha)) != 0
              && (attributes & wmask_excl(wctype_alpha)) == 0);
    }
    return 0;
  }
}
