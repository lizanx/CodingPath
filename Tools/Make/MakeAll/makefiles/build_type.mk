#######################################
# Define build type and build directory
#######################################
# 3 build types are supported:
# debug (default), release and profile.
# each build type has its own directory, under a common build directory.
# the common build directory is under the source directory.
# e.g. a component xyz will be built in one of the 3 directories:
# xyz/build/debug
# xyz/build/release
# xyz/build/profile

$(info +   Included  : $(realpath $(lastword $(MAKEFILE_LIST))))

# Expect an override from the command line, thus check value before assigning a default value.
# ?= : if not already defined
BUILD ?= debug
$(info ... Build type: $(BUILD))

ifneq ($(BUILD), debug)
  ifneq ($(BUILD), release)
    ifneq ($(BUILD), profile)
      $(error $(BUILD) is an invalid value to the BUILD option; legal values are: debug, release or profile)
    endif
  endif
endif

build_dir := build/$(BUILD)
$(info ... build_dir : $(build_dir))

# --------------------------------------------------------
# make variables available to 2nd call to gmake (sub-make)
# --------------------------------------------------------
export BUILD
export build_dir
