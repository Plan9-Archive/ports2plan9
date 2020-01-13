
#
# Portable Object Compiler
# $Id: Makefile.in,v 1.3 2003/10/12 10:01:34 stes Exp $
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
OBJSUFFIX=o
LIBSUFFIX=$O
BOOTDIR=../..
LIBDIR=$(BOOTDIR)/lib
IFLAGS=-noI -I../../include/objcrt
MFLAGS=$(OPT_MFLAGS)

.SUFFIXES: .m

LIBRARY=objpak.$(LIBSUFFIX)
SHLIB=libobjpak.so

OBJFILES=\
	ascfiler.$(OBJSUFFIX)\
	  notfound.$(OBJSUFFIX)\
	  outofbnd.$(OBJSUFFIX)\
	  unknownt.$(OBJSUFFIX)\
	  typeinc.$(OBJSUFFIX)\
	  badvers.$(OBJSUFFIX)\
	cltn.$(OBJSUFFIX)\
	  ordcltn.$(OBJSUFFIX)\
	  sortcltn.$(OBJSUFFIX)\
	  set.$(OBJSUFFIX)\
	  bag.$(OBJSUFFIX)\
	  stack.$(OBJSUFFIX)\
	  runarray.$(OBJSUFFIX)\
        dictnary.$(OBJSUFFIX)\
	sequence.$(OBJSUFFIX)\
	array.$(OBJSUFFIX)\
	  ocstring.$(OBJSUFFIX)\
	  idarray.$(OBJSUFFIX)\
	  intarray.$(OBJSUFFIX)\
	rectangl.$(OBJSUFFIX)\
	point.$(OBJSUFFIX)\
	assoc.$(OBJSUFFIX)\
	objgraph.$(OBJSUFFIX)\
	cltnseq.$(OBJSUFFIX)\
	keyseq.$(OBJSUFFIX)\
	valueseq.$(OBJSUFFIX)\
	setseq.$(OBJSUFFIX)\
	bagseq.$(OBJSUFFIX)\
	treeseq.$(OBJSUFFIX)\
	octext.$(OBJSUFFIX)\
	txtstyle.$(OBJSUFFIX)\
	paragrph.$(OBJSUFFIX)\
	txtattr.$(OBJSUFFIX)

.m.o:
	$(OBJC) -c $*.m $(MFLAGS) $(IFLAGS)
	$(AR) $(LIBRARY) $@ 

$(LIBRARY) : $(OBJFILES)
	$(FINAL_AR) $(LIBRARY) $(OBJFILES)
	$(RANLIB) $(LIBRARY)

shlib : $(OBJFILES)
	objc -dl $(OBJFILES) -o $(SHLIB)

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
	-$(RM) $(SHLIB)

distclean : clean
	-$(RM) Makefile 
	-$(RM) config.h 

