# Makefile for these samples.
#
# Eli Bendersky [http://eli.thegreenplace.net]
# This code is in the public domain.
CC = gcc
CCFLAGS = -std=gnu99 -Wall -O0 -no-pie

EXECUTABLES = \
	hello \
	simple_tracer

.PHONY: all clean

all: $(EXECUTABLES)

hello: hello.c
	$(CC) $(CCFLAGS) $< -o $@

simple_tracer: simple_tracer.c
	$(CC) $(CCFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES) *.o *.a

