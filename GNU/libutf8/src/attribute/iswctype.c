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

#undef isblank
#define isblank(c) ((c) == ' ' || (c) == '\t')

int iswctype (wint_t wc, wctype_t desc)
#undef iswctype /* identifier used inside is* macros on OSF/1 4.0 */
{
  if (!locale_is_utf8) {
    if ((u_wchar_t) wc < 0x100)
      switch (wmask_number(desc)) {
        case wmask_number(wctype_upper):  return isupper((unsigned char) wc);
        case wmask_number(wctype_lower):  return islower((unsigned char) wc);
        case wmask_number(wctype_alpha):  return isalpha((unsigned char) wc);
        case wmask_number(wctype_digit):  return isdigit((unsigned char) wc);
        case wmask_number(wctype_xdigit): return isxdigit((unsigned char) wc);
        case wmask_number(wctype_space):  return isspace((unsigned char) wc);
        case wmask_number(wctype_print):  return isprint((unsigned char) wc);
        case wmask_number(wctype_graph):  return isgraph((unsigned char) wc);
        case wmask_number(wctype_blank):  return isblank((unsigned char) wc);
        case wmask_number(wctype_cntrl):  return iscntrl((unsigned char) wc);
        case wmask_number(wctype_punct):  return ispunct((unsigned char) wc);
        case wmask_number(wctype_alnum):  return isalnum((unsigned char) wc);
        default: return 0; /* should not happen */
      }
    else
      return 0;
  } else {
    if ((unsigned int) wc <= 0xffffu) {
      unsigned char attributes = attribute_table[((unsigned int) wc) >> 8][((unsigned int) wc) & 0xff];
      return ((attributes & wmask_incl(desc)) != 0
              && (attributes & wmask_excl(desc)) == 0);
    }
    return 0;
  }
}
