#####################
# Compilation options
#####################
# My set of makefiles define several variables.
# To assign a value to such a variable, or to override one with a default value, use the command line.
# e.g. compiler, CC, is by default "g++", but you can override it to be "gcc":
# CC=gcc

# To assign a value to a C preprocessor, or to override one with a default value, use the command line.
# e.g. if the C code is: #define XYZ 111
# and you with to override it with 222, do:
# -DXYZ=222

# Not all make and compile options are assigned values in these makefiles.
# If you need to assign values to such options, do that on the command line, by assigning values to the EXTRA_OPTIONS variable, which starts out as an empty variable.
# e.g. to assign option xyz with the value 123, do:
# EXTRA_OPTIONS=-xyz=123

$(print-last-makefile)

# -------------------
# compilation options
# -------------------
# compiler, compiler path, warning level, C++ standard
# -ggdb to get line numbers in gdb
CC     :=g++
cc_path:=$(shell which $(CC))
CC_STD :=-std=c++14
WARNING:=-Wall

ifeq ($(BUILD), debug)
DEBUG  :=-g
OPT    :=-O0 -ggdb
else ifeq ($(BUILD), release)
DEBUG  :=
OPT    :=-O3
else ifeq ($(BUILD), profile)
DEBUG  :=
OPT    :=
endif

# command line extra options (starts empty)
EXTRA_OPTIONS :=

# all compilation flags together:
CPPFLAGS :=$(CC_STD) $(WARNING) $(DEBUG) $(OPT) $(EXTRA_OPTIONS)

$(info ... Compiler  : $(cc_path))
$(info ... CPPFLAGS  : $(CPPFLAGS))
