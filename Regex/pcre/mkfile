</$objtype/mkfile
DIRS=doc 

all:V:
	mk -f mkfile.libpcre
	mk -f mkfile.libpcreposix
	mk -f mkfile.pcregrep
	mv $O.out $O.pcregrep
	mk -f mkfile.pcretest
	for (i in $DIRS)
		@{ cd $i; mk }

install:V:
	mk -f mkfile.libpcre $target
	mk -f mkfile.libpcreposix $target
	mk -f mkfile.pcregrep $target
	mv $O.out $O.pcregrep
	mk -f mkfile.pcretest $target
	for (i in $DIRS)
		@{ cd $i; mk $target }
	mv $O.pcregrep /$objtype/bin/pcregrep
	mv $O.out /$objtype/bin/pcretest
	mv libpcre.a$O /$objtype/lib/ape/libpcre.a
	mv libpcreposix.a$O /$objtype/lib/ape/libpcreposix.a
	mkdir -p /$objtype/lib/ape/pkgconfig
	cp pcre.pc  /$objtype/lib/ape/pkgconfig/
	cp pcreposix.pc  /$objtype/lib/ape/pkgconfig/
	cp pcre.h.ape /sys/include/ape/pcre.h
	cp pcreposix.h.ape /sys/include/ape/pcreposix.h
	chmod +x pcre-config
	cp pcre-config /rc/bin/ape

clean:V:
	mk -f mkfile.libpcre $target
	mk -f mkfile.libpcreposix $target
	mk -f mkfile.pcregrep $target
	rm -f $O.pcregrep
	mk -f mkfile.pcretest $target
	for (i in $DIRS)
		@{ cd $i; mk $target }

nuke:V:
	mk -f mkfile.libpcre $target
	mk -f mkfile.libpcreposix $target
	mk -f mkfile.pcregrep $target
	rm -f $O.pcregrep
	mk -f mkfile.pcretest $target
	for (i in $DIRS)
		@{ cd $i; mk $target }
	rm -f /$objtype/bin/pcregrep
	rm -f /$objtype/bin/pcretest
	rm -f /$objtype/lib/ape/libpcre.a
	rm -f /$objtype/lib/ape/libpcreposix.a
	rm -f /sys/include/ape/pcre.h
	rm -f /sys/include/ape/pcreposix.h
	rm -f /rc/bin/ape/pcre-config

