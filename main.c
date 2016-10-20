#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BranchBound.h"

//------------------------------------------------------------------------------
int main(int argc, char** argv) {

    if(argc > 1) {

        Probleme pb;

        chargerProbleme(&pb, argv[1]);

        afficherProbleme(&pb);
        printf("\n");

        Probleme ord;
        creerProblemeOrdonne(&pb, &ord);

        Solution sol;
        creerSolution(&pb, &sol);

        BranchAndBound(&sol);

        printf("Solution optimale : \n");
        afficherSolution(&sol);
        printf("z = %d\n", sol.z);
        printf("capacité résiduelle : %d\n\n\n", sol.residu);

        detruireSolution(&sol);

        detruireProbleme(&pb);

    } else {
        printf("Veuillez donner le nom d'une instance valide avec le programme.\n");
    }

    return 0;
}
