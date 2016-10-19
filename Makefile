.PHONY: clean
CC = gcc
CFLAGS = -std=c99 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra

main.o: main.c
	$(CC) $(CFLAGS) main.c -c

Probleme.o: Probleme.h Probleme.c
	$(CC) $(CFLAGS) Probleme.c -c

BranchBound.o: BranchBound.h BranchBound.c
	$(CC) $(CFLAGS) BranchBound.c -c

Solution.o: Solution.h Solution.c
	$(CC) $(CFLAGS) Solution.c -c

Tri.o: Tri.h Tri.c
	$(CC) $(CFLAGS) Tri.c -c

main: main.o Probleme.o BranchBound.o Solution.o Tri.o
	$(CC) $(CFLAGS) main.o Probleme.o BranchBound.o Solution.o Tri.o -lm -o main

glpkSolver: Probleme.o Solution.o glpkSolver.c
	$(CC) $(CFLAGS) Probleme.o Solution.o glpkSolver.c -l glpk -o glpkSolver

clean:
	@rm -rf *.o main glpkSolver
