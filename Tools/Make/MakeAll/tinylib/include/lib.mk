#####################################
# Define a library as a pre-requisite
#####################################
$(print-last-makefile)

lib_name := tinylib

# library include directory:
# this directory is included by USERS of the library.
# the directory contains:
# - the library's top-level header file
# - lib.mk which defines the library
# - a COPY of the library file per build type
# - a COPY of all the library's object header files reside.
#   a program, by using those copied libraries and their object headers,
#   will not be affected/rebuilt when someone's working on the library, but hasn't released it to the users.
lib_inc_dir   := $(TOT)/$(lib_name)/include

# list of library components header file directories, within $(lib_inc_dir).
# if library components depend on each other, these directories are used to find the header files, that the components include, since they lack relative path.
lib_inc_comp_hdr_dirs  := $(lib_inc_dir)/a $(lib_inc_dir)/b

# --- Do not change below this line --------------------------------------------

lib_file_name := $(lib_name).a

# all header file directories:
# converted into INCDIR to find header files.
hdr_dirs      += $(lib_inc_dir) $(lib_inc_comp_hdr_dirs)

# library file lists:
pre_req_libs      += $(lib_file_name)
pre_req_libs_dirs += $(lib_inc_dir)/$(build_dir)

$(info ... $(lib_name) include dir : $(lib_inc_dir))
$(info ... $(lib_name) library file: $(lib_inc_dir)/$(build_dir)/$(lib_file_name))
