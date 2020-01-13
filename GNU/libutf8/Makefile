# Generated automatically from Makefile.in by configure.
# Makefile for libutf8

#### Start of system configuration section. ####

# Directories used by "make":
srcdir = .

# Directories used by "make install":
prefix = $(DESTDIR)
local_prefix = $(DESTDIR)
exec_prefix = $(prefix)
libdir = $(exec_prefix)/lib
includedir = $(prefix)/include
mandir = $(prefix)/man

# Programs used by "make":
RM = rm -f


# Programs used by "make install":
INSTALL = /bin/install -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644

#### End of system configuration section. ####

SHELL = /bin/sh

all : force
	cd src; $(MAKE) -r all
	cd man; $(MAKE) -r all

install : force
	cd src; $(MAKE) -r install prefix='$(prefix)' exec_prefix='$(exec_prefix)' libdir='$(libdir)'
	if [ ! -d $(prefix) ] ; then mkdir $(prefix) ; fi
	if [ ! -d $(exec_prefix) ] ; then mkdir $(exec_prefix) ; fi
	if [ ! -d $(includedir) ] ; then mkdir $(includedir) ; fi
	if [ ! -d $(includedir)/utf8 ] ; then mkdir $(includedir)/utf8 ; fi
	$(INSTALL_DATA) $(srcdir)/include/libutf8.h $(includedir)/libutf8.h
	$(INSTALL_DATA) include/utf8/config.h $(includedir)/utf8/config.h
	$(INSTALL_DATA) include/utf8/types.h $(includedir)/utf8/types.h
	$(INSTALL_DATA) include/utf8/wchar.h $(includedir)/utf8/wchar.h
	$(INSTALL_DATA) $(srcdir)/include/utf8/stdlib.h $(includedir)/utf8/stdlib.h
	$(INSTALL_DATA) $(srcdir)/include/utf8/locale.h $(includedir)/utf8/locale.h
	$(INSTALL_DATA) $(srcdir)/include/utf8/limits.h $(includedir)/utf8/limits.h
	$(INSTALL_DATA) $(srcdir)/include/utf8/wctype.h $(includedir)/utf8/wctype.h
	$(INSTALL_DATA) $(srcdir)/include/utf8/stdio.h $(includedir)/utf8/stdio.h
	cd man; $(MAKE) -r install prefix='$(prefix)' exec_prefix='$(exec_prefix)' mandir='$(mandir)'

installdirs : force
	cd src; $(MAKE) -r installdirs prefix='$(prefix)' exec_prefix='$(exec_prefix)' libdir='$(libdir)'
	if [ ! -d $(prefix) ] ; then mkdir $(prefix) ; fi
	if [ ! -d $(exec_prefix) ] ; then mkdir $(exec_prefix) ; fi
	if [ ! -d $(includedir) ] ; then mkdir $(includedir) ; fi
	if [ ! -d $(includedir)/utf8 ] ; then mkdir $(includedir)/utf8 ; fi
	cd man; $(MAKE) -r installdirs prefix='$(prefix)' exec_prefix='$(exec_prefix)' mandir='$(mandir)'

uninstall : force
	cd src; $(MAKE) -r uninstall prefix='$(prefix)' exec_prefix='$(exec_prefix)' libdir='$(libdir)'
	$(RM) $(includedir)/libutf8.h
	$(RM) $(includedir)/utf8/config.h
	$(RM) $(includedir)/utf8/types.h
	$(RM) $(includedir)/utf8/wchar.h
	$(RM) $(includedir)/utf8/stdlib.h
	$(RM) $(includedir)/utf8/locale.h
	$(RM) $(includedir)/utf8/limits.h
	$(RM) $(includedir)/utf8/wctype.h
	$(RM) $(includedir)/utf8/stdio.h
	-rmdir $(includedir)/utf8
	cd man; $(MAKE) -r uninstall prefix='$(prefix)' exec_prefix='$(exec_prefix)' mandir='$(mandir)'

check : force
	cd src; $(MAKE) -r check
	cd man; $(MAKE) -r check

mostlyclean : force
	cd src; $(MAKE) -r mostlyclean
	cd man; $(MAKE) -r mostlyclean

clean : force
	cd src; $(MAKE) -r clean
	cd man; $(MAKE) -r clean

distclean : force
	cd src; if test -f Makefile; then $(MAKE) -r distclean; fi
	cd man; if test -f Makefile; then $(MAKE) -r distclean; fi
	$(RM) config.status config.log config.cache Makefile libtool
	$(RM) include/utf8/config.h include/utf8/types.h include/utf8/wchar.h

maintainer-clean : force
	cd src; if test -f Makefile; then $(MAKE) -r maintainer-clean; fi
	cd man; if test -f Makefile; then $(MAKE) -r maintainer-clean; fi
	$(RM) config.status config.log config.cache Makefile libtool
	$(RM) include/utf8/config.h include/utf8/types.h include/utf8/wchar.h

force :

