# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as
GCCDIR = /usr/local/nachos/decstation-ultrix/bin/
LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)


# if you aren't cross-compiling:
#GCCDIR =
#LDFLAGS = -N -T 0
#ASFLAGS =
#CPPFLAGS = -P $(INCDIR)


CC = $(GCCDIR)gcc
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = /lib/cpp
INCDIR =-I../userprog -I../threads -I../lib
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort test1 test2 test3 add yield1 yield2 printint log 

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.s > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

#halt.o: halt.c
#	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

#shell.o: shell.c
#	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

#sort.o: sort.c
#	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

#matmult.o: matmult.c
#	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

test1: test1.o start.o
	$(LD) $(LDFLAGS) start.o test1.o -o test1.coff
	../bin/coff2noff test1.coff test1
test2: test2.o start.o
	$(LD) $(LDFLAGS) start.o test2.o -o test2.coff
	../bin/coff2noff test2.coff test2
test3.o:test3.c
	$(CC) $(CFLAGS) -c test3.c
test3: test3.o start.o
	$(LD) $(LDFLAGS) start.o test3.o -o test3.coff
	../bin/coff2noff test3.coff test3
add.o: add.c
	$(CC) $(CFLAGS) -c add.c
add:	add.o start.o
	$(LD) $(LDFLAGS) start.o add.o -o add.coff
	../bin/coff2noff add.coff add

yield1.o: yield1.c
	$(CC) $(CFLAGS) -c yield1.c
yield1:	yield1.o start.o
	$(LD) $(LDFLAGS) start.o yield1.o -o yield1.coff
	../bin/coff2noff yield1.coff yield1

yield2.o: yield2.c
	$(CC) $(CFLAGS) -c yield2.c
yield2: yield2.o start.o
	$(LD) $(LDFLAGS) start.o yield2.o -o yield2.coff
	../bin/coff2noff yield2.coff yield2

log.o: log.c
	$(CC) $(CFLAGS) -c log.c
log: log.o start.o
	$(LD) $(LDFLAGS) start.o log.o -o log.coff
	../bin/coff2noff log.coff log


printint: printint.o start.o
	$(LD) $(LDFLAGS) start.o printint.o -o printint.coff
	../bin/coff2noff printint.coff printint
