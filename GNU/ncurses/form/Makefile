# $Id: Makefile.in,v 1.53 2010/11/27 21:45:27 tom Exp $
##############################################################################
# Copyright (c) 1998-2009,2010 Free Software Foundation, Inc.                #
#                                                                            #
# Permission is hereby granted, free of charge, to any person obtaining a    #
# copy of this software and associated documentation files (the "Software"), #
# to deal in the Software without restriction, including without limitation  #
# the rights to use, copy, modify, merge, publish, distribute, distribute    #
# with modifications, sublicense, and/or sell copies of the Software, and to #
# permit persons to whom the Software is furnished to do so, subject to the  #
# following conditions:                                                      #
#                                                                            #
# The above copyright notice and this permission notice shall be included in #
# all copies or substantial portions of the Software.                        #
#                                                                            #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR #
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    #
# THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      #
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    #
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        #
# DEALINGS IN THE SOFTWARE.                                                  #
#                                                                            #
# Except as contained in this notice, the name(s) of the above copyright     #
# holders shall not be used in advertising or otherwise to promote the sale, #
# use or other dealings in this Software without prior written               #
# authorization.                                                             #
##############################################################################
#
# Author: Thomas E. Dickey 1996-on
#
# Makefile for form source code.
#
# This makes the following:
#	libraries (normal/debug/profile/shared)
#
# The variable 'srcdir' refers to the source-distribution, and can be set with
# the configure script by "--srcdir=DIR".
#
# The rules are organized to produce the libraries for the configured models,

# turn off _all_ suffix rules; we'll generate our own
.SUFFIXES:

SHELL		= /bin/sh

THIS		= Makefile

x		= 
o		= .o

MODEL		= normal
DESTDIR		= 
srcdir		= .
prefix		= /sys/lib
exec_prefix	= /386
bindir		= /386/bin/ape
libdir		= /386/lib/ape
includedir	= /sys/include/ape

LIBTOOL		= 
LIBTOOL_CLEAN	= 
LIBTOOL_COMPILE	= 
LIBTOOL_LINK	= ${CC}
LIBTOOL_INSTALL	= 
LIBTOOL_UNINSTALL = 
LT_UNDEF	= 

INSTALL		= /bin/install -c
INSTALL_LIB	= /bin/install -c -m 644
INSTALL_PROG	= ${INSTALL}
INSTALL_DATA	= ${INSTALL} -m 644

AR		= ar
ARFLAGS		= curv
AWK		= awk
LD		= ld
LN_S		= ln -s -f

CTAGS		= 
ETAGS		= 

CC		= cc
CPP		= cc -E
CFLAGS		= -D_POSIX_SOURCE -D_SUSV2_SOURCE -D_RESEARCH_SOURCE -D_PLAN9_SOURCE -D_BSD_EXTENSION -D_REENTRANT_SOURCE -D_C99_SNPRINTF_EXTENSION -D_REGEXP_EXTENSION -DPLAN9  -g

CPPFLAGS	= -I../ncurses -DHAVE_CONFIG_H   -D_XOPEN_SOURCE=500  -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE_EXTENDED -I. -I../include -I${includedir}

CCFLAGS		= $(CPPFLAGS) $(CFLAGS)

CFLAGS_LIBTOOL	= $(CCFLAGS)
CFLAGS_NORMAL	= $(CCFLAGS)
CFLAGS_DEBUG	= $(CCFLAGS) -g -DTRACE
CFLAGS_PROFILE	= $(CCFLAGS) -pg
CFLAGS_SHARED	= $(CCFLAGS) unknown

CFLAGS_DEFAULT	= $(CFLAGS_NORMAL)

LINK		= $(LIBTOOL_LINK)
LDFLAGS		=    

SHLIB_DIRS	= -L../lib
SHLIB_LIST	= $(SHLIB_DIRS) -lncursestw  -ltinfotw

MK_SHARED_LIB	= echo unknown

NCURSES_MAJOR	= 5
NCURSES_MINOR	= 9
REL_VERSION	= 6.0
ABI_VERSION	= 6

RANLIB		= ranlib

LIBRARIES	=  ../lib/libformtw.a ../lib/libformtw_p.a

LINT		= 
LINT_OPTS	= 
LINT_LIBS	= -lform -lncurses  

AUTO_SRC	= \
		../include/form.h

################################################################################
all \
libs \
install ::	$(AUTO_SRC) $(LIBRARIES)

sources :	$(AUTO_SRC)

$(DESTDIR)$(bindir) \
$(DESTDIR)$(libdir) :
	mkdir -p $@

# make copies to simplify include-paths while still keeping form's include
# file in this directory.
../include/form.h : $(srcdir)/form.h
	-rm -f $@
	cp $(srcdir)/form.h $@

HEADER_DEPS = \
	$(srcdir)/form.priv.h \
	$(srcdir)/form.h \
	../include/mf_common.h \
	../include/curses.h \
	../include/eti.h

tags:
	$(CTAGS) *.[ch]

#TAGS:
#	$(ETAGS) *.[ch]

mostlyclean ::
	-rm -f core tags TAGS *~ *.bak *.i *.ln *.atac trace

clean :: mostlyclean
	-rm -f $(AUTO_SRC)

distclean :: clean
	-rm -f Makefile

realclean :: distclean

../include/mf_common.h \
../include/eti.h :
	cd ../menu && $(MAKE) $@

###############################################################################
# The remainder of this file is automatically generated during configuration
###############################################################################

# generated by mk-0th.awk
#   libname:    formtw
#   subsets:    ticlib+termlib+ext_tinfo base+widechar+ext_funcs

.SUFFIXES: .c .cc .h .i .ii
.c.i :
	$(CPP) $(CPPFLAGS) $< >$@
.cc.ii :
	$(CPP) $(CPPFLAGS) $< >$@
.h.i :
	$(CPP) $(CPPFLAGS) $< >$@

C_SRC = \
	$(srcdir)/f_trace.c \
	$(srcdir)/fld_arg.c \
	$(srcdir)/fld_attr.c \
	$(srcdir)/fld_current.c \
	$(srcdir)/fld_def.c \
	$(srcdir)/fld_dup.c \
	$(srcdir)/fld_ftchoice.c \
	$(srcdir)/fld_ftlink.c \
	$(srcdir)/fld_info.c \
	$(srcdir)/fld_just.c \
	$(srcdir)/fld_link.c \
	$(srcdir)/fld_max.c \
	$(srcdir)/fld_move.c \
	$(srcdir)/fld_newftyp.c \
	$(srcdir)/fld_opts.c \
	$(srcdir)/fld_pad.c \
	$(srcdir)/fld_page.c \
	$(srcdir)/fld_stat.c \
	$(srcdir)/fld_type.c \
	$(srcdir)/fld_user.c \
	$(srcdir)/frm_cursor.c \
	$(srcdir)/frm_data.c \
	$(srcdir)/frm_def.c \
	$(srcdir)/frm_driver.c \
	$(srcdir)/frm_hook.c \
	$(srcdir)/frm_opts.c \
	$(srcdir)/frm_page.c \
	$(srcdir)/frm_post.c \
	$(srcdir)/frm_req_name.c \
	$(srcdir)/frm_scale.c \
	$(srcdir)/frm_sub.c \
	$(srcdir)/frm_user.c \
	$(srcdir)/frm_win.c \
	$(srcdir)/fty_alnum.c \
	$(srcdir)/fty_alpha.c \
	$(srcdir)/fty_enum.c \
	$(srcdir)/fty_generic.c \
	$(srcdir)/fty_int.c \
	$(srcdir)/fty_ipv4.c \
	$(srcdir)/fty_num.c \
	$(srcdir)/fty_regex.c

# Producing llib-lformtw is time-consuming, so there's no direct-dependency for
# it in the lintlib rule.  We'll only remove in the cleanest setup.
clean ::
	rm -f llib-lformtw.*

realclean ::
	rm -f llib-lformtw

llib-lformtw : $(C_SRC)
	cproto -a -l -DNCURSES_ENABLE_STDBOOL_H=0 -DLINT $(CPPFLAGS) $(C_SRC) >$@

lintlib :
	sh $(srcdir)/../misc/makellib formtw $(CPPFLAGS)
lint :
	$(LINT) $(LINT_OPTS) $(CPPFLAGS) $(C_SRC) $(LINT_LIBS)





# generated by mk-1st.awk (subset=base+widechar+ext_funcs)
#  name:          formtw
#  traces:        DEBUG
#  MODEL:         NORMAL
#  model:         objects
#  prefix:        lib
#  suffix:        .a
#  subset:        base+widechar+ext_funcs
#  ShlibVer:      auto
#  ShlibVerInfix: no
#  SymLink:       ln -s -f
#  TermlibRoot:   tinfotw
#  TermlibSuffix: .a
#  ReLink:        no
#  DoLinks:       no
#  rmSoLocs:      no
#  ldconfig:      
#  overwrite:     no
#  depend:        ../include/ncurses_cfg.h ./form.priv.h
#  host:          i386-unknown-plan9

NORMAL_OBJS = \
	../objects/fld_arg$o \
	../objects/fld_attr$o \
	../objects/fld_current$o \
	../objects/fld_def$o \
	../objects/fld_dup$o \
	../objects/fld_ftchoice$o \
	../objects/fld_ftlink$o \
	../objects/fld_info$o \
	../objects/fld_just$o \
	../objects/fld_link$o \
	../objects/fld_max$o \
	../objects/fld_move$o \
	../objects/fld_newftyp$o \
	../objects/fld_opts$o \
	../objects/fld_pad$o \
	../objects/fld_page$o \
	../objects/fld_stat$o \
	../objects/fld_type$o \
	../objects/fld_user$o \
	../objects/frm_cursor$o \
	../objects/frm_data$o \
	../objects/frm_def$o \
	../objects/frm_driver$o \
	../objects/frm_hook$o \
	../objects/frm_opts$o \
	../objects/frm_page$o \
	../objects/frm_post$o \
	../objects/frm_req_name$o \
	../objects/frm_scale$o \
	../objects/frm_sub$o \
	../objects/frm_user$o \
	../objects/frm_win$o \
	../objects/fty_alnum$o \
	../objects/fty_alpha$o \
	../objects/fty_enum$o \
	../objects/fty_generic$o \
	../objects/fty_int$o \
	../objects/fty_ipv4$o \
	../objects/fty_num$o \
	../objects/fty_regex$o

$(NORMAL_OBJS) : ../include/ncurses_cfg.h ./form.priv.h

../lib/libformtw.a : $(NORMAL_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	$(RANLIB) $@

install \
install.libs \
install.formtw :: $(DESTDIR)$(libdir) ../lib/libformtw.a
	@echo installing ../lib/libformtw.a as $(DESTDIR)$(libdir)/libformtw.a
	$(INSTALL_DATA) ../lib/libformtw.a $(DESTDIR)$(libdir)/libformtw.a
	$(RANLIB) $(DESTDIR)$(libdir)/libformtw.a

uninstall \
uninstall.libs \
uninstall.formtw ::
	@echo uninstalling $(DESTDIR)$(libdir)/libformtw.a
	-@rm -f $(DESTDIR)$(libdir)/libformtw.a

clean ::
	-rm -f ../lib/libformtw.a

mostlyclean::
	-rm -f $(NORMAL_OBJS)

# generated by mk-2nd.awk
#   model:      objects
#   MODEL:      NORMAL
#   echo:       yes
#   subset:     base+widechar+ext_funcs
#   crenames:   yes
#   cxxrenames: 
#   traces:     DEBUG
#   srcdir:     .

../objects/fld_arg$o :	$(srcdir)/fld_arg.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_arg.c -o ../objects/fld_arg$o

../objects/fld_attr$o :	$(srcdir)/fld_attr.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_attr.c -o ../objects/fld_attr$o

../objects/fld_current$o :	$(srcdir)/fld_current.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_current.c -o ../objects/fld_current$o

../objects/fld_def$o :	$(srcdir)/fld_def.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_def.c -o ../objects/fld_def$o

../objects/fld_dup$o :	$(srcdir)/fld_dup.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_dup.c -o ../objects/fld_dup$o

../objects/fld_ftchoice$o :	$(srcdir)/fld_ftchoice.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_ftchoice.c -o ../objects/fld_ftchoice$o

../objects/fld_ftlink$o :	$(srcdir)/fld_ftlink.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_ftlink.c -o ../objects/fld_ftlink$o

../objects/fld_info$o :	$(srcdir)/fld_info.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_info.c -o ../objects/fld_info$o

../objects/fld_just$o :	$(srcdir)/fld_just.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_just.c -o ../objects/fld_just$o

../objects/fld_link$o :	$(srcdir)/fld_link.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_link.c -o ../objects/fld_link$o

../objects/fld_max$o :	$(srcdir)/fld_max.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_max.c -o ../objects/fld_max$o

../objects/fld_move$o :	$(srcdir)/fld_move.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_move.c -o ../objects/fld_move$o

../objects/fld_newftyp$o :	$(srcdir)/fld_newftyp.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_newftyp.c -o ../objects/fld_newftyp$o

../objects/fld_opts$o :	$(srcdir)/fld_opts.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_opts.c -o ../objects/fld_opts$o

../objects/fld_pad$o :	$(srcdir)/fld_pad.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_pad.c -o ../objects/fld_pad$o

../objects/fld_page$o :	$(srcdir)/fld_page.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_page.c -o ../objects/fld_page$o

../objects/fld_stat$o :	$(srcdir)/fld_stat.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_stat.c -o ../objects/fld_stat$o

../objects/fld_type$o :	$(srcdir)/fld_type.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_type.c -o ../objects/fld_type$o

../objects/fld_user$o :	$(srcdir)/fld_user.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fld_user.c -o ../objects/fld_user$o

../objects/frm_cursor$o :	$(srcdir)/frm_cursor.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_cursor.c -o ../objects/frm_cursor$o

../objects/frm_data$o :	$(srcdir)/frm_data.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_data.c -o ../objects/frm_data$o

../objects/frm_def$o :	$(srcdir)/frm_def.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_def.c -o ../objects/frm_def$o

../objects/frm_driver$o :	$(srcdir)/frm_driver.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_driver.c -o ../objects/frm_driver$o

../objects/frm_hook$o :	$(srcdir)/frm_hook.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_hook.c -o ../objects/frm_hook$o

../objects/frm_opts$o :	$(srcdir)/frm_opts.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_opts.c -o ../objects/frm_opts$o

../objects/frm_page$o :	$(srcdir)/frm_page.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_page.c -o ../objects/frm_page$o

../objects/frm_post$o :	$(srcdir)/frm_post.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_post.c -o ../objects/frm_post$o

../objects/frm_req_name$o :	$(srcdir)/frm_req_name.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_req_name.c -o ../objects/frm_req_name$o

../objects/frm_scale$o :	$(srcdir)/frm_scale.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_scale.c -o ../objects/frm_scale$o

../objects/frm_sub$o :	$(srcdir)/frm_sub.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_sub.c -o ../objects/frm_sub$o

../objects/frm_user$o :	$(srcdir)/frm_user.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_user.c -o ../objects/frm_user$o

../objects/frm_win$o :	$(srcdir)/frm_win.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/frm_win.c -o ../objects/frm_win$o

../objects/fty_alnum$o :	$(srcdir)/fty_alnum.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fty_alnum.c -o ../objects/fty_alnum$o

../objects/fty_alpha$o :	$(srcdir)/fty_alpha.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fty_alpha.c -o ../objects/fty_alpha$o

../objects/fty_enum$o :	$(srcdir)/fty_enum.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fty_enum.c -o ../objects/fty_enum$o

../objects/fty_generic$o :	$(srcdir)/fty_generic.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fty_generic.c -o ../objects/fty_generic$o

../objects/fty_int$o :	$(srcdir)/fty_int.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fty_int.c -o ../objects/fty_int$o

../objects/fty_ipv4$o :	$(srcdir)/fty_ipv4.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fty_ipv4.c -o ../objects/fty_ipv4$o

../objects/fty_num$o :	$(srcdir)/fty_num.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fty_num.c -o ../objects/fty_num$o

../objects/fty_regex$o :	$(srcdir)/fty_regex.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_NORMAL) -c ../form/fty_regex.c -o ../objects/fty_regex$o


# generated by mk-1st.awk (subset=base+widechar+ext_funcs)
#  name:          formtw
#  traces:        DEBUG
#  MODEL:         PROFILE
#  model:         obj_p
#  prefix:        lib
#  suffix:        _p.a
#  subset:        base+widechar+ext_funcs
#  ShlibVer:      auto
#  ShlibVerInfix: no
#  SymLink:       ln -s -f
#  TermlibRoot:   tinfotw
#  TermlibSuffix: .a
#  ReLink:        no
#  DoLinks:       no
#  rmSoLocs:      no
#  ldconfig:      
#  overwrite:     no
#  depend:        ../include/ncurses_cfg.h ./form.priv.h
#  host:          i386-unknown-plan9

PROFILE_OBJS = \
	../obj_p/fld_arg$o \
	../obj_p/fld_attr$o \
	../obj_p/fld_current$o \
	../obj_p/fld_def$o \
	../obj_p/fld_dup$o \
	../obj_p/fld_ftchoice$o \
	../obj_p/fld_ftlink$o \
	../obj_p/fld_info$o \
	../obj_p/fld_just$o \
	../obj_p/fld_link$o \
	../obj_p/fld_max$o \
	../obj_p/fld_move$o \
	../obj_p/fld_newftyp$o \
	../obj_p/fld_opts$o \
	../obj_p/fld_pad$o \
	../obj_p/fld_page$o \
	../obj_p/fld_stat$o \
	../obj_p/fld_type$o \
	../obj_p/fld_user$o \
	../obj_p/frm_cursor$o \
	../obj_p/frm_data$o \
	../obj_p/frm_def$o \
	../obj_p/frm_driver$o \
	../obj_p/frm_hook$o \
	../obj_p/frm_opts$o \
	../obj_p/frm_page$o \
	../obj_p/frm_post$o \
	../obj_p/frm_req_name$o \
	../obj_p/frm_scale$o \
	../obj_p/frm_sub$o \
	../obj_p/frm_user$o \
	../obj_p/frm_win$o \
	../obj_p/fty_alnum$o \
	../obj_p/fty_alpha$o \
	../obj_p/fty_enum$o \
	../obj_p/fty_generic$o \
	../obj_p/fty_int$o \
	../obj_p/fty_ipv4$o \
	../obj_p/fty_num$o \
	../obj_p/fty_regex$o

$(PROFILE_OBJS) : ../include/ncurses_cfg.h ./form.priv.h

../lib/libformtw_p.a : $(PROFILE_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	$(RANLIB) $@

install \
install.libs \
install.formtw :: $(DESTDIR)$(libdir) ../lib/libformtw_p.a
	@echo installing ../lib/libformtw_p.a as $(DESTDIR)$(libdir)/libformtw_p.a
	$(INSTALL_DATA) ../lib/libformtw_p.a $(DESTDIR)$(libdir)/libformtw_p.a
	$(RANLIB) $(DESTDIR)$(libdir)/libformtw_p.a

uninstall \
uninstall.libs \
uninstall.formtw ::
	@echo uninstalling $(DESTDIR)$(libdir)/libformtw_p.a
	-@rm -f $(DESTDIR)$(libdir)/libformtw_p.a

clean ::
	-rm -f ../lib/libformtw_p.a

mostlyclean::
	-rm -f $(PROFILE_OBJS)

# generated by mk-2nd.awk
#   model:      obj_p
#   MODEL:      PROFILE
#   echo:       yes
#   subset:     base+widechar+ext_funcs
#   crenames:   yes
#   cxxrenames: 
#   traces:     DEBUG
#   srcdir:     .

../obj_p/fld_arg$o :	$(srcdir)/fld_arg.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_arg.c -o ../obj_p/fld_arg$o

../obj_p/fld_attr$o :	$(srcdir)/fld_attr.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_attr.c -o ../obj_p/fld_attr$o

../obj_p/fld_current$o :	$(srcdir)/fld_current.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_current.c -o ../obj_p/fld_current$o

../obj_p/fld_def$o :	$(srcdir)/fld_def.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_def.c -o ../obj_p/fld_def$o

../obj_p/fld_dup$o :	$(srcdir)/fld_dup.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_dup.c -o ../obj_p/fld_dup$o

../obj_p/fld_ftchoice$o :	$(srcdir)/fld_ftchoice.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_ftchoice.c -o ../obj_p/fld_ftchoice$o

../obj_p/fld_ftlink$o :	$(srcdir)/fld_ftlink.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_ftlink.c -o ../obj_p/fld_ftlink$o

../obj_p/fld_info$o :	$(srcdir)/fld_info.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_info.c -o ../obj_p/fld_info$o

../obj_p/fld_just$o :	$(srcdir)/fld_just.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_just.c -o ../obj_p/fld_just$o

../obj_p/fld_link$o :	$(srcdir)/fld_link.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_link.c -o ../obj_p/fld_link$o

../obj_p/fld_max$o :	$(srcdir)/fld_max.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_max.c -o ../obj_p/fld_max$o

../obj_p/fld_move$o :	$(srcdir)/fld_move.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_move.c -o ../obj_p/fld_move$o

../obj_p/fld_newftyp$o :	$(srcdir)/fld_newftyp.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_newftyp.c -o ../obj_p/fld_newftyp$o

../obj_p/fld_opts$o :	$(srcdir)/fld_opts.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_opts.c -o ../obj_p/fld_opts$o

../obj_p/fld_pad$o :	$(srcdir)/fld_pad.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_pad.c -o ../obj_p/fld_pad$o

../obj_p/fld_page$o :	$(srcdir)/fld_page.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_page.c -o ../obj_p/fld_page$o

../obj_p/fld_stat$o :	$(srcdir)/fld_stat.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_stat.c -o ../obj_p/fld_stat$o

../obj_p/fld_type$o :	$(srcdir)/fld_type.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_type.c -o ../obj_p/fld_type$o

../obj_p/fld_user$o :	$(srcdir)/fld_user.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fld_user.c -o ../obj_p/fld_user$o

../obj_p/frm_cursor$o :	$(srcdir)/frm_cursor.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_cursor.c -o ../obj_p/frm_cursor$o

../obj_p/frm_data$o :	$(srcdir)/frm_data.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_data.c -o ../obj_p/frm_data$o

../obj_p/frm_def$o :	$(srcdir)/frm_def.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_def.c -o ../obj_p/frm_def$o

../obj_p/frm_driver$o :	$(srcdir)/frm_driver.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_driver.c -o ../obj_p/frm_driver$o

../obj_p/frm_hook$o :	$(srcdir)/frm_hook.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_hook.c -o ../obj_p/frm_hook$o

../obj_p/frm_opts$o :	$(srcdir)/frm_opts.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_opts.c -o ../obj_p/frm_opts$o

../obj_p/frm_page$o :	$(srcdir)/frm_page.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_page.c -o ../obj_p/frm_page$o

../obj_p/frm_post$o :	$(srcdir)/frm_post.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_post.c -o ../obj_p/frm_post$o

../obj_p/frm_req_name$o :	$(srcdir)/frm_req_name.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_req_name.c -o ../obj_p/frm_req_name$o

../obj_p/frm_scale$o :	$(srcdir)/frm_scale.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_scale.c -o ../obj_p/frm_scale$o

../obj_p/frm_sub$o :	$(srcdir)/frm_sub.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_sub.c -o ../obj_p/frm_sub$o

../obj_p/frm_user$o :	$(srcdir)/frm_user.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_user.c -o ../obj_p/frm_user$o

../obj_p/frm_win$o :	$(srcdir)/frm_win.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/frm_win.c -o ../obj_p/frm_win$o

../obj_p/fty_alnum$o :	$(srcdir)/fty_alnum.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fty_alnum.c -o ../obj_p/fty_alnum$o

../obj_p/fty_alpha$o :	$(srcdir)/fty_alpha.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fty_alpha.c -o ../obj_p/fty_alpha$o

../obj_p/fty_enum$o :	$(srcdir)/fty_enum.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fty_enum.c -o ../obj_p/fty_enum$o

../obj_p/fty_generic$o :	$(srcdir)/fty_generic.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fty_generic.c -o ../obj_p/fty_generic$o

../obj_p/fty_int$o :	$(srcdir)/fty_int.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fty_int.c -o ../obj_p/fty_int$o

../obj_p/fty_ipv4$o :	$(srcdir)/fty_ipv4.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fty_ipv4.c -o ../obj_p/fty_ipv4$o

../obj_p/fty_num$o :	$(srcdir)/fty_num.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fty_num.c -o ../obj_p/fty_num$o

../obj_p/fty_regex$o :	$(srcdir)/fty_regex.c \
			$(HEADER_DEPS)
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS_PROFILE) -c ../form/fty_regex.c -o ../obj_p/fty_regex$o


# generated by mk-hdr.awk
#  subset:     ticlib+termlib+ext_tinfo base+widechar+ext_funcs
#  compat:     yes

${DESTDIR}${includedir} :
	mkdir -p $@

install \
install.libs \
install.includes :: ${AUTO_SRC} ${DESTDIR}${includedir} \
		$(srcdir)/form.h
	@ (cd ${DESTDIR}${includedir} && rm -f form.h) ; ../headers.sh ${INSTALL_DATA} ${DESTDIR}${includedir} ${srcdir} $(srcdir)/form.h

uninstall \
uninstall.libs \
uninstall.includes ::
	-@ (cd ${DESTDIR}${includedir} && rm -f form.h)
depend : ${AUTO_SRC}
	makedepend -- ${CPPFLAGS} -- ${C_SRC}

# DO NOT DELETE THIS LINE -- make depend depends on it.
