# GNU Makefile

CFLAGS = -Wall -g -lm

CmdLineArgs = polexpr entab2 detab2 entab3 detab3
PtrsToPtrs = sortlines sortlinesnoalloc ymd ymdptr
Explore = orderofop
CharPointFunc = strcat strend strn pointers
PointFuncArgs = getint getfloat

all: $(PointFuncArgs) $(CharPointFunc) $(Explore) $(PtrsToPtrs) $(CmdLineArgs)

detab3:
entab3:
detab2:
entab2:
polexpr:
ymdptr:
ymd:
sortlinesnoalloc: sortlinesnoalloc.o line.o
sortlinesnoalloc.o: line.o 
sortlines: sortlines.o alloc.o line.o
sortlines.o:
alloc.o: alloc.h
line.o: line.h
pointers:
strn:
orderofop:
strend:
strcat:
getfloat:
getint:

.PHONY: clean
clean:
	rm -f *~ *.o
