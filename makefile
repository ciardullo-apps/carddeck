# makefile for deal

# Compiler
CC = gcc

# C files
FILES = cards.c usage.c poker.c

# Executable file
OUT = deal

# Here is the build target, which compiles the two c files and
# generates the deal executable file
compileAndLink: $(FILES)
	$(CC) -o $(OUT) $(FILES) -I.

# Remove object files
clean:
	rm -f *.o core

build: clean compileAndLink
