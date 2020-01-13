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

#include <utf8/locale.h>

#include <stdlib.h>
#include <string.h>
#ifdef LIBUTF8_PLUG
#include "libc.h"
#include <dlfcn.h>
#endif

char* setlocale (int category, const char* locale)
#undef setlocale
{
#ifdef LIBUTF8_PLUG
  static char* (*original_setlocale) (int, const char*) = NULL;
  if (original_setlocale == NULL) {
    void* libc_handle = utf8_libc_handle();
    if (libc_handle != NULL)
      original_setlocale = dlsym(libc_handle,"setlocale");
  }
#define setlocale(x,y) \
  (original_setlocale != NULL ? original_setlocale(x,y) : NULL)
#endif
  {
    char* result = setlocale(category, locale);
    /* locale = NULL means no change, just an enquiry. */
    if (locale) {
      /* We are only interested in LC_CTYPE changes. */
      if (category == LC_CTYPE || category == LC_ALL) {
        if (locale[0] == '\0') {
          /* Determine the current locale the same way as setlocale() does,
             according to POSIX. */
          locale = getenv("LC_ALL");
          if (!locale || !*locale) {
            locale = getenv("LC_CTYPE");
            if (!locale || !*locale) {
              locale = getenv("LANG");
            }
          }
        }
        locale_is_utf8 = 0;
        if (locale && *locale) {
          /* The most general syntax of a locale (not all optional parts
             recognized by all systems) is
             language[_territory][.codeset][@modifier][+special][,[sponsor][_revision]]
             To retrieve the codeset, search the first dot. Stop searching when
             a '@' or '+' or ',' is encountered. */
          const char* cp = locale;
          for (; *cp != '\0' && *cp != '@' && *cp != '+' && *cp != ','; cp++) {
            if (*cp == '.') {
              const char* encoding = ++cp;
              for (; *cp != '\0' && *cp != '@' && *cp != '+' && *cp != ','; cp++);
              /* The encoding is now contained in the part from encoding to cp. */
              /* Check it for "UTF-8", which is the only official IANA name of
                 UTF-8. Also check for the lowercase-no-dashes version, which is
                 what some SystemV systems use. */
              if ((cp-encoding == 5 && !strncmp(encoding, "UTF-8", 5))
                  || (cp-encoding == 4 && !strncmp(encoding, "utf8", 4)))
                locale_is_utf8 = 1; /* it's UTF-8 */
              break;
            }
          }
        }
      }
    }
    return result;
  }
}
