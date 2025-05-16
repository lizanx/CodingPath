###########################
# Build a library component
###########################
# This is the top-level gmake Makefile to build a library component.
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
# define build type (BUILD) and its directory (build_dir)
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
  $(info --- Building a $(lib_name) library component ---)

  # common facilities
  include $(MAKEFILES_DIR)/common.mk
  include $(TOT)/$(lib_name)/common.mk

  # defines the component (built as one or more object files).
  # call_dir is where the component's source code is (defined in target.mk).
  include $(call_dir)/obj.mk

  # defines how object files are built
  include $(MAKEFILES_DIR)/build_obj.mk
endif