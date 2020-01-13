
INCLUDES = -I/usr/jens/dvl/apr-iconv-1.2.1/lib -I/usr/jens/dvl/apr-iconv-1.2.1/include  -I/sys/include/ape/apr-1 /sys/include/ape /386/include/ape

PROGRAMS = apriconv
TARGETS  = $(PROGRAMS)

# bring in rules.mk for standard functionality
include /usr/jens/dvl/apr-iconv-1.2.1/build/rules.mk

iconv_OBJECTS = iconv.lo iconv_stream.lo
iconv_LDADD   = ../lib/libapriconv-1.la
APR_LIBS      =  /386/lib/ape/libapr-1.a 

apriconv:	$(iconv_OBJECTS) $(iconv_LDADD)
	$(LINK) -o $@ $(iconv_OBJECTS) $(iconv_LDADD) $(LIBS) $(APR_LIBS)
