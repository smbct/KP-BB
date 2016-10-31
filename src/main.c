#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <string.h>

#include "BranchBound.h"

//------------------------------------------------------------------------------
int main(int argc, char** argv) {

    if(argc > 2) {

        Probleme pb;

        // chargement du problème
        chargerProbleme(&pb, argv[1]);

        // afficherProbleme(&pb);

        // obtention d'un problème ordonné
        Probleme ord;
        creerProblemeOrdonne(&pb, &ord);

        Solution sol;
        creerSolution(&pb, &sol);

        double temps = 0;

        // thanks to http://stackoverflow.com/questions/5248915/execution-time-of-c-program#5249150
        clock_t begin, end;

        // exécution du branch and bound avec choix de la borne
        begin = clock();
        if(argv[2][0] == '1') {
            BranchAndBound(&sol, 1);
        } else if(argv[2][0] == '2') {
            BranchAndBound(&sol, 2);
        } else {
            BranchAndBound(&sol, 3);
        }
        end = clock();
        temps = (double)(end - begin) / CLOCKS_PER_SEC;
        temps *= 1000;

        // affichage de la solution optimale
        printf("Solution optimale : \n");

        afficherSolution(&sol);
        printf("z = %d\n", sol.z);
        printf("capacité résiduelle : %d\n\n", sol.residu);
        printf("temps écoulé : %fms\n", temps);

        detruireSolution(&sol);

        detruireProbleme(&pb);

    } else {
        printf("Veuillez donner le nom d'une instance valide avec le programme ainsi qu'un borne valide (1, 2 ou 3).\n");
    }

    return 0;
}
