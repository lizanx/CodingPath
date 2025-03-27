prog: main.o
	$(CC) main.o -o prog

main.o: main.c
	$(CC) -c -o main.o main.c

main.c:
	@echo "int main() {return 0;}" > main.c

.PHONY: clean

clean:
	$(RM) prog *.o

# If there's file named "hello", then no commands will get executed.
hello:
	@echo "Hello World"
