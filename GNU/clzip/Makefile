# Makefile for Clzip - Data compressor based on the LZMA algorithm
# Copyright (C) 2010, 2011 Antonio Diaz Diaz.
# This file was generated automatically by configure. Do not edit.
#
# This Makefile is free software: you have unlimited permission
# to copy, distribute and modify it.

pkgname = clzip
pkgversion = 1.2
progname = clzip
VPATH = .
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
datadir = $(prefix)/share
infodir = $(datadir)/info
mandir = $(datadir)/man
sysconfdir = $(prefix)/etc
CC = cc
CPPFLAGS = 
CFLAGS = -Wall -W -O2
LDFLAGS = 

DISTNAME = $(pkgname)-$(pkgversion)
INSTALL = install
INSTALL_PROGRAM = $(INSTALL) -p -m 755
INSTALL_DATA = $(INSTALL) -p -m 644
INSTALL_DIR = $(INSTALL) -d -m 755
SHELL = /bin/sh

objs = carg_parser.o decoder.o encoder.o main.o


.PHONY : all install install-info install-man install-strip \
         uninstall uninstall-info uninstall-man \
         doc info man check dist clean distclean

all : $(progname)

$(progname) : $(objs)
	$(CC) $(LDFLAGS) -o $@ $^

$(progname)_profiled : $(objs)
	$(CC) $(LDFLAGS) -pg -o $@ $^

main.o : main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -DPROGVERSION=\"$(pkgversion)\" -c -o $@ $<

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(objs)       : Makefile
carg_parser.o : carg_parser.h
decoder.o     : clzip.h decoder.h
encoder.o     : clzip.h encoder.h
main.o        : carg_parser.h clzip.h decoder.h encoder.h


doc : info man

info : $(VPATH)/doc/$(pkgname).info

$(VPATH)/doc/$(pkgname).info : $(VPATH)/doc/$(pkgname).texinfo
	cd $(VPATH)/doc && makeinfo $(pkgname).texinfo

man : $(VPATH)/doc/$(progname).1

$(VPATH)/doc/$(progname).1 : $(progname)
	help2man -n 'reduces the size of files' \
	  -o $@ ./$(progname)

Makefile : $(VPATH)/configure $(VPATH)/Makefile.in
	./config.status

check : all
	@$(VPATH)/testsuite/check.sh $(VPATH)/testsuite $(pkgversion)

install : all install-info install-man
	if [ ! -d "$(DESTDIR)$(bindir)" ] ; then $(INSTALL_DIR) "$(DESTDIR)$(bindir)" ; fi
	$(INSTALL_PROGRAM) ./$(progname) "$(DESTDIR)$(bindir)/$(progname)"

install-info :
	if [ ! -d "$(DESTDIR)$(infodir)" ] ; then $(INSTALL_DIR) "$(DESTDIR)$(infodir)" ; fi
	$(INSTALL_DATA) $(VPATH)/doc/$(pkgname).info "$(DESTDIR)$(infodir)/$(pkgname).info"
	-install-info --info-dir="$(DESTDIR)$(infodir)" $(DESTDIR)$(infodir)/$(pkgname).info

install-man :
	if [ ! -d "$(DESTDIR)$(mandir)/man1" ] ; then $(INSTALL_DIR) "$(DESTDIR)$(mandir)/man1" ; fi
	$(INSTALL_DATA) $(VPATH)/doc/$(progname).1 "$(DESTDIR)$(mandir)/man1/$(progname).1"

install-strip : all
	$(MAKE) INSTALL_PROGRAM='$(INSTALL_PROGRAM) -s' install

uninstall : uninstall-info uninstall-man
	-rm -f "$(DESTDIR)$(bindir)/$(progname)"

uninstall-info :
	-install-info --info-dir="$(DESTDIR)$(infodir)" --remove "$(DESTDIR)$(infodir)/$(pkgname).info"
	-rm -f "$(DESTDIR)$(infodir)/$(pkgname).info"

uninstall-man :
	-rm -f "$(DESTDIR)$(mandir)/man1/$(progname).1"

dist : doc
	ln -sf $(VPATH) $(DISTNAME)
	tar -cvf $(DISTNAME).tar \
	  $(DISTNAME)/AUTHORS \
	  $(DISTNAME)/COPYING \
	  $(DISTNAME)/ChangeLog \
	  $(DISTNAME)/INSTALL \
	  $(DISTNAME)/Makefile.in \
	  $(DISTNAME)/NEWS \
	  $(DISTNAME)/README \
	  $(DISTNAME)/configure \
	  $(DISTNAME)/doc/$(progname).1 \
	  $(DISTNAME)/doc/$(pkgname).info \
	  $(DISTNAME)/doc/$(pkgname).texinfo \
	  $(DISTNAME)/testsuite/check.sh \
	  $(DISTNAME)/testsuite/test.txt \
	  $(DISTNAME)/testsuite/test_sync.lz \
	  $(DISTNAME)/testsuite/test_v[01].lz \
	  $(DISTNAME)/*.h \
	  $(DISTNAME)/*.c
	rm -f $(DISTNAME)
	lzip -v -9 $(DISTNAME).tar

clean :
	-rm -f $(progname) $(progname)_profiled $(objs)

distclean : clean
	-rm -f Makefile config.status *.tar *.tar.lz
