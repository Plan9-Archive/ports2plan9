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

#include <string.h>
#include "iswbits.h"

struct ctype_property {
  const char* property;
  wctype_t ctype;
};

static struct ctype_property all_properties[] = {
  { "upper", wctype_upper },
  { "lower", wctype_lower },
  { "alpha", wctype_alpha },
  { "digit", wctype_digit },
  { "xdigit", wctype_xdigit },
  { "space", wctype_space },
  { "print", wctype_print },
  { "graph", wctype_graph },
  { "blank", wctype_blank },
  { "cntrl", wctype_cntrl },
  { "punct", wctype_punct },
  { "alnum", wctype_alnum }
};

wctype_t wctype (const char* property)
{
  struct ctype_property * ptr = &all_properties[0];
  size_t count = sizeof(all_properties) / sizeof(all_properties[0]);
  for (; count > 0; ptr++, count--)
    if (!strcmp(ptr->property, property))
      return ptr->ctype;
  return 0;
}
