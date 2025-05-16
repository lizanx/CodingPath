##################
# Define a program
##################
$(print-last-makefile)

description := Test project component y
$(print-description)

# ---------------------------
# dependency on other objects
# ---------------------------
# if this object depends on other objects,
# i.e. its code includes their header files,
# those objects' obj.mk files must be included here,
# ahead of main_src, this_src_dir and this_extra_hdr_dirs,
# so that those objects' source and header directories will be added to the
# src_dirs and hdr_dirs lists.
#
# e.g. if this object depends on object xyz, do:
# $(eval $(call include-once, $(lib_src_dir)/xyz/obj.mk))

# this program depends on 1 object: y
$(eval $(call include-once, $(proj_src_dir)/y/obj.mk))

# ------------
# this program
# ------------
# the source file, that includes a main() function
main_src := test.cpp

# source files directory (full path)
this_src_dir := $(proj_src_dir)/y/test

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