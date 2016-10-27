#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BranchBound.h"

//------------------------------------------------------------------------------
int main(int argc, char** argv) {

    if(argc > 1) {

        Probleme pb;

        chargerProbleme(&pb, argv[1]);

        // afficherProbleme(&pb);
        // printf("\n");

        /*double *utilite = malloc(pb.nbVar*sizeof(double));
        calculerUtilites(&pb, utilite);

        printf("utilités : \n");
        for(int i = 0; i < pb.nbVar; i++) {
            printf("%f, ", utilite[i]);
        }
        printf("\n");

        free(utilite);*/

        Probleme ord;
        creerProblemeOrdonne(&pb, &ord);

        Solution sol;
        creerSolution(&pb, &sol);

        // thanks http://stackoverflow.com/questions/5248915/execution-time-of-c-program#5249150
        clock_t begin = clock();
        BranchAndBound(&sol);
        clock_t end = clock();

        double temps_ecoule = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("Solution optimale : \n");
        // afficherSolution(&sol);
        printf("z = %d\n", sol.z);
        printf("capacité résiduelle : %d\n\n", sol.residu);
        printf("temps écoulé : %fs\n", temps_ecoule);


        detruireSolution(&sol);

        detruireProbleme(&pb);

    } else {
        printf("Veuillez donner le nom d'une instance valide avec le programme.\n");
    }

    return 0;
}
