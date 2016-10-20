/**
 * \file generateur.c
 * \brief implémentation d'un générateur aléatoire d'instances pour le 01KP unidimensionnel
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Probleme.h"

int main(int argc, char** argv) {

    srand(time(NULL));

    Probleme pb;

    creerProblemeVide(&pb, 10);
    pb.k = 150;


    for(int i = 0; i < pb.nbVar; i++) {
        pb.profit[i] = rand()%50;
        pb.poids[i] = rand()%(int)((double)pb.k*0.3);
    }

    enregistrerProbleme(&pb, "test.dat");

    detruireProbleme(&pb);

    return 0;

}
