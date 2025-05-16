#############################################################################
# Compile source files into object files, and package them as a library file.
#############################################################################
$(print-last-makefile)

# a list of object files, that will be built
objs   := $(srcs:$(src_ext)=.o)

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

vpath %$(src_ext) $(sort $(src_dirs))
vpath %$(hdr_ext) $(sort $(hdr_dirs))
vpath %.o         $(build_dir)
vpath %.a         $(pre-requisite-dir-libs)

$(info ... Objects source files:)       $(foreach i, $(sort $(srcs))    , $(info ...    $(i)))
$(info ... Objects source directories:) $(foreach i, $(sort $(src_dirs)), $(info ...    $(i)))
$(info ... Header directories:)         $(foreach i, $(sort $(hdr_dirs)), $(info ...    $(i)))
$(info ... Built object files:)         $(foreach i, $(sort $(objs))    , $(info ...    $(i)))

# build a library file
.PHONY : make_lib
make_lib : $(lib_name).a

# rule for building a library
include $(MAKEFILES_DIR)/lib_target_rule.mk
