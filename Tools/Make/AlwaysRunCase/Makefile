some_file: other_file
	@echo "This will always run ,and runs second."
	touch some_file

other_file:
	@echo "This will always run, and runs first."

.PHONY: clean

clean:
	$(RM) some_file
