# Makefile for 'common' module
#
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016
# updated by Temi Prioleau, January 2020

# PROG = 
OBJS = create.o 
OBJS1 = createTest.o
LIB = create.a
L = ../common
LL = ../solver
LIBS= $(L)/common.a
LLIBS = $(LL)/solve.a
PROG = createTest
UNITTEST=-DMYTEST


CFLAGS = -Wall -pedantic -std=c11 -ggdb -I $(LL) -I$(L)
MAKE = make
CC = gcc

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

create.o: ../solver/solve.h ../common/node.h ../common/grid.h  ../common/node.h  

$(PROG): create.c
	$(CC) $(CFLAGS) $(UNITTEST) $^ $(LIBS) $(LLIBS) -o $@

.PHONY: clean test

test: $(PROG)

all: $(LIB) $(PROG)

clean:
	rm -f *~ *.o *.dSYM
	rm -f *.a
