
#
# Portable Object Compiler (c) 1996, 97. All Rights Reserved.
#

CD=cd
RM=rm

MKDIR=mkdir
TAR=tar
TARARGS=
INSTALLDIR=./build

default ::
	$(MAKE) cleanruntime
	$(MAKE) compiler
	$(MAKE) cakit
	$(MAKE) bootstrap
	$(MAKE) cleanruntime
	$(MAKE) runtime

runtime : objcrtr objpakr cakitr

compiler : objcrt objpak oclib objc

objcrt ::
	$(CD) src; $(CD) objcrt; $(MAKE)

objcrtr ::
	$(CD) src;$(CD) objcrt; $(MAKE) OBJC="objc -q -refcnt" LIBRARY=objcrtr.a

objpak ::
	$(CD) src; $(CD) objpak; $(MAKE)

objpakr ::
	$(CD) src;$(CD) objpak; $(MAKE) OBJC="objc -q -refcnt" LIBRARY=objpakr.a

oclib ::
	$(CD) src; $(CD) oclib;  $(MAKE)

objc ::
	$(CD) src; $(CD) objc;   $(MAKE)

cakit ::
	$(CD) src; $(CD) cakit;  $(MAKE)

cakitr ::
	$(CD) src;$(CD) cakit;$(MAKE) OBJC="objc -q -refcnt" LIBRARY=cakitr.a

browse ::
	objc -browse tmp browse.h
	cd tmp;cursel Menu.main


bootstrap :
	-$(CD) src; $(CD) objcrt; $(MAKE) bootstrap
	-$(CD) src; $(CD) objcrt; $(MAKE) LIBRARY=objcrtr.a bootstrap
	-$(CD) src; $(CD) objpak; $(MAKE) bootstrap
	-$(CD) src; $(CD) objpak; $(MAKE) LIBRARY=objpakr.a bootstrap
	-$(CD) src; $(CD) oclib;  $(MAKE) bootstrap
	-$(CD) src; $(CD) objc;   $(MAKE) bootstrap
	-$(CD) src; $(CD) cakit;  $(MAKE) bootstrap
	-$(CD) src; $(CD) cakit;  $(MAKE) LIBRARY=cakitr.a bootstrap

#
# tags file (vi -t isEqual , for example, brings you to isEqual)
# control-] for a classname also works.
#

tags :
	gawk -f ctags.awk src/objcrt/*.m src/objpak/*.m src/oclib/*.m > tags

#
# UNIX install.
#

install : bootstrap
	test -d $(INSTALLDIR) || $(MKDIR) $(INSTALLDIR)
	$(TAR) cf - $(TARARGS) bin lib man include | ( $(CD) ${INSTALLDIR}; $(TAR) xvf - $(TARARGS))

cleantmp :
	-$(CD) src; $(CD) objcrt; $(MAKE) cleantmp
	-$(CD) src; $(CD) objpak; $(MAKE) cleantmp
	-$(CD) src; $(CD) oclib;  $(MAKE) cleantmp
	-$(CD) src; $(CD) objc;   $(MAKE) cleantmp
	-$(CD) src; $(CD) cakit;  $(MAKE) cleantmp
	-$(CD) examples;          $(MAKE) cleantmp
	-$(CD) words;             $(MAKE) cleantmp

cleanruntime :
	-$(CD) src; $(CD) objcrt; $(MAKE) clean
	-$(CD) src; $(CD) objpak; $(MAKE) clean
	-$(CD) src; $(CD) cakit;  $(MAKE) clean

clean : cleanruntime
	-$(CD) src; $(CD) oclib;  $(MAKE) clean
	-$(CD) src; $(CD) objc;   $(MAKE) clean
	-$(CD) examples;          $(MAKE) clean
	-$(CD) words;             $(MAKE) clean

distclean :
	-$(RM) Makefile tags
	-$(RM) config.h config.cache config.log config.status
	-$(CD) src; $(CD) objcrt; $(MAKE) distclean
	-$(CD) src; $(CD) objpak; $(MAKE) distclean
	-$(CD) src; $(CD) oclib;  $(MAKE) distclean
	-$(CD) src; $(CD) objc;   $(MAKE) distclean
	-$(CD) src; $(CD) cakit;  $(MAKE) distclean
	-$(CD) examples;          $(MAKE) distclean
	-$(CD) words;             $(MAKE) distclean



