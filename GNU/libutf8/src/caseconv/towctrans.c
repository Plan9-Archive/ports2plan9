/* Copyright (C) 1999-2001 Free Software Foundation, Inc.
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
#include <errno.h>

extern const short * const toupper_table[0x108];
extern const short * const tolower_table[0x108];

wint_t towctrans (wint_t wc, wctrans_t odesc)
#undef towupper /* identifier used inside toupper macro on OSF/1 4.0 */
#undef towlower /* identifier used inside tolower macro on OSF/1 4.0 */
{
  utf8_wctrans_t desc = (utf8_wctrans_t) odesc;
  if (!locale_is_utf8) {
    if ((u_wchar_t) wc < 0x100) {
      if (desc == toupper_table)
        return toupper((unsigned char) wc);
      if (desc == tolower_table)
        return tolower((unsigned char) wc);
      errno = EINVAL;
      return wc;
    } else
      return wc;
  } else {
    if ((unsigned int) wc < 0x10800u)
      return (unsigned short) (wc + desc[((unsigned int) wc) >> 8][((unsigned int) wc) & 0xff]);
    else
      return wc;
  }
}
