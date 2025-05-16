##################
# Define a library
##################
$(print-last-makefile)

description := Library has 2 components: a and b
$(print-description)

# ---------------
# include objects
# ---------------
# Include the obj.mk Makefiles of this library's objects.
# e.g. if this library should contain object xyz, do:
# $(eval $(call include-once, $(lib_src_dir)/xyz/obj.mk))

# this library has 2 objects: a and b
$(eval $(call include-once, $(lib_src_dir)/a/obj.mk))
$(eval $(call include-once, $(lib_src_dir)/b/obj.mk))
