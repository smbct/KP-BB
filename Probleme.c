/**
 * \file Probleme.c
 * \brief implémentation des fonctions pour manipuler le problème
 */

#include <stdio.h>
#include <stdlib.h>
#include "Probleme.h"

//------------------------------------------------------------------------------
void chargerProbleme(Probleme* pb, char* nom) {

    FILE* fichier = fopen(nom,  "r");

    if(fichier) {

        fscanf(fichier, "%d", &pb->nbVar);

        // allocation mémoire
        pb->profit = malloc((long unsigned int)pb->nbVar*sizeof(int));
        pb->poids = malloc((long unsigned int)pb->nbVar*sizeof(int));

        // lecture des profits
        for(int i = 0; i < pb->nbVar; i++) {
            fscanf(fichier, "%d", &pb->profit[i]);
        }

        // capacité
        fscanf(fichier, "%d", &pb->k);

        //lecture des poids
        for(int i = 0; i < pb->nbVar; i++) {
            fscanf(fichier, "%d", &pb->poids[i]);
        }
    }


}

//------------------------------------------------------------------------------
void afficherProbleme(Probleme* pb) {

    printf("max z = ");
    for(int i = 0; i < pb->nbVar; i++) {
        printf("%d", pb->profit[i]);
        if(i != pb->nbVar-1) {
            printf(" ");
        } else {
            printf("\n\n");
        }
    }

    printf("s/c ");
    for(int i = 0; i < pb->nbVar; i++) {
        printf("%d ", pb->poids[i]);
    }
    printf(" <= %d\n", pb->k);

}

//------------------------------------------------------------------------------
void detruireProbleme(Probleme* pb) {

    free(pb->profit);
    free(pb->poids);

}
