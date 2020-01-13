/* Copyright (C) 1999-2000 Free Software Foundation, Inc.
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

#include <stdio.h>
#include "wprintf-parse.h"

int utf8_wprintf_parse (const wchar_t* format, directives* d, arguments* a)
{
  const wchar_t* cp = format;	/* pointer into format */
  directive* dp = &d->dir[0];	/* pointer to next directive */
  int arg_posn = 0;		/* number of regular arguments consumed */
  d->count = 0;
  a->count = 0;

#define REGISTER_ARG(_index_,_type_) \
  {									\
    unsigned int n = (_index_);						\
    while (a->count <= n) a->arg[a->count++].type = TYPE_NONE;		\
    if (a->arg[n].type == TYPE_NONE)					\
      a->arg[n].type = (_type_);					\
    else if (a->arg[n].type != (_type_)) {				\
      fprintf(stderr, "utf8_printf: Ambiguous type for positional argument %u\n", n); \
      return -1;							\
    }									\
  }

  while (*cp != '\0') {
    wchar_t c = *cp++;
    if (c == '%') {
      int arg_index = -1;
      /* Initialize the next directive. */
      dp->dir_start = cp-1;
      dp->flags = 0;
      dp->width_start = NULL;
      dp->width_end = NULL;
      dp->width_arg_index = -1;
      dp->precision_start = NULL;
      dp->precision_end = NULL;
      dp->precision_arg_index = -1;
      dp->arg_index = -1;
      /* Test for positional argument. */
      if (*cp >= '0' && *cp <= '9') {
        const wchar_t* np;
        for (np = cp; *np >= '0' && *np <= '9'; np++);
        if (*np == '$') {
          unsigned int n = 0;
          for (np = cp; *np >= '0' && *np <= '9'; np++)
            n = 10*n + (*np-'0');
          if (n == 0) {
            fprintf(stderr, "utf8_printf: Positional argument 0\n");
            return -1;
          }
          if (n > MAX_ARGUMENTS) {
            fprintf(stderr, "utf8_printf: Positional argument %u too large\n", n);
            return -1;
          }
          arg_index = n-1;
          cp = np+1;
        }
      }
      /* Read the flags. */
      for (;;) {
        if (*cp == '\'') {
          dp->flags |= FLAG_GROUP;
          cp++;
        } else if (*cp == '-') {
          dp->flags |= FLAG_LEFT;
          cp++;
        } else if (*cp == '+') {
          dp->flags |= FLAG_SHOWSIGN;
          cp++;
        } else if (*cp == ' ') {
          dp->flags |= FLAG_SPACE;
          cp++;
        } else if (*cp == '#') {
          dp->flags |= FLAG_ALT;
          cp++;
        } else if (*cp == '0') {
          dp->flags |= FLAG_ZERO;
          cp++;
        } else
          break;
      }
      /* Parse the field width. */
      if (*cp == '*') {
        dp->width_start = cp;
        cp++;
        dp->width_end = cp;
        /* Test for positional argument. */
        if (*cp >= '0' && *cp <= '9') {
          const wchar_t* np;
          for (np = cp; *np >= '0' && *np <= '9'; np++);
          if (*np == '$') {
            unsigned int n = 0;
            for (np = cp; *np >= '0' && *np <= '9'; np++)
              n = 10*n + (*np-'0');
            if (n == 0) {
              fprintf(stderr, "utf8_printf: Positional argument 0\n");
              return -1;
            }
            if (n > MAX_ARGUMENTS) {
              fprintf(stderr, "utf8_printf: Positional argument %u too large\n", n);
              return -1;
            }
            dp->width_arg_index = n-1;
            cp = np+1;
          }
        }
        if (dp->width_arg_index < 0)
          dp->width_arg_index = arg_posn++;
        REGISTER_ARG(dp->width_arg_index,TYPE_INT);
      } else if (*cp >= '0' && *cp <= '9') {
        dp->width_start = cp;
        for (; *cp >= '0' && *cp <= '9'; cp++);
        dp->width_end = cp;
      }
      /* Parse the precision. */
      if (*cp == '.') {
        cp++;
        if (*cp == '*') {
          dp->precision_start = cp-1;
          cp++;
          dp->precision_end = cp;
          /* Test for positional argument. */
          if (*cp >= '0' && *cp <= '9') {
            const wchar_t* np;
            for (np = cp; *np >= '0' && *np <= '9'; np++);
            if (*np == '$') {
              unsigned int n = 0;
              for (np = cp; *np >= '0' && *np <= '9'; np++)
                n = 10*n + (*np-'0');
              if (n == 0) {
                fprintf(stderr, "utf8_printf: Positional argument 0\n");
                return -1;
              }
              if (n > MAX_ARGUMENTS) {
                fprintf(stderr, "utf8_printf: Positional argument %u too large\n", n);
                return -1;
              }
              dp->precision_arg_index = n-1;
              cp = np+1;
            }
          }
          if (dp->precision_arg_index < 0)
            dp->precision_arg_index = arg_posn++;
          REGISTER_ARG(dp->precision_arg_index,TYPE_INT);
        } else {
          dp->precision_start = cp-1;
          for (; *cp >= '0' && *cp <= '9'; cp++);
          dp->precision_end = cp;
        }
      }
      {
        arg_type type;
        /* Parse argument type/size specifiers. */
        {
          int flags = 0;
          for (;;) {
            if (*cp == 'h') {
              flags |= (1 << (flags & 1));
              cp++;
            } else if (*cp == 'L') {
              flags |= 4;
              cp++;
            } else if (*cp == 'l') {
              flags += 8;
              cp++;
            }
#ifdef HAVE_INTMAX_T
              else if (*cp == 'j') {
              if (sizeof(intmax_t) > sizeof(long)) {
                /* intmax_t = long long */
                flags += 16;
              } else if (sizeof(intmax_t) > sizeof(int)) {
                /* intmax_t = long */
                flags += 8;
              }
              cp++;
            }
#endif
              else if (*cp == 'z' || *cp == 'Z') {
              /* 'z' is standardized in ISO C 99, but glibc uses 'Z' because
                 the warning facility in gcc-2.95.2 understands only 'Z'
                 (see gcc-2.95.2/gcc/c-common.c:1784). */
              if (sizeof(size_t) > sizeof(long)) {
                /* size_t = long long */
                flags += 16;
              } else if (sizeof(size_t) > sizeof(int)) {
                /* size_t = long */
                flags += 8;
              }
              cp++;
            } else if (*cp == 't') {
              if (sizeof(ptrdiff_t) > sizeof(long)) {
                /* ptrdiff_t = long long */
                flags += 16;
              } else if (sizeof(ptrdiff_t) > sizeof(int)) {
                /* ptrdiff_t = long */
                flags += 8;
              }
              cp++;
            } else
              break;
          }
          /* Read the conversion character. */
          c = *cp++;
          switch (c) {
            case 'd': case 'i':
#ifdef HAVE_LONG_LONG
              if (flags >= 16 || (flags & 4))
                type = TYPE_LONGLONGINT;
              else
#endif
              if (flags >= 8)
                type = TYPE_LONGINT;
              else if (flags & 2)
                type = TYPE_SCHAR;
              else if (flags & 1)
                type = TYPE_SHORT;
              else
                type = TYPE_INT;
              break;
            case 'o': case 'u': case 'x': case 'X':
#ifdef HAVE_LONG_LONG
              if (flags >= 16 || (flags & 4))
                type = TYPE_ULONGLONGINT;
              else
#endif
              if (flags >= 8)
                type = TYPE_ULONGINT;
              else if (flags & 2)
                type = TYPE_UCHAR;
              else if (flags & 1)
                type = TYPE_USHORT;
              else
                type = TYPE_UINT;
              break;
            case 'f': case 'e': case 'E': case 'g': case 'G':
#ifdef HAVE_LONG_DOUBLE
              if (flags >= 16 || (flags & 4))
                type = TYPE_LONGDOUBLE;
              else
#endif
                type = TYPE_DOUBLE;
              break;
            case 'c':
              if (flags >= 8)
                type = TYPE_WIDE_CHAR;
              else
                type = TYPE_CHAR;
              break;
            case 'C':
              type = TYPE_WIDE_CHAR;
              c = 'c';
              break;
            case 's':
              if (flags >= 8)
                type = TYPE_WIDE_STRING;
              else
                type = TYPE_STRING;
              break;
            case 'S':
              type = TYPE_WIDE_STRING;
              c = 's';
              break;
            case 'p':
              type = TYPE_POINTER;
              break;
            case 'n':
#ifdef HAVE_LONG_LONG
              if (flags >= 16 || (flags & 4))
                type = TYPE_COUNT_LONGLONGINT_POINTER;
              else
#endif
              if (flags >= 8)
                type = TYPE_COUNT_LONGINT_POINTER;
              else if (flags & 2)
                type = TYPE_COUNT_SCHAR_POINTER;
              else if (flags & 1)
                type = TYPE_COUNT_SHORT_POINTER;
              else
                type = TYPE_COUNT_INT_POINTER;
              break;
            case '%':
              type = TYPE_NONE;
              break;
            default:
              fprintf(stderr, "utf8_printf: Unknown conversion character `%lc'\n", (wint_t) c);
              return -1;
          }
        }
        if (type != TYPE_NONE) {
          dp->arg_index = arg_index;
          if (dp->arg_index < 0)
            dp->arg_index = arg_posn++;
          REGISTER_ARG(dp->arg_index,type);
        }
        dp->conversion = c;
        dp->dir_end = cp;
      }
      dp++; d->count++;
      if (d->count >= MAX_DIRECTIVES) {
        fprintf(stderr, "utf8_printf: Too many directives\n");
        return -1;
      }
    }
  }
  dp->dir_start = cp;
  return 0;
}
