##################
# Define an object
##################
$(print-last-makefile)

description := Project component y
$(print-description)

# ---------------------------
# dependency on other objects
# ---------------------------
# if this object depends on other objects,
# i.e. its code includes their header files,
# those objects' obj.mk files must be included here,
# ahead of this_srcs/this_src_dir,
# so that those objects' source files, and source and header directories will be added to the
# srcs, src_dirs and hdr_dirs lists.
#
# e.g. if this object depends on object xyz, do:
# $(eval $(call include-once, $(lib_src_dir)/xyz/obj.mk))

# this object does not depend on other objects

# -----------
# this object
# -----------
# a list of this object's source files
this_srcs    := y.cpp

# this object's source files directory (full path)
this_src_dir := $(proj_src_dir)/y

# a list of additional header file directories (full path), that this object depends on,
# but that do not correspond to objects (i.e. they are pure header files),
# and are not already included by common.mk file.
this_extra_hdr_dirs :=

# --- Do not change below this line --------------------------------------------

# ------------
# add to lists
# ------------
# all source files:
# used when building an executable,
# that uses this and other objects, so that each object can be built.
srcs      += $(this_srcs)

# all source file directories:
# used by vpath to find source files.
src_dirs  += $(this_src_dir)

# all header file directories:
# converted into INCDIR to find header files.
hdr_dirs  += $(this_src_dir) $(this_extra_hdr_dirs)
