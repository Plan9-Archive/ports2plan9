# sbase version
VERSION = 0.0

# paths
PREFIX = /$objtype
MANPREFIX = /sys/man

#Plan9/APE settings (run make under ape/psh)
CC = cc
LD = ld
CFLAGS = "-I. -D_POSIX_SOURCE -D_SUSV2_SOURCE -D_BSD_EXTENSION" 

#CC = gcc
#CC = musl-gcc
#LD = $(CC)
#CPPFLAGS = -D_POSIX_C_SOURCE=200112L
#CFLAGS   = -g -ansi -Wall -pedantic $(CPPFLAGS)
#LDFLAGS  = -g

#CC = tcc
#LD = $(CC)
#CPPFLAGS = -D_POSIX_C_SOURCE=200112L
#CFLAGS   = -Os -Wall $(CPPFLAGS)
#LDFLAGS  =
