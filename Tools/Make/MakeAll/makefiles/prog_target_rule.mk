##########################################
# Rules to build a program (an executable)
##########################################
$(print-last-makefile)

# Building a program requires linking the object files and libraries from which the program is made.
# The target is a program file name.
# - Link the program's object file.
# - Link all the other object files, $(objs), that the program relies on. $(objs) is a list - assembled via include calls to those objects' obj.mk files.
# - Link to additional pre-requisite libraries, $(pre_req_libs). These libraries are ones you wrote.
#   Place them last, after the objects, so that functions are found in object files first.
#
# Also link to $(non_pre_req_libs), found in $(non_pre_req_lib_dirs), that you didn't write or have control over, e.g. SystemC.
#
# $^: all prerequisites
# $@: target
# $<: first prerequisite
#
# c++filt: If there are errors, show C++ demangled function names.
# (https://sourceware.org/binutils/docs/binutils/c_002b_002bfilt.html)
#
# 2>&1: Redirect stderr (file descriptor 2), which carries error messages, to stdout (file descriptor 1). For the redirection to understand '1' as a file descriptor and not as a file name, '&' must be added.
# (https://stackoverflow.com/questions/818255/in-the-shell-what-does-21-mean)

%$(prog_ext) : %.o $(objs) $(pre_req_libs)
	       $(CC) $(LINKFLAGS) $(non_pre_req_lib_dirs) $(non_pre_req_libs) $^ -o $@ 2>&1 | c++filt

# load main object dependency file (.d)
dep_file := $(main_obj:.o=.d)
$(dep_file):
$(info ... Load prog. dep. file (if exists): $(dep_file))
-include $(dep_file)   # -include so that make won't complain if dependency file doesn't exist