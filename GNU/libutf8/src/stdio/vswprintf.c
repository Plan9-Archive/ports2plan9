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

#include "sysdep-alloca.h"

#include <utf8/stdio.h>

#include <utf8/limits.h>
#include <utf8/stdlib.h>
#include <utf8/wchar.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include "wprintf-parse.h"
#ifdef LIBUTF8_PLUG
#include <unistd.h>
#include "libc.h"
#include <dlfcn.h>
#endif

#undef sprintf

int vswprintf (wchar_t* s, size_t maxlen, const wchar_t* format, va_list args)
{
  directives d;
  arguments a;
#ifdef LIBUTF8_PLUG
  static int (*original_sprintf) (char*, const char*, ...) = NULL;
  if (original_sprintf == NULL) {
    void* libc_handle = utf8_libc_handle();
    if (libc_handle != NULL)
      original_sprintf = dlsym(libc_handle,"sprintf");
  }
  if (!original_sprintf) {
    const char* errmessage = "libutf8: symbol 'sprintf' not found\n";
    write(2, errmessage, strlen(errmessage));
    exit(1);
  }
#define sprintf original_sprintf
#endif

  if (utf8_wprintf_parse(format,&d,&a) < 0) {
    if (maxlen > 0) *s = '\0'; /* for robustness */
    return -1;
  }
  if (utf8_printf_fetchargs(args,&a) < 0) {
    if (maxlen > 0) *s = '\0'; /* for robustness */
    return -1;
  }

  {
    const wchar_t* cp;
    unsigned int i;
    directive* dp;
    int total = 0;

    for (cp = format, i = 0, dp = &d.dir[0]; ; cp = dp->dir_end, i++, dp++) {
      if (cp != dp->dir_start) {
        unsigned long n = dp->dir_start - cp;
        total += n;
        if (maxlen > 0) {
          if (n > maxlen)
            n = maxlen;
          if (n > 0) {
            memcpy(s,cp,n*sizeof(wchar_t)); s += n; maxlen -= n;
            if (maxlen == 0) s[-1] = '\0';
          }
        }
      }
      if (i == d.count)
        break;
      /* Execute a single directive. */
      if (dp->conversion == '%') {
        if (!(dp->arg_index < 0)) abort();
        if (maxlen > 0) {
          *s++ = '%'; maxlen--;
          if (maxlen == 0) s[-1] = '\0';
        }
        total += 1;
      } else if (dp->conversion == 'n') {
        if (!(dp->arg_index >= 0)) abort();
        switch (a.arg[dp->arg_index].type) {
          case TYPE_COUNT_SCHAR_POINTER:
            *a.arg[dp->arg_index].a.a_count_schar_pointer = total;
            break;
          case TYPE_COUNT_SHORT_POINTER:
            *a.arg[dp->arg_index].a.a_count_short_pointer = total;
            break;
          case TYPE_COUNT_INT_POINTER:
            *a.arg[dp->arg_index].a.a_count_int_pointer = total;
            break;
          case TYPE_COUNT_LONGINT_POINTER:
            *a.arg[dp->arg_index].a.a_count_longint_pointer = total;
            break;
#ifdef HAVE_LONG_LONG
          case TYPE_COUNT_LONGLONGINT_POINTER:
            *a.arg[dp->arg_index].a.a_count_longlongint_pointer = total;
            break;
#endif
          default:
            abort();
        }
      } else {
        char buf[4096];
        char* p;
        unsigned int prefix_count;
        int prefixes[2];
        char mbbuf[4096];
        int count;
        int retcount;

        /* Using sprintf is safe, because valid format directives contain
           only ASCII characters, and the result too. */
        p = buf;
        *p++ = '%';
        if (dp->flags & FLAG_GROUP)
          *p++ = '\'';
        if (dp->flags & FLAG_LEFT)
          *p++ = '-';
        if (dp->flags & FLAG_SHOWSIGN)
          *p++ = '+';
        if (dp->flags & FLAG_SPACE)
          *p++ = ' ';
        if (dp->flags & FLAG_ALT)
          *p++ = '#';
        if (dp->flags & FLAG_ZERO)
          *p++ = '0';
        if (dp->width_start != dp->width_end) {
          unsigned long n = dp->width_end - dp->width_start;
          const wchar_t* wp = dp->width_start;
          for (; n > 0; n--)
            *p++ = (unsigned char) *wp++;
        }
        if (dp->precision_start != dp->precision_end) {
          unsigned long n = dp->precision_end - dp->precision_start;
          const wchar_t* wp = dp->precision_start;
          for (; n > 0; n--)
            *p++ = (unsigned char) *wp++;
        }
        if (dp->arg_index >= 0) {
          arg_type type = a.arg[dp->arg_index].type;
          switch (type) {
#ifdef HAVE_LONG_LONG
            case TYPE_LONGLONGINT:
            case TYPE_ULONGLONGINT:
              *p++ = 'l';
              /*FALLTHROUGH*/
#endif
            case TYPE_LONGINT:
            case TYPE_ULONGINT:
              *p++ = 'l';
              break;
#ifdef HAVE_LONG_DOUBLE
            case TYPE_LONGDOUBLE:
              *p++ = 'L';
              break;
#endif
            default:
              break;
          }
        }
        *p = dp->conversion;
        p[1] = '%';
        p[2] = 'n';
        p[3] = '\0';
        prefix_count = 0;
        if (dp->width_arg_index >= 0) {
          if (!(a.arg[dp->width_arg_index].type == TYPE_INT)) abort();
          prefixes[prefix_count++] = a.arg[dp->width_arg_index].a.a_int;
        }
        if (dp->precision_arg_index >= 0) {
          if (!(a.arg[dp->precision_arg_index].type == TYPE_INT)) abort();
          prefixes[prefix_count++] = a.arg[dp->precision_arg_index].a.a_int;
        }
        mbbuf[0] = '\0'; /* for checking whether snprintf returns the count via %n */
        count = 0;
        retcount = 0;
        if (dp->arg_index >= 0) {
          arg_type type = a.arg[dp->arg_index].type;
          switch (type) {
            case TYPE_SCHAR:
              {
                int arg = a.arg[dp->arg_index].a.a_schar;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            case TYPE_UCHAR:
              {
                unsigned int arg = a.arg[dp->arg_index].a.a_uchar;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            case TYPE_SHORT:
              {
                int arg = a.arg[dp->arg_index].a.a_short;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            case TYPE_USHORT:
              {
                unsigned int arg = a.arg[dp->arg_index].a.a_ushort;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            case TYPE_INT:
              {
                int arg = a.arg[dp->arg_index].a.a_int;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            case TYPE_UINT:
              {
                unsigned int arg = a.arg[dp->arg_index].a.a_uint;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            case TYPE_LONGINT:
              {
                long int arg = a.arg[dp->arg_index].a.a_longint;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            case TYPE_ULONGINT:
              {
                unsigned long int arg = a.arg[dp->arg_index].a.a_ulongint;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
#ifdef HAVE_LONG_LONG
            case TYPE_LONGLONGINT:
              {
                long long int arg = a.arg[dp->arg_index].a.a_longlongint;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            case TYPE_ULONGLONGINT:
              {
                unsigned long long int arg = a.arg[dp->arg_index].a.a_ulonglongint;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
#endif
            case TYPE_DOUBLE:
              {
                double arg = a.arg[dp->arg_index].a.a_double;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
#ifdef HAVE_LONG_DOUBLE
            case TYPE_LONGDOUBLE:
              {
                long double arg = a.arg[dp->arg_index].a.a_longdouble;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
#endif
            case TYPE_CHAR:
              {
                int arg = a.arg[dp->arg_index].a.a_char;
                char c[2];
                wchar_t wc;
                c[0] = (unsigned char) arg; c[1] = '\0';
                if (mbtowc(&wc,c,2) < 0) {
                  errno = EILSEQ;
                  if (maxlen > 0) *s = '\0'; /* for robustness */
                  return -1;
                }
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,'@',&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],'@',&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],'@',&count); break;
                  default: abort();
                }
                for (p = mbbuf; *p && maxlen > 0; p++) {
                  *s++ = (*p=='@' ? wc : (wchar_t) *p);
                  if (--maxlen == 0) s[-1] = '\0';
                }
                mbbuf[0] = '\0';
              }
              break;
            case TYPE_WIDE_CHAR:
              {
                wint_t arg = a.arg[dp->arg_index].a.a_wide_char;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,'@',&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],'@',&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],'@',&count); break;
                  default: abort();
                }
                for (p = mbbuf; *p && maxlen > 0; p++) {
                  *s++ = (*p=='@' ? arg : (wchar_t) *p);
                  if (--maxlen == 0) s[-1] = '\0';
                }
                mbbuf[0] = '\0';
              }
              break;
            case TYPE_STRING:
              {
                const char* arg = a.arg[dp->arg_index].a.a_string;
                int n = mbstowcs(NULL,arg,0);
                if (n >= 0) {
                  wchar_t* wcsarg = alloca((n+1)*sizeof(wchar_t));
                  char* fakearg = alloca(n+1);
                  mbstowcs(wcsarg,arg,n+1);
                  memset(fakearg,'@',n); fakearg[n] = '\0';
                  switch (prefix_count) {
                    case 0: retcount = sprintf(mbbuf,buf,fakearg,&count); break;
                    case 1: retcount = sprintf(mbbuf,buf,prefixes[0],fakearg,&count); break;
                    case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],fakearg,&count); break;
                    default: abort();
                  }
                  for (p = mbbuf; *p && maxlen > 0; p++) {
                    *s++ = (*p=='@' ? *wcsarg++ : (wchar_t) *p);
                    if (--maxlen == 0) s[-1] = '\0';
                  }
                  freea(fakearg);
                  freea(wcsarg);
                } else {
                  errno = EILSEQ;
                  if (maxlen > 0) *s = '\0'; /* for robustness */
                  return -1;
                }
                mbbuf[0] = '\0';
              }
              break;
            case TYPE_WIDE_STRING:
              {
                const wchar_t* arg = a.arg[dp->arg_index].a.a_wide_string;
                int n = wcslen(arg);
                char* fakearg = alloca(n+1);
                memset(fakearg,'@',n); fakearg[n] = '\0';
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,fakearg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],fakearg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],fakearg,&count); break;
                  default: abort();
                }
                for (p = mbbuf; *p && maxlen > 0; p++) {
                  *s++ = (*p=='@' ? *arg++ : (wchar_t) *p);
                  if (--maxlen == 0) s[-1] = '\0';
                }
                mbbuf[0] = '\0';
                freea(fakearg);
              }
              break;
            case TYPE_POINTER:
              {
                void* arg = a.arg[dp->arg_index].a.a_pointer;
                switch (prefix_count) {
                  case 0: retcount = sprintf(mbbuf,buf,arg,&count); break;
                  case 1: retcount = sprintf(mbbuf,buf,prefixes[0],arg,&count); break;
                  case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],arg,&count); break;
                  default: abort();
                }
              }
              break;
            default:
              abort();
          }
        } else {
          switch (prefix_count) {
            case 0: retcount = sprintf(mbbuf,buf,&count); break;
            case 1: retcount = sprintf(mbbuf,buf,prefixes[0],&count); break;
            case 2: retcount = sprintf(mbbuf,buf,prefixes[0],prefixes[1],&count); break;
            default: abort();
          }
        }
        for (p = mbbuf; *p && maxlen > 0; p++) {
          *s++ = *p;
          if (--maxlen == 0) s[-1] = '\0';
        }
        total += (retcount > count ? retcount : count);
      }
    }
    if (maxlen == 0)
      return -1;
    *s = '\0';
    return total;
  }
}
