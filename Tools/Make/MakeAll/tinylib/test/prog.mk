##################
# Define a program
##################
$(print-last-makefile)

description := Test $(lib_name) library
$(print-description)

# ----------------------
# include your libraries
# ----------------------
# if the program files include the header files of your libraries,
# those libraries' lib.mk files must be included here.
#
# e.g. if this program depends on library mylib, do:
# $(eval $(call include-once, $(TOT)/mylib/include/lib.mk))

# this program depends on 1 library
$(eval $(call include-once, $(TOT)/$(lib_name)/include/lib.mk))

# ---------------------------
# dependency on other objects
# ---------------------------
# if the program depends on other objects, besides those in the libraries above,
# i.e. its code includes their header files,
# those objects' obj.mk files must be included here,
# ahead of main_src, this_src_dir and this_extra_hdr_dirs,
# so that those objects' source and header directories will be added to the
# src_dirs and hdr_dirs lists.
#
# e.g. if this object depends on object xyz, do:
# $(eval $(call include-once, $(lib_src_dir)/xyz/obj.mk))

# this program does not depend on other objects

# ------------
# this program
# ------------
# the source file, that includes a main() function
main_src := test.cpp

# source files directory (full path)
this_src_dir := $(TOT)/tinylib/test

# a list of additional header file directories (full path), that this program depends on,
# but that do not correspond to objects (i.e. they are pure header files),
# and are not already included by common.mk file.
this_extra_hdr_dirs :=

# --- Do not change below this line --------------------------------------------

# ------------
# add to lists
# ------------
# all source file directories:
# used by vpath to find source files.
src_dirs  += $(this_src_dir)

# all header file directories:
# converted into INCDIR to find header files.
hdr_dirs  += $(this_extra_hdr_dirs)