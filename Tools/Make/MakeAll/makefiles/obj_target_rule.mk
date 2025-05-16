#################################################################################################
# Define the rule that compiles a source file into an object file, using an auto-dependency file.
#################################################################################################
$(print-last-makefile)

# This building method combines the dependency generation and the object file generation into a single command.
# Based on Paul D. Smith's work as described here: http://make.mad-scientist.net/papers/advanced-auto-dependency-generation
#
# Each source file is compiled into an object file, with a corresponding dependency file.
#
# -MMD omits system headers from the generated dependencies
#
# $^: all prerequisites
# $@: target
# $<: first prerequisite
#
# c++filt: If there are errors, show C++ demangled function names.
# (https://sourceware.org/binutils/docs/binutils/c_002b_002bfilt.html)
#
# 2>&1: Redirect stderr (file descriptor 2), which carries error messages, to stdout (file descriptor 1). For the redirection to understand '1' as a file descriptor and not as a file name, '&' must be added.
# (https://stackoverflow.com/questions/818255/in-the-shell-what-does-21-mean)

DEPFLAGS    = -MT $@ -MMD -MP -MF $*.Td
POSTCOMPILE = mv -f $*.Td $*.d && touch $@

COMPILE.c = $(CC) $(CPPFLAGS) $(INCDIR) $(DEPFLAGS) -c

%.o : %$(src_ext) %.d
	$(COMPILE.c) -o $@ $< 2>&1 | c++filt
	$(POSTCOMPILE)

# load object dependency files (.d)
dep_files := $(objs:%.o=%.d)
$(dep_files):
$(info ... Load obj. dep. files (if exist):) $(foreach i, $(dep_files) , $(info ...    $(i)))
include $(wildcard $(dep_files))   # wildcard returns only existing dependency files, thus make won't complain about unfound include files (similar to using -include without wildcard)
