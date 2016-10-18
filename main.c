#include <stdio.h>
#include <stdlib.h>

#include "BranchBound.h"

int main(int argc, char* argv[]) {

    Probleme pb;

    chargerProbleme(&pb, "instance2.dat");

    afficherProbleme(&pb);

    Solution sol;
    creerSolution(&pb, &sol);

    BranchAndBound(&sol);

    afficherSolution(&sol);
    detruireSolution(&sol);

    detruireProbleme(&pb);

    return 0;
}
