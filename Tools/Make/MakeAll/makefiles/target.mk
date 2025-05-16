########################################################################################
# Create a build directory, switch to it, and call the top-level Makefile in a sub-shell
########################################################################################
# when gmake is executed in the source directory, the top-level Makefile will include this file.

$(info +   Included  : $(realpath $(lastword $(MAKEFILE_LIST))))

# remove all implicit rules, so that only those in my makefiles are used.
.SUFFIXES:

# call the top-level Makefile again, this time from the build directory:
# Based on Paul D. Smith's work as described here: http://make.mad-scientist.net/papers/multi-architecture-builds/
#
# -C tells make to change directory before doing anything.
# -f calls on the top-level Makefile, while using the CURDIR of the 1st call (where Makefile resides).
# call_dir=$(CURDIR) where top-level Makefile resides.
# MAKECMDGOALS is a list of targets given to the top-level Makefile, but not command line options nor variable assignments.
MAKETARGET = $(MAKE) --no-print-directory -C $@ -f $(CURDIR)/Makefile call_dir=$(CURDIR) $(MAKECMDGOALS)

# ensure there's a build_dir: either already exists (-d $@) or make it.
# then execute the top-level Makefile for a 2nd time.

# @ prevents make from printing the command before execution.
# silence output, unless QUIET is defined on the command line.
QUIET ?= @

# $@: target

.PHONY: $(build_dir)
$(build_dir):
	+$(QUIET)[ -d $@ ] || mkdir -p $@
	+$(QUIET)$(MAKETARGET)

Makefile : ;
%.mk :: ;

% :: $(build_dir) ; :

# clean rule removes build_dir
.PHONY: clean
clean:
	rm -rf $(build_dir)
