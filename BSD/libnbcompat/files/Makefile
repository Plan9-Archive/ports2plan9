# $NetBSD: Makefile.in,v 1.36 2009/06/05 19:58:04 joerg Exp $
#

srcdir=		.
prefix= 	/sys

SHELL=		/bin/sh

CC=		cc
CCLD=		cc
CFLAGS=		-I$(srcdir) -I.  -D_POSIX_SOURCE -D_SUSV2_SOURCE -D_RESEARCH_SOURCE -D_BSD_EXTENSION -D_C99_SNPRINTF_EXTENSION -D_REGEXP_EXTENSION
CPPFLAGS=	
DEFS=		-DHAVE_CONFIG_H
INSTALL=	./install-sh -c
LIBMODE?=	644
LDFLAGS=	

AWK=		awk
AR=		ar
RANLIB=		ranlib

LIB=		libnbcompat.a

INCS=		nbcompat.h \
		nbcompat/assert.h \
		nbcompat/cdefs.h \
		nbcompat/ctype.h \
		nbcompat/dirent.h \
		nbcompat/endian.h \
		nbcompat/err.h \
		nbcompat/fnmatch.h \
		nbcompat/fts.h \
		nbcompat/getopt.h \
		nbcompat/glob.h \
		nbcompat/grp.h \
		nbcompat/limits.h \
		nbcompat/md5.h \
		nbcompat/nbconfig.h \
		nbcompat/netdb.h \
		nbcompat/param.h \
		nbcompat/paths.h \
		nbcompat/poll.h \
		nbcompat/pwd.h \
		nbcompat/queue.h \
		nbcompat/regex.h \
		nbcompat/rmd160.h \
		nbcompat/sha1.h \
		nbcompat/sha2.h \
		nbcompat/stat.h \
		nbcompat/statvfs.h \
		nbcompat/stdbool.h \
		nbcompat/stdio.h \
		nbcompat/stdlib.h \
		nbcompat/string.h \
		nbcompat/termcap.h \
		nbcompat/time.h \
		nbcompat/types.h \
		nbcompat/tzfile.h \
		nbcompat/unistd.h \
		nbcompat/util.h \
		nbcompat/vis.h

OBJS=		 ${LIBOBJDIR}glob$U.o ${LIBOBJDIR}regcomp$U.o ${LIBOBJDIR}regerror$U.o ${LIBOBJDIR}regexec$U.o ${LIBOBJDIR}regfree$U.o ${LIBOBJDIR}md5c$U.o ${LIBOBJDIR}md5hl$U.o ${LIBOBJDIR}rmd160$U.o ${LIBOBJDIR}rmd160hl$U.o ${LIBOBJDIR}sha1$U.o ${LIBOBJDIR}sha1hl$U.o ${LIBOBJDIR}sha2$U.o ${LIBOBJDIR}sha2hl$U.o ${LIBOBJDIR}getopt$U.o ${LIBOBJDIR}getopt_long$U.o ${LIBOBJDIR}vis$U.o ${LIBOBJDIR}unvis$U.o ${LIBOBJDIR}asprintf$U.o ${LIBOBJDIR}err$U.o ${LIBOBJDIR}fgetln$U.o ${LIBOBJDIR}fnmatch$U.o ${LIBOBJDIR}fparseln$U.o ${LIBOBJDIR}isblank$U.o ${LIBOBJDIR}lchflags$U.o ${LIBOBJDIR}lchmod$U.o ${LIBOBJDIR}lchown$U.o ${LIBOBJDIR}lutimes$U.o ${LIBOBJDIR}mkdtemp$U.o ${LIBOBJDIR}mkstemp$U.o ${LIBOBJDIR}setenv$U.o ${LIBOBJDIR}setgroupent$U.o ${LIBOBJDIR}setpassent$U.o ${LIBOBJDIR}setprogname$U.o ${LIBOBJDIR}shquote$U.o ${LIBOBJDIR}statvfs$U.o ${LIBOBJDIR}strlcat$U.o ${LIBOBJDIR}strlcpy$U.o ${LIBOBJDIR}strmode$U.o ${LIBOBJDIR}strsep$U.o ${LIBOBJDIR}unsetenv$U.o ${LIBOBJDIR}usleep$U.o ${LIBOBJDIR}utimes$U.o ${LIBOBJDIR}warn$U.o ${LIBOBJDIR}getaddrinfo$U.o ${LIBOBJDIR}findenv$U.o ${LIBOBJDIR}gettemp$U.o ${LIBOBJDIR}setmode$U.o ${LIBOBJDIR}pwcache$U.o ${LIBOBJDIR}fts$U.o ${LIBOBJDIR}timegm$U.o ${LIBOBJDIR}poll$U.o ${LIBOBJDIR}snprintf$U.o

WITH_DB=	

.if ${WITH_DB} == "yes"
.  include "${.CURDIR}/db/Makefile.inc"
.endif

LINK=		$(CCLD) $(CFLAGS) $(LDFLAGS) -o $@
COMPILE=	$(CC) $(CPPFLAGS) $(CFLAGS)

all: nbcompat/nbconfig.h $(LIB)

.c.o:
	$(COMPILE) $(DEFS) -c $<

$(LIB): $(OBJS)
	$(AR) cr $@ $(OBJS)
	$(RANLIB) $@

nbcompat/nbconfig.h: nbcompat/config.h nbcompat.awk
	$(AWK) -f nbcompat.awk nbcompat/config.h > $@

install:
	$(INSTALL) -m 755 -d ${DESTDIR}$(prefix)/lib
	$(INSTALL) -m $(LIBMODE) ${LIB} ${DESTDIR}$(prefix)/lib
	$(RANLIB) ${DESTDIR}$(prefix)/lib/$(LIB)
	$(INSTALL) -m 755 -d ${DESTDIR}$(prefix)/include
	$(INSTALL) -m 755 -d ${DESTDIR}$(prefix)/include/nbcompat
	@for file in $(INCS); do \
		echo "$(INSTALL) -m 444 $$file ${DESTDIR}$(prefix)/include/$$file"; \
		$(INSTALL) -m 444 $$file ${DESTDIR}$(prefix)/include/$$file; \
	done

clean:
	rm -f *.a *.o bits nbcompat/nbcompat.h

distclean: clean
	rm -f Makefile config.log config.status configure.lineno
	rm -f nbcompat/config.h nbcompat/nbconfig.h
