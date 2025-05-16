########################
# Define file extensions
########################
$(print-last-makefile)

# A non-empty file extension must include a beginning period!

# source files
src_ext  := .cpp

# header files
hdr_ext  := .hpp

# program/executable files
prog_ext := .exe

$(info ... File extensions: Source: $(src_ext); Header: $(hdr_ext); Program: $(prog_ext))
