APP_DIR := $(ROOT_DIR)/app
APP_BUILD_DIR := $(BUILD_DIR)/$(APP_DIR)
$(shell mkdir -p $(APP_BUILD_DIR))

TARGETS += app
APP_SRC_FILES := main.c
APP_DEPENDENCIES := car

app : $(patsubst %.c,$(BUILD_DIR)/$(APP_DIR)/%.o,$(APP_SRC_FILES)) $(APP_DEPENDENCIES)
	$(CC) $(filter %.o,$^) -o $(APP_BUILD_DIR)/app $(patsubst %,-l%,$(APP_DEPENDENCIES)) -L$(CAR_BUILD_DIR)
