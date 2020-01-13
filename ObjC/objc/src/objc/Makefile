
#
# Portable Object Compiler (c) 1997,98.  All Rights Reserved. 
# $Id: Makefile.in,v 1.3 2002/05/18 10:57:50 stes Exp $
#

#
# This Makefile should work with UNIX make (like SysV, BSD, GNU make)
#

CD=cd
MKDIR=mkdir
STRIP=strip
CHMOD=chmod
RM=rm -f
CP=cp -p
AR=ar cr
FINAL_AR=echo
RANLIB=ranlib

YACC=byacc -d
LEX=flex
YTABH=y.tab.h
YTABC=y.tab.c
LEXYYC=lex.yy.c
DBG_MFLAGS=-DDEBUG -g
OPT_MFLAGS=-DNDEBUG
OBJSUFFIX=$O
LIBSUFFIX=a
BOOTDIR=../..
BINDIR=$(BOOTDIR)/bin
LIBDIR=$(BOOTDIR)/lib
IFLAGS=-I. -I../../include/objcrt -I../../include/objpak -I../oclib
BOOTLIBS= ../oclib/oclib.a ../objpak/objpak.a ../objcrt/objcrt.a
DEPENDLIBS=../objcrt/objcrt.$(LIBSUFFIX) \
           ../objpak/objpak.$(LIBSUFFIX) \
           ../oclib/oclib.$(LIBSUFFIX)
MFLAGS=$(OPT_MFLAGS)

#
# Because this directory will contain a new compiler,
# make sure we configure with a full path towards the old compiler.
#

OBJC=/bin/objc
.SUFFIXES: .m .lm .ym

OBJCSCRIPT=objc
OBJCPROGRAM=objc.exe
OBJC1PROGRAM=objc1
POSTLINK=postlink

OBJCFILES=\
	objc.$(OBJSUFFIX)

OBJC1FILES=\
	yacc.$(OBJSUFFIX)\
	lex.$(OBJSUFFIX)\
	lexfiltr.$(OBJSUFFIX)\
	objc1.$(OBJSUFFIX)

PRELINKFILE=\
	_prelink.$(OBJSUFFIX)

PREDLLFILE=\
	_predll.$(OBJSUFFIX)

POSTLINKFILES=\
	postlink.$(OBJSUFFIX)

.m.$(OBJSUFFIX):
	$(OBJC) -c $*.m $(MFLAGS) $(IFLAGS)

.lm.$(OBJSUFFIX):
	$(LEX) $*.lm
	-$(CP) $(LEXYYC) $*.m
	$(OBJC) -c $(MFLAGS) $(IFLAGS) $*.m
	-$(RM) $(LEXYYC)
	-$(RM) $*.m

.ym.$(OBJSUFFIX):
	$(YACC) $*.ym
	-$(CP) $(YTABH) $*.h
	-$(CP) $(YTABC) $*.m
	$(OBJC) -c $(MFLAGS) $(IFLAGS) $*.m
	-$(RM) $(YTABC)
	-$(RM) $*.m

default : $(OBJC1PROGRAM) $(PRELINKFILE) $(PREDLLFILE) $(POSTLINK)

$(OBJCPROGRAM) : $(OBJCFILES) $(DEPENDLIBS)
	$(OBJC) $(OBJCFILES) $(BOOTLIBS) -o $(OBJCPROGRAM)

$(OBJC1PROGRAM) : $(OBJC1FILES) $(DEPENDLIBS)
	$(OBJC) $(OBJC1FILES) $(BOOTLIBS) -o $(OBJC1PROGRAM)

$(PRELINKFILE) : _prelink.c
	$(OBJC) -c _prelink.c

$(PREDLLFILE) : _predll.c
	$(OBJC) -c _predll.c

$(POSTLINK) : $(POSTLINKFILES) $(DEPENDLIBS)
	$(OBJC) $(POSTLINKFILES) $(BOOTLIBS) -o $(POSTLINK)

bootstrap : 
	-test -d $(BINDIR) || $(MKDIR) $(BINDIR)
	-$(CP) $(OBJCSCRIPT) $(BINDIR)
	-$(CHMOD) 755 $(BINDIR)/$(OBJCSCRIPT)
	-$(CP) $(OBJC1PROGRAM) $(BINDIR)
	-$(STRIP) $(BINDIR)/$(OBJC1PROGRAM)
	-$(CHMOD) 755 $(BINDIR)/$(OBJC1PROGRAM)
	-$(CP) $(PRELINKFILE) $(LIBDIR)
	-$(CHMOD) 644 $(LIBDIR)/$(PRELINKFILE)
	-$(CP) $(PREDLLFILE) $(LIBDIR)
	-$(CHMOD) 644 $(LIBDIR)/$(PREDLLFILE)
	-$(CP) $(POSTLINK) $(BINDIR)
	-$(CHMOD) 755 $(BINDIR)/$(POSTLINK)
	-$(CP) cvtimport $(BINDIR)
	-$(CHMOD) 755 $(BINDIR)/cvtimport
	-$(CP) objchelp.txt $(LIBDIR)
	-$(CHMOD) 644 $(LIBDIR)/objchelp.txt
	-$(CP) objcdlso.ld $(LIBDIR)
	-$(CHMOD) 644 $(LIBDIR)/objcdlso.ld

cleantmp :
	-$(RM) *.P
	-$(RM) *.i
	-$(RM) y.tab.h y.output y.tab.c

clean : cleantmp
	-$(RM) *.$(OBJSUFFIX)
	-$(RM) *.$(LIBSUFFIX)
	-$(RM) objc.m yacc.m lex.m
	-$(RM) $(OBJCPROGRAM)
	-$(RM) $(OBJC1PROGRAM)
	-$(RM) $(POSTLINK)

distclean : clean
	-$(RM) $(OBJCSCRIPT) 
	-$(RM) Makefile 
	-$(RM) config.h 

