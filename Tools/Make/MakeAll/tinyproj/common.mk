#########################
# Project common Makefile
#########################
# Define additional common variables, used for compiling components of a project, and building that project.
#
# 1. This file should reside in the project's base directory.
# 2. This file should be included after common.mk in a top-level Makefile, during the 2nd call (i.e. after switching to the build directory).
# 3. Directory tree assumptions:
#    - All code resides under a common base directory, $(TOT), e.g. prog.
#    - All supporting Makefiles reside under a common base directory, $(MAKEFILES_DIR), e.g. prog/makefiles.
#    - All project code - itself and all of its components - reside under a common base directory, e.g. $(TOT)/tinyproj.
#    - This Makefile should be in the base directory of the project, e.g. $(TOT)/tinyproj/common.mk.
#    - All project COMPONENTS reside under a common base directory, e.g. $(TOT)/tinyproj/src.
#    - Each project component resides in its own directory, under the project's base source directory,
#      e.g. component xyz is in $(TOT)/tinyproj/src/xyz
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
# project base directory
proj_base_dir := $(TOT)/$(proj_name)

# project common header files directory (those not associated with project components)
proj_hdr_dir  := $(proj_base_dir)/src

# project source files directory:
# project components reside under this directory.
# e.g. component xyz resides in $(proj_src_dir)/xyz.
# each component is compiled into an object file.
proj_src_dir  := $(proj_base_dir)/src

$(info ... Project base dir      : $(proj_base_dir))
$(info ... Project header dir    : $(proj_hdr_dir))
$(info ... Project components dir: $(proj_src_dir))

# header file directories
hdr_dirs      := $(proj_hdr_dir)

# ----------------------
# include your libraries
# ----------------------
# if the program files include the header files of your libraries,
# those libraries lib.mk files must be included here.
# e.g. if this program depends on a library in mylib_dir, do:
# $(eval $(call include-once, $(mylib_dir)/header/lib.mk))
#
# this program depends on tinylib library.
$(eval $(call include-once, $(TOT)/tinylib/include/lib.mk))
