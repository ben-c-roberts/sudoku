# Makefile for CS50 Final Project: Sudoku
#
# C-Median: Thomas Clark, Daniel McClafferty, Kuzi Mutsvangwa, Ben Roberts
# May, 27, 2020

# Variables
PROG = sudoku
OBJS = sudoku.o
L = ./common
LL = ./creator
LLL = ./solver
LIBS = $(L)/common.a
LIBS1 = $(LL)/create.a
LIBS2 = $(LLL)/solve.a
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I $(L) -I $(LL) -I $(LLL)
CC = gcc
MAKE = make
NUM_TESTS = 10

$(PROG): $(OBJS) $(LIBS2) $(LIBS1) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJS): $(LLL)/solve.h $(LL)/create.h $(L)/shared.h $(L)/node.h $(L)/bag.h


# Phony targets
.PHONY: test clean libs cleanlibs
all: libs $(PROG)

libs:
	$(MAKE) -C common
	$(MAKE) -C solver
	$(MAKE) -C creator

test: $(PROG)
	./$(PROG) solve <testgrids/test1
	./$(PROG) solve <testgrids/test2
	./$(PROG) solve <testgrids/test3
testcreate: $(PROG)
	./$(PROG) create

fuzztest: 
	./testing.sh $(NUM_TESTS) &> testing.out

clean:
	rm -rf *.o
	rm -rf testing.out
	rm -rf *.dSYM
	rm -rf $(PROG)
	rm -rf core
	rm -rf vgcore.*
	$(MAKE) -C common clean
	$(MAKE) -C creator clean
	$(MAKE) -C solver clean
