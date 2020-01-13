include config.mk

.POSIX:
.SUFFIXES: .c .o

HDR = fs.h text.h util.h arg.h
LIB = \
	util/afgets.o    \
	util/agetcwd.o   \
	util/apathmax.o  \
	util/concat.o    \
	util/cp.o        \
	util/enmasse.o   \
	util/eprintf.o   \
	util/estrtol.o   \
	util/fnck.o      \
	util/getlines.o  \
	util/putword.o   \
	util/recurse.o   \
	util/rm.o

#basename and dirname need libgen.h
#	basename.c \
#	dirname.c  \

SRC = \
	cat.c      \
	chmod.c    \
	chown.c    \
	cksum.c    \
	cmp.c      \
	cp.c       \
	date.c     \ 
	echo.c     \
	false.c    \
	fold.c     \
	grep.c     \
	head.c     \
	kill.c     \
	ln.c       \
	ls.c       \
	mc.c       \
	mkdir.c    \
	mkfifo.c   \
	mv.c       \
	nl.c       \
	nohup.c    \
	pwd.c      \
	rm.c       \
	sleep.c    \
	sort.c     \
	tail.c     \
	tee.c      \
	test.c     \
	touch.c    \
	true.c     \
	tty.c      \
	uname.c    \
	uniq.c     \
	seq.c      \
	wc.c       \
	yes.c

OBJ = $(SRC:.c=.o) $(LIB)
BIN = $(SRC:.c=)
MAN = $(SRC:.c=.1)

all: $(BIN)

$(OBJ): util.h config.mk
$(BIN): util.a
cat.o fold.o grep.o nl.o sort.o tail.o uniq.o: text.h
cp.o mv.o rm.o: fs.h

.o:
	@echo LD $@
	@$(LD) $@ $< util.a $(LDFLAGS)

.c.o:
	@echo CC $<
	@$(CC) $@ $< $(CFLAGS)

util.a: $(LIB)
	@echo AR $@
	@$(AR) -r -c $@ $(LIB)
	@ranlib $@

install: all
	@echo installing executables to $(DESTDIR)$(PREFIX)/bin/ape
	@mkdir -p $(DESTDIR)$(PREFIX)/bin/ape
	@cp -f $(BIN) $(DESTDIR)$(PREFIX)/bin/ape
	@cd $(DESTDIR)$(PREFIX)/bin && chmod 755 $(BIN)
	@echo installing manual pages to $(DESTDIR)$(MANPREFIX)/1ape
	@mkdir -p $(DESTDIR)$(MANPREFIX)/1ape
	@cp -f $(MAN) $(DESTDIR)$(MANPREFIX)/1ape
	@cd $(DESTDIR)$(MANPREFIX)/man1 && chmod 644 $(MAN)

uninstall:
	@echo removing executables from $(DESTDIR)$(PREFIX)/bin/ape
	@cd $(DESTDIR)$(PREFIX)/bin/ape && rm -f $(BIN)
	@echo removing manual pages from $(DESTDIR)$(MANPREFIX)/man1
	@cd $(DESTDIR)$(MANPREFIX)/1ape && rm -f $(MAN)

dist: clean
	@echo creating dist tarball
	@mkdir -p sbase-$(VERSION)
	@cp -r LICENSE Makefile config.mk $(SRC) $(MAN) util $(HDR) sbase-$(VERSION)
	@tar -cf sbase-$(VERSION).tar sbase-$(VERSION)
	@gzip sbase-$(VERSION).tar
	@rm -rf sbase-$(VERSION)

sbase-box: $(SRC) util.a
	@echo creating box binary
	@mkdir -p build
	@cp $(HDR) build
	@for f in $(SRC); do sed "s/^main(/`basename $$f .c`_&/" < $$f > build/$$f; done
	@echo '#include <libgen.h>'  > build/$@.c
	@echo '#include <stdlib.h>' >> build/$@.c
	@echo '#include <string.h>' >> build/$@.c
	@echo '#include "util.h"'   >> build/$@.c
	@for f in $(SRC); do echo "int `basename $$f .c`_main(int, char **);" >> build/$@.c; done
	@echo 'int main(int argc, char *argv[]) { char *s = basename(argv[0]); if(0) ;' >> build/$@.c
	@for f in $(SRC); do echo "else if(!strcmp(s, \"`basename $$f .c`\")) `basename $$f .c`_main(argc, argv);" >> build/$@.c; done
	@printf 'else eprintf("%%s: unknown program\\n", s); return EXIT_SUCCESS; }\n' >> build/$@.c
	@echo LD $@
	@$(LD) -o $@ build/*.c util.a $(CFLAGS) $(LDFLAGS)
	@rm -r build

clean:
	@echo cleaning
	@rm -f $(BIN) $(OBJ) $(LIB) util.a sbase-box
