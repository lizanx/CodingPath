##############################################
# Compile source files into an executable file
##############################################
$(print-last-makefile)

# prevent gmake from deleting object files after build is done (saves on recompilation)
.PRECIOUS: %.o

# object file name, that is built from the main source file
main_obj := $(main_src:$(src_ext)=.o)

# program name, based on the main source file name
prog     := $(main_src:$(src_ext)=$(prog_ext))

# object file list (doen't include the main source file)
objs     := $(srcs:$(src_ext)=.o)

# header files directories list (sort removes duplicates)
INCDIR   := $(addprefix -I, $(sort $(hdr_dirs)))

# ------------------------------------
# vpath - file-type search directories
# ------------------------------------
# when a file is not found in the current directory,
# based on the file's type, a specific list of directories will be searched for it.

vpath %$(src_ext) $(sort $(src_dirs))
vpath %$(hdr_ext) $(sort $(hdr_dirs))
vpath %.o         $(build_dir)
vpath %.a         $(pre_req_libs_dirs)

$(info ... Program file: $(prog))
$(info ... Source files: $(main_src) (main) ) $(foreach i, $(sort $(srcs))     	       , $(info ...    $(i)))
$(info ... Object files: $(main_obj) (main) ) $(foreach i, $(sort $(objs))     	       , $(info ...    $(i)))
$(info ... Library files:)            	      $(foreach i, $(sort $(pre_req_libs))     , $(info ...    $(i)))
$(info ... Source directories:)       	      $(foreach i, $(sort $(src_dirs)) 	       , $(info ...    $(i)))
$(info ... Header directories:)       	      $(foreach i, $(sort $(hdr_dirs)) 	       , $(info ...    $(i)))
$(info ... Pre requisite libs directories:)   $(foreach i, $(sort $(pre_req_libs_dirs)), $(info ...    $(i)))

# compile program
.PHONY : make_prog
make_prog : $(prog)

# rules for building objects and a program
include $(MAKEFILES_DIR)/obj_target_rule.mk
include $(MAKEFILES_DIR)/prog_target_rule.mk
