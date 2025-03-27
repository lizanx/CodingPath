CFLAGS += -I include

SRC_FILES := main.c point.c
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))

prog: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o prog

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean show

show:
	@echo "Src files: " $(SRC_FILES)
	@echo "Object files: " $(OBJ_FILES)

clean:
	$(RM) *.o prog
