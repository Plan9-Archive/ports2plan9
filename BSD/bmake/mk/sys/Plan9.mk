#	$Id: Plan9.mk $
#

ROOT_GROUP= glenda
OS?=		Plan9
unix?= 		We run ${OS}
MACHINE=	uname -m
MACHINE_ARCH=	uname -m

Oext.i386= 8
Oext.amd64= 6
Oext.arm= 5
Oext.68000= 1
Oext.68020= 2
Oext.alpa= 7
Oext.power= q
Oext.power64= 9
Oext.spark= k
Oext.sparc64= u

Oext = ${Oext.${MACHINE}}

# some reasonable defaults
.SUFFIXES: .out .a .ln .${Oext} .o .s .S .c .cc .cpp .cxx .C .F .f .r .y .l .cl .p .h
.SUFFIXES: .sh .m4

.LIBS:		.a

tools = \
	ar \
	lorder \
	ranlib \
	tsort

.for t in ${tools}
${t:tu} := ${t:${M_whence}}
.endfor

# need to make sure this is set
MACHINE_ARCH.${MACHINE} ?= ${MACHINE}
.if empty(MACHINE_ARCH)
MACHINE_ARCH = ${MACHINE_ARCH.${MACHINE}}
.endif

.if !empty(TSORT)
TSORT += -q
.endif

ARFLAGS?=	rl

AS?=		${Oext}a
AFLAGS?=
COMPILE.s?=	${CC} ${AFLAGS} -c
LINK.s?=	${CC} ${AFLAGS} ${LDFLAGS}
COMPILE.S?=	${CC} ${AFLAGS} ${CPPFLAGS} -c -traditional-cpp
LINK.S?=	${CC} ${AFLAGS} ${CPPFLAGS} ${LDFLAGS}

# CC?=		pcc
#use ape/cc default to get .o object files. bmake needs to be run under ape/psh
CC?=		cc
DBG?=		
CFLAGS?=	${DBG}
COMPILE.c?=	${CC} ${CFLAGS} ${CPPFLAGS} -c
LINK.c?=	${CC} ${CFLAGS} ${CPPFLAGS} ${LDFLAGS}

# assumes that cfront is installed.
 CXX?=		/bin/c++/cfront
 CXXFLAGS?=	${CFLAGS}
 COMPILE.cc?=	${CXX} ${CXXFLAGS} ${CPPFLAGS} -c
 LINK.cc?=	${CXX} ${CXXFLAGS} ${CPPFLAGS} ${LDFLAGS}

# assumes that objc is installed.
 OBJC?=		/bin/objc
 OBJCFLAGS?=	${CFLAGS}
 COMPILE.m?=	${OBJC} ${OBJCFLAGS} ${CPPFLAGS} -c
 LINK.m?=	${OBJC} ${OBJCFLAGS} ${CPPFLAGS} ${LDFLAGS}

CPP?=		pcc
CPPFLAGS?=	

# assumes that f2c is installed. Uses bourne shell wrapper fc.
 FC?=		fc
 FFLAGS?=	
 RFLAGS?=
 COMPILE.f?=	${FC} ${FFLAGS} -c
 LINK.f?=	${FC} ${FFLAGS} ${LDFLAGS}
 COMPILE.F?=	${FC} ${FFLAGS} ${CPPFLAGS} -c
 LINK.F?=	${FC} ${FFLAGS} ${CPPFLAGS} ${LDFLAGS}
 COMPILE.r?=	${FC} ${FFLAGS} ${RFLAGS} -c
 LINK.r?=	${FC} ${FFLAGS} ${RFLAGS} ${LDFLAGS}

INSTALL?=	install

LEX?=		lex
LFLAGS?=
LEX.l?=		${LEX} ${LFLAGS}

LD?=		ld
LDFLAGS?=

LINT?=		lint
LINTFLAGS?=	-chapbxzF

MAKE?=		${.MAKE}

NM?=		nm

# this assumes that p2c is installed, needs perl
PC?=		p2cc
PFLAGS?=
COMPILE.p?=	${PC} ${PFLAGS} ${CPPFLAGS} -c
LINK.p?=	${PC} ${PFLAGS} ${CPPFLAGS} ${LDFLAGS}

SHELL?=		sh

SIZE?=		size

YACC?=		yacc
YFLAGS?=
YACC.y?=	${YACC} ${YFLAGS}

# C
.c:
	${LINK.c} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.c.o:
	${COMPILE.c} ${.IMPSRC}
.c.a:
	${COMPILE.c} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.c.ln:
	${LINT} ${LINTFLAGS} ${CPPFLAGS:M-[IDU]*} -i ${.IMPSRC}

# C++
.cc .cpp .cxx .C:
	${LINK.cc} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.cc.o .cpp.o .cxx.o .C.o:
	${COMPILE.cc} ${.IMPSRC}
.cc.a .cpp.a .cxx.a .C.a:
	${COMPILE.cc} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Fortran/Ratfor
.f:
	${LINK.f} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.f.o:
	${COMPILE.f} ${.IMPSRC}
.f.a:
	${COMPILE.f} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.F:
	${LINK.F} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.F.o:
	${COMPILE.F} ${.IMPSRC}
.F.a:
	${COMPILE.F} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.r:
	${LINK.r} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.r.o:
	${COMPILE.r} ${.IMPSRC}
.r.a:
	${COMPILE.r} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Pascal
.p:
	${LINK.p} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.p.o:
	${COMPILE.p} ${.IMPSRC}
.p.a:
	${COMPILE.p} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Assembly
.s:
	${LINK.s} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.s.o:
	${COMPILE.s} ${.IMPSRC}
.s.a:
	${COMPILE.s} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.S:
	${LINK.S} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.S.o:
	${COMPILE.S} ${.IMPSRC}
.S.a:
	${COMPILE.S} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Lex
.l:
	${LEX.l} ${.IMPSRC}
	${LINK.c} -o ${.TARGET} lex.yy.c ${LDLIBS} -ll
	rm -f lex.yy.c
.l.c:
	${LEX.l} ${.IMPSRC}
	mv lex.yy.c ${.TARGET}
.l.o:
	${LEX.l} ${.IMPSRC}
	${COMPILE.c} -o ${.TARGET} lex.yy.c 
	rm -f lex.yy.c

# Yacc
.y:
	${YACC.y} ${.IMPSRC}
	${LINK.c} -o ${.TARGET} y.tab.c ${LDLIBS}
	rm -f y.tab.c
.y.c:
	${YACC.y} ${.IMPSRC}
	mv y.tab.c ${.TARGET}
.y.o:
	${YACC.y} ${.IMPSRC}
	${COMPILE.c} -o ${.TARGET} y.tab.c
	rm -f y.tab.c

# Shell
.sh:
	rm -f ${.TARGET}
	cp ${.IMPSRC} ${.TARGET}

