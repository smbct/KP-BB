.PHONY: clean
CC = gcc
CFLAGS = -std=c99 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra

OBJECTS_FILES = src/Probleme.o src/BranchBound.o src/Solution.o src/Tri.o

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -c -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

solver: $(OBJECTS_FILES) src/main.c
	$(CC) $(CFLAGS) $(OBJECTS_FILES) src/main.c -lm -o solver

glpkSolver: $(OBJECTS_FILES) src/glpkSolver.c
	$(CC) $(CFLAGS) $(OBJECTS_FILES) src/glpkSolver.c -l glpk -o glpkSolver

generateur: $(OBJECTS_FILES) src/generateur.c
	$(CC) $(CFAGS) $(OBJECTS_FILES) src/generateur.c -o generateur

clean:
	@rm -rf src/*.o solver glpkSolver generateur
