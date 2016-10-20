/**
 * \file Probleme.c
 * \brief implémentation des fonctions pour manipuler le problème
 */

#include <stdio.h>
#include <stdlib.h>

#include "Probleme.h"
#include "Tri.h"

//------------------------------------------------------------------------------
void chargerProbleme(Probleme* ord, char* nom) {

    Probleme pb;

    FILE* fichier = fopen(nom,  "r");

    if(fichier) {

        fscanf(fichier, "%d", &pb.nbVar);

        // allocation mémoire
        pb.profit = malloc((long unsigned int)pb.nbVar*sizeof(int));
        pb.poids = malloc((long unsigned int)pb.nbVar*sizeof(int));

        // lecture des profits
        for(int i = 0; i < pb.nbVar; i++) {
            fscanf(fichier, "%d", &pb.profit[i]);
        }

        // capacité
        fscanf(fichier, "%d", &pb.k);

        //lecture des poids
        for(int i = 0; i < pb.nbVar; i++) {
            fscanf(fichier, "%d", &pb.poids[i]);
        }
    }

    // création du problème ordonné, utilisable par le solveur
    creerProblemeOrdonne(&pb, ord);
    detruireProbleme(&pb);

    fclose(fichier);

}

//------------------------------------------------------------------------------
void enregistrerProbleme(Probleme* pb, char* nom) {

    FILE* fichier = fopen(nom, "w");

    // nombre de variable
    fprintf(fichier, "%d\n", pb->nbVar);

    // profits
    for(int i = 0; i < pb->nbVar; i++) {
        fprintf(fichier, "%d", pb->profit[i]);
        if(i < pb->nbVar-1) {
            fprintf(fichier, " ");
        }
    }

    // capacité
    fprintf(fichier, "\n%d\n", pb->k);

    // poids
    for(int i = 0; i < pb->nbVar; i++) {
        fprintf(fichier, "%d", pb->poids[i]);
        if(i < pb->nbVar-1) {
            fprintf(fichier, " ");
        }
    }
    fprintf(fichier, "\n");

    fclose(fichier);

}

//------------------------------------------------------------------------------
void creerProblemeVide(Probleme* pb, int nbVar) {
    pb->nbVar = nbVar;
    pb->profit = malloc((long unsigned int)pb->nbVar*sizeof(int));
    pb->poids = malloc((long unsigned int)pb->nbVar*sizeof(int));
}

//------------------------------------------------------------------------------
void creerProblemeOrdonne(Probleme* pb, Probleme* ord) {

    // calcule des utilités des variables
    double* utilite = malloc((long unsigned int)pb->nbVar*sizeof(double));

    calculerUtilites(pb, utilite);

    // création d'une permution de variable
    int* perm = malloc((long unsigned int)pb->nbVar*sizeof(int));
    for(int i = 0; i < pb->nbVar; i++) {
        perm[i] = i;
    }

    // réordonne les variables selon les utilités
    trierDecroissant(pb->nbVar, perm, utilite);

    // initialisation du nouveau problème ordonné
    ord->nbVar = pb->nbVar;
    ord->k = pb->k;
    ord->profit = malloc((long unsigned int)ord->nbVar*sizeof(int));
    ord->poids = malloc((long unsigned int)ord->nbVar*sizeof(int));

    for(int i = 0; i < pb->nbVar; i++) {
        ord->profit[i] = pb->profit[perm[i]];
        ord->poids[i] = pb->poids[i];
    }

    free(utilite);
    free(perm);
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
void calculerUtilites(Probleme* pb, double* utilite) {

    for(int i = 0; i < pb->nbVar; i++) {
        utilite[i] = (double)pb->profit[i]/(double)pb->poids[i];
    }

}

//------------------------------------------------------------------------------
void detruireProbleme(Probleme* pb) {

    free(pb->profit);
    free(pb->poids);

}
