######################
# Build a library test
######################
# This is the top-level gmake Makefile to build a test for a library.
# Call this file from the source directory.
#
# Before calling this Makefile, define 2 environment variables:
# TOT           points to the base directory of ALL your code.
# MAKEFILES_DIR points to the directory with common Makefiles, used during a build.
#
# Build types are defined in build_type.mk.
# You can override the default type value on the command line.
# e.g. to select "release", do:
# gmake BUILD=release

$(info >   Called    : $(realpath $(firstword $(MAKEFILE_LIST))))

# ------------
# library name
# ------------
ifndef lib_name
  # executed once, during 1st call to Makefile. export lib_name to make it available to 2nd call.
  lib_name := tinylib

# --- Do not change below this line --------------------------------------------

  export lib_name
  $(info ... TOT                 : $(TOT))
  $(info ... Common Makefiles dir: $(MAKEFILES_DIR))
endif

# ------------------------
# build type and directory
# ------------------------
# define build type (BUILD) and its directory (build_dir).
ifndef build_dir
  # executed once, during 1st call to Makefile
  include $(MAKEFILES_DIR)/build_type.mk
endif

# ----------------------------------------------
# switch to the build directory, and build there
# ----------------------------------------------
ifeq (,$(filter $(BUILD),$(notdir $(CURDIR))))
  # switch from the source to the build directory.
  # this part is executed during the 1st call to Makefile, which is from the source directory.
  $(info --- Switching to $(build_dir) directory ---)

  include $(MAKEFILES_DIR)/target.mk
else
  # build the target.
  # this part is executed during the 2nd call to Makefile, which is from the build directory.

  $(info --- Building a test for $(lib_name) library ---)

  # common facilities
  include $(MAKEFILES_DIR)/common.mk

  # defines the test (built as an executable file).
  # call_dir is where the program's source code is (defined in target.mk).
  include $(call_dir)/prog.mk

  # defines how an executable is built
  include $(MAKEFILES_DIR)/build_prog.mk
endif