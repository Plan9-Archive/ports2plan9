
#
# Portable Object Compiler
# $Id: Makefile.in,v 1.3 2003/09/27 09:32:44 stes Exp $
#

#
# This Makefile should work with UNIX make's (like SysV, BSD, GNU make)
#

MKDIR=mkdir
OBJC=objc -q
RM=rm -f
CP=cp -p
AR=ar cr
FINAL_AR=echo
RANLIB=ranlib

DBG_MFLAGS=-DDEBUG -g
OPT_MFLAGS=-DNDEBUG
OBJSUFFIX=$O
LIBSUFFIX=a
BOOTDIR=../..
LIBDIR=$(BOOTDIR)/lib
IFLAGS=-noI
MFLAGS=$(OPT_MFLAGS)

.SUFFIXES: .m 

LIBRARY=objcrt.$(LIBSUFFIX)

OBJFILES=\
	Object.$(OBJSUFFIX)\
	Block.$(OBJSUFFIX)\
	Message.$(OBJSUFFIX)\
	Exceptn.$(OBJSUFFIX)\
	OutOfMem.$(OBJSUFFIX)\
	objcrt.$(OBJSUFFIX)

.m.o:
	$(OBJC) -c $*.m $(MFLAGS) $(IFLAGS)
	$(AR) $(LIBRARY) $@ 

$(LIBRARY) : $(OBJFILES)
	$(FINAL_AR) $(LIBRARY) $(OBJFILES)
	$(RANLIB) $(LIBRARY)


bootstrap :
	test -d $(LIBDIR) || $(MKDIR) $(LIBDIR)
	-$(CP) $(LIBRARY) $(LIBDIR)

cleantmp :
	-$(RM) *.P
	-$(RM) *.c
	-$(RM) *.i

clean : cleantmp
	-$(RM) *.$(OBJSUFFIX)
	-$(RM) *.$(LIBSUFFIX)

distclean : clean
	-$(RM) Makefile 
	-$(RM) config.h 

