################################################################
# Define the rule that packages object files into a library file
################################################################
$(print-last-makefile)

# package objects into a library file.
#
# r only update newer objects
# v verbose output
#
# $@: target
# $? pre-requisites that are newer than the target
# 
# use
# nm -C lib_name
# to see the library's object content with unmangled function names.

$(lib_name).a : $(objs)
	ar rv $@ $?

# rule for building objects
include $(MAKEFILES_DIR)/obj_target_rule.mk
