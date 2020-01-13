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

#include <utf8/locale.h>

#if defined(LIBUTF8_PLUG) && defined(__GLIBC__) && (__GLIBC__ == 2) && (__GLIBC_MINOR__ == 0)
int utf8_mb_cur_max (void)
#else
size_t utf8_mb_cur_max (void)
#endif
{
  if (!locale_is_utf8)
    return 1;
  else
    /* 3 for 16-bit Unicode, 6 for 32-bit Unicode. */
#if WCHAR_T_BITS == 32
    return 6;
#else
    return 3;
#endif
}
