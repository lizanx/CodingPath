########################################
# Compile source files into object files
########################################
$(print-last-makefile)

# a list of THIS object's files, that will be built
objs   := $(this_srcs:$(src_ext)=.o)

# a list of unique header file directories; searched during compilation (sort func removes duplicates)
INCDIR := $(addprefix -I, $(sort $(hdr_dirs)))

# ------------------------------------
# vpath - file-type search directories
# ------------------------------------
# when a file is not found in the current directory,
# based on the file's type, a specific list of directories will be searched for it.
#
# since only a single object is being built, source files are only searched in this_src_dir.
# but, this object might depend on header files from multiple locations - its own source dir, common headers and other objects.
# thus, header files are searched in hdr_dirs (which is a list of dirs).

vpath %$(src_ext) $(this_src_dir)
vpath %$(hdr_ext) $(sort $(hdr_dirs))
vpath %.o         $(build_dir)

$(info ... This object's source files:) $(foreach i, $(sort $(this_srcs)), $(info ...    $(i)))
$(info ... This object's source directory:)                                $(info ...    $(this_src_dir))
$(info ... Header directories:)         $(foreach i, $(sort $(hdr_dirs)) , $(info ...    $(i)))
$(info ... Built object files:)         $(foreach i, $(sort $(objs))     , $(info ...    $(i)))

# compile object files
.PHONY : make_objs
make_objs : $(objs)

# rule for building objects
include $(MAKEFILES_DIR)/obj_target_rule.mk
