############################################################################
# Shenkar - Software Eng. Dept.
#
# Makefile for Programming 2 - Ex2
# Author David Avdat
# Date: 22-May-2026
#
#
#
############################################################################
# Feel free to change this file's content to fit your needs and file names #
############################################################################


CC     = gcc
CFLAGS = -Werror --pedantic-errors -std=c99 -no-pie

TEST1 = my_test1
TEST2 = my_test2

MAIN = main.c
PROG = TransportLL
OBJS = $(PROG).o
TEST = TEST1
OUT_FILE = $(TEST).out
ERR_FILE = $(TEST).err
REFILES  = > $(OUT_FILE) 2> $(ERR_FILE)

ifdef DEBUG
	CFLAGS += -DDEBUG
	REFILES = 
endif

help:
	@echo "Welcome to Programming 2 Ex2 Makefile :-)"
	@echo "-----------------------------------------"
	@echo "Usage: Note: operations inside [] are optional"
	@echo "make [help] - Shows this menu"
	@echo "make test1 [DEBUG=1] - Will compile and run test1."
	@echo "			If DEBUG=1 was added, output will contain debug printings. All output will be sent to screen"
	@echo "make test2 [DEBUG=1] - Will compile and run test2."
	@echo "			If DEBUG=1 was added, output will contain debug printings. All output will be sent to screen"
	@echo "clean" - Will remove all compilation and output products
	@echo ""
	@echo "Example: to run test 1 with debug prints use:"
	@echo "make test1 DEBUG=1"
	@echo "Good Luck!"

test1: TEST = TEST1
test1: test
test2: TEST = TEST2
test2: test

test: clean $(PROG)
	./$(PROG) $(REFILES)

$(PROG): $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -D$(TEST) $(OBJS) prog2_ex2.o $(MAIN) -o $@

$(PROG).o: $(PROG).c prog2_ex2.h $(PROG).h
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(PROG) TEST*
