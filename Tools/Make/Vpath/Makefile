# Without adding folder "header" and "include" to vpath,
# make cannot find where "header1.h" or "header2.h" is,
# which results in make error.
vpath %.h header include

.PHONY: all h1 h2

all: h1 h2
	@echo "Building all..."

h1: header1.h
	@echo "Content of header1: "$(shell cat header/header1.h)

h2: header2.h
	@echo "Content of header2: "$(shell cat include/header2.h)
