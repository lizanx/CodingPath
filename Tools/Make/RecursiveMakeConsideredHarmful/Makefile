.PHONY: all clean

# SRC_FILES =
TARGETS =
# OBJECTS =
ROOT_DIR = .
BUILD_DIR = ./build
MODULES = $(ROOT_DIR)/car $(ROOT_DIR)/app
SUB_DIR_MAKEFILES = $(patsubst %,%/Build.mk,$(MODULES))
$(info "sub dir makefiles: $(SUB_DIR_MAKEFILES)")

CFLAGS += -Iinclude

# Make sure that build dir exists
$(shell mkdir -p $(BUILD_DIR))

include $(SUB_DIR_MAKEFILES)
-include $(BUILD_DIR)/**/*.d

all : $(TARGETS)

clean :
	$(RM) ./*.o ./*.d ./**/*.o ./**/*.d
	$(RM) -r $(BUILD_DIR)

$(BUILD_DIR)/%.o : %.c %.d
	-$(shell mkdir -p $(BUILD_DIR)/$(dir $<))
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# $(BUILD_DIR)/%.o : %.d
# 	include($(BUILD_DIR)/$<)

%.d : %.c
	$(CC) -MM -MP $< -MF $(BUILD_DIR)/$@ $(CFLAGS)

.INTERMEDIATE : %.o %.d
