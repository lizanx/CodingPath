include $(wildcard */Makefile)

.PHONY: all

# This var will influence sub-targets since they're included.
SHARED_VAR = A shared variable

all: sub_target_1 sub_target_2
	@echo "Building all from main Makefile!"
