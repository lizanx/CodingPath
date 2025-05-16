#########################
# Library common Makefile
#########################
# Define additional common variables, used for compiling components of a library, and building that library.
#
# 1. This file should reside in the library's base directory.
# 2. This file should be included after common.mk in a top-level Makefile, during the 2nd call (i.e. after switching to the build directory).
# 3. Directory tree assumptions:
#    - All code resides under a common base directory, $(TOT), e.g. prog.
#    - All supporting Makefiles reside under a common base directory, $(MAKEFILES_DIR), e.g. prog/makefiles.
#    - All library code - itself and all of its components - reside under a common base directory, e.g. $(TOT)/tinylib.
#    - This Makefile should be in the base directory of the library, e.g. $(TOT)/tinylib/common.mk.
#    - All library COMPONENTS reside under a common base directory, e.g. $(TOT)/tinylib/src.
#    - Each library component resides in its own directory, under the library's base source directory,
#      e.g. component xyz is in $(TOT)/tinylib/src/xyz
#
# -------------------------------------------
# Variable name conventions for all makefiles
# -------------------------------------------
# Function names are hyphenated-lower-case.
# Variables which the user is expected to change via the command line are ALL_CAPS_WITH_UNDERSCORES.
# Variables internal to the makefiles are lower_case_with_underscores.

$(print-last-makefile)

# -----------
# directories
# -----------
# library base directory
lib_base_dir := $(TOT)/$(lib_name)

# library common header files directory (those files not associated with library components, e.g. always.hpp)
lib_hdr_dir  := $(lib_base_dir)/src

# library source files directory:
# library components reside UNDER this directory.
# e.g. component xyz resides in $(lib_src_dir)/xyz.
# each component is compiled into an object file.
lib_src_dir  := $(lib_base_dir)/src

$(info ... Library base dir      : $(lib_base_dir))
$(info ... Library header dir    : $(lib_hdr_dir))
$(info ... Library components dir: $(lib_src_dir))

# header file directories (common headers to all components are in lib_hdr_dir)
hdr_dirs     :=  $(lib_hdr_dir)
