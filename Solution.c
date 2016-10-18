/**
 * \file Solution.c
 * \brief implémentation des fonctions pour manipuler la solution
 */

#include "Solution.h"
#include <stdlib.h>
#include <stdio.h>

//------------------------------------------------------------------------------
void creerSolution(Probleme* pb, Solution* sol) {

    sol->pb = pb;

    sol->valeur = malloc((long unsigned int)pb->nbVar*sizeof(int));
    for(int i = 0; i < pb->nbVar; i++) {
        sol->valeur[i] = 0;
    }
    sol->residu = pb->k;
    sol->z = 0;

}

//------------------------------------------------------------------------------
void detruireSolution(Solution* sol) {

    free(sol->valeur);

}

//------------------------------------------------------------------------------
void afficherSolution(Solution* sol) {

    printf("(");
    for(int i = 0; i < sol->pb->nbVar; i++) {
        printf("%d", sol->valeur[i]);
        if(i < sol->pb->nbVar-1) {
            printf(", ");
        }
    }
    printf(")\n");

}


//------------------------------------------------------------------------------
void copierSolution(Solution* sol, Solution* copie) {

    copie->residu = sol->residu;
    copie->pb = sol->pb;
    copie->z = sol->z;
    for(int i = 0; i < sol->pb->nbVar; i++) {
        copie->valeur[i] = sol->valeur[i];
    }

}
