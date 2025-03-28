SUB_DIRS = sub1 sub2

.PHONY: all $(SUB_DIRS)

# This var won't influence sub-targets since it's not exported.
NON_EXPORTED_SHARED_VAR = Non-exported shared variable
# This var will influence sub-dir Makefiles since it's exported.
export EXPORTED_SHARED_VAR = Exported shared variable

all: $(SUB_DIRS)
	@echo "Building all from main Makefile!"

$(SUB_DIRS):
	$(MAKE) -C $@ all
