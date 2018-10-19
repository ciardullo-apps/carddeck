# Here is the build target, which compiles the two c files and
# generates the deal executable file
build: cards.c usage.c poker.c
	gcc -o deal cards.c usage.c poker.c -I.
