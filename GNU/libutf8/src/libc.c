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

#ifdef LIBUTF8_PLUG

#include "libc.h"

#include <stddef.h>
#include <dlfcn.h>

/* Linux */
#ifdef __linux__
#include <features.h>
#ifdef __GLIBC__
#define LIBC_FILENAME "/lib/libc.so.6"
#else
#define LIBC_FILENAME "/lib/libc.so.5"
#endif
#endif

/* Solaris */
#ifdef __sun
#define LIBC_FILENAME "/lib/libc.so"
#endif

/* OSF/1 */
#ifdef __osf__
#define LIBC_FILENAME "/shlib/libc.so"
#endif

void* utf8_libc_handle (void)
{
  static void* libc_handle = NULL;
  if (libc_handle == NULL)
    libc_handle = dlopen(LIBC_FILENAME,RTLD_LAZY);
  return libc_handle;
}

#endif
