CAR_DIR := $(ROOT_DIR)/car
CAR_BUILD_DIR := $(BUILD_DIR)/$(CAR_DIR)
$(shell mkdir -p $(CAR_BUILD_DIR))

TARGETS += car
CAR_SRC_FILES := car.c car_impl.c

car : $(patsubst %.c,$(BUILD_DIR)/$(CAR_DIR)/%.o,$(CAR_SRC_FILES))
	$(AR) rcs $(CAR_BUILD_DIR)/libcar.a $^
