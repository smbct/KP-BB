#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <string.h>

#include "BranchBound.h"

//------------------------------------------------------------------------------
int main(int argc, char** argv) {

    if(argc > 1) {

        Probleme pb;

        char* pos = strrchr(argv[1], '/');
        if(pos == NULL) {
            pos = argv[1];
        }
        char* nom = pos+1;

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

        double tempsB1 = 0, tempsB2 = 0, tempsB3 = 0;

        // thanks to http://stackoverflow.com/questions/5248915/execution-time-of-c-program#5249150
        clock_t begin, end;

        begin = clock();
        BranchAndBound(&sol, 1);
        end = clock();
        tempsB1 = (double)(end - begin) / CLOCKS_PER_SEC;

        begin = clock();
        BranchAndBound(&sol, 2);
        end = clock();
        tempsB2 = (double)(end - begin) / CLOCKS_PER_SEC;

        begin = clock();
        BranchAndBound(&sol, 3);
        end = clock();
        tempsB3 = (double)(end - begin) / CLOCKS_PER_SEC;

        // printf("Solution optimale : \n");

        // afficherSolution(&sol);
        // printf("z = %d\n", sol.z);
        // printf("capacité résiduelle : %d\n\n", sol.residu);
        // printf("temps écoulé : %fs\n", temps_ecoule);

        tempsB1 *= 1000.;
        tempsB2 *= 1000.;
        tempsB3 *= 1000.;

        printf(nom);
        printf(" & %f & %f & %f\n", tempsB1, tempsB2, tempsB3);

        detruireSolution(&sol);

        detruireProbleme(&pb);

    } else {
        printf("Veuillez donner le nom d'une instance valide avec le programme.\n");
    }

    return 0;
}
