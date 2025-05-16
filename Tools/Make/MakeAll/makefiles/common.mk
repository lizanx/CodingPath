#################
# Common Makefile
#################
# Define common variables, and include common Makefile facilities, to be used by all top-level Makefiles.
#
# This file should be the first included makefile in a top-level Makefile, during the 2nd call (i.e. after switching to the build directory).
#
# -------------------------------------------
# Variable name conventions for all makefiles
# -------------------------------------------
# Function names are hyphenated-lower-case.
# Variables which the user is expected to change via the command line are ALL_CAPS_WITH_UNDERSCORES.
# Variables internal to Makefiles are lower_case_with_underscores.

$(info +   Included  : $(realpath $(lastword  $(MAKEFILE_LIST))))

# -----
# lists
# -----
# included objects add to these lists their associated source files, and source and header file directories.
# the following variables MUST be initialized with immediate assignments, :=, to correctly collect items into them later on.

# source files, that compile into object files
srcs :=

# source file directories
src_dirs :=

# header file directories
hdr_dirs :=

# pre-requisite libraries
# a target will be rebuilt, if these libraries are newer than the target.
# usually these are my libraries.
# $(pre_req_libs) is where those libraries can be found.
pre_req_libs      :=
pre_req_libs_dirs :=

# non-pre-requisite libraries
# a target merely depends on these libraries, and it will NOT be rebuilt, if these libraries are newer than the target.
# use with publically available libraries (e.g. SystemC).
# $(non_pre_req_libs) is where those libraries can be found.
non_pre_req_libs      :=
non_pre_req_libs_dirs :=

# --------------------------
# common Makefile facilities
# --------------------------
# common macros and functions
include $(MAKEFILES_DIR)/macros_and_functions.mk

# compilation options
include $(MAKEFILES_DIR)/compile_options.mk

# file extensions
include $(MAKEFILES_DIR)/file_extensions.mk
