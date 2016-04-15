# GNU Makefile

CFLAGS = -Wall -g -lm

PtrsToPtrs = sortlines sortlinesnoalloc ymd ymdptr polexpr
Explore = orderofop
CharPointFunc = strcat strend strn pointers
PointFuncArgs = getint getfloat

all: $(PointFuncArgs) $(CharPointFunc) $(Explore) $(PtrsToPtrs)

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
