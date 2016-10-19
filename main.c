#include <stdio.h>
#include <stdlib.h>

#include "BranchBound.h"

//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {

    Probleme pb;

    chargerProbleme(&pb, "instance2.dat");

    printf("Problème à résoudre : \n\n");
    afficherProbleme(&pb);
    printf("\n");

    Solution sol;
    creerSolution(&pb, &sol);

    BranchAndBound(&sol);

    printf("Solution optimale : \n");
    afficherSolution(&sol);
    printf("z = %d\n", sol.z);
    printf("capacité résiduelle : %d\n", sol.residu);

    detruireSolution(&sol);

    detruireProbleme(&pb);

    return 0;
}
