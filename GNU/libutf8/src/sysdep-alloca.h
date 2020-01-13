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


/* When this file is included, it may be preceded only by preprocessor
   declarations. Thanks to AIX. */

#include "config.h"

#ifdef NO_ALLOCA

#include <stdlib.h>
#define alloca malloc
#define freea free

#else

/* This is the recommended way to get alloca() working. */
# ifdef __GNUC__
#  define alloca __builtin_alloca
# else
#  ifdef _MSC_VER
#   include <malloc.h>
#   define alloca _alloca
#  else
#   ifdef HAVE_ALLOCA_H
#    include <alloca.h>
#   else
#    ifdef _AIX
 #pragma alloca
#    else
#     ifndef alloca
       char *alloca ();
#     endif
#    endif
#   endif
#  endif
# endif

#define freea(x)

#endif
