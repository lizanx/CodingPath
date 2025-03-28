.PHONY: all, clean

all: main.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o prog

main.o::
	@echo "Extra rule 1 for main.o!"

main.o:: main.c
	@echo "Compiling main.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^

main.o::
	@echo "Extra rule 2 for main.o!"

main.c:
	@echo "int main() { return 0; }" > main.c

clean:
	$(RM) $(wildcard *.o) prog
