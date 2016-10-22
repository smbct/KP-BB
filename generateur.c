/**
 * \file generateur.c
 * \brief implémentation d'un générateur aléatoire d'instances pour le 01KP unidimensionnel
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Probleme.h"

/**
 * \brief génération d'une instance aléatoire
 * \param nbVar le nombre de variable
 * \nom le nom du fichier de l'instance
 */
void genererInstance(int nbVar, int k, char* nom);

/**
 * \brief génération d'un nombre aléatoire entre deux bornes
 * \param min la valeur minimale
 * \param max la valeur maximale
 */
int randRange(int min, int max);

//------------------------------------------------------------------------------
int main(int argc, char** argv) {

    srand(time(NULL));

    char nom[50];

    int nbVar = 10;
    for(int i = 0; i < 20; i++) {

        sprintf(nom, "instances/wcorr%d.dat", nbVar);

        genererInstance(nbVar, randRange(10000, 500000), nom);

        nbVar += 1000;
    }


    return 0;

}

//------------------------------------------------------------------------------
int randRange(int min, int max) {
    return min + rand()%(max-min+1);
}

//------------------------------------------------------------------------------
void genererInstance(int nbVar, int k, char* nom) {

    Probleme pb;

    creerProblemeVide(&pb, nbVar);
    pb.k = k;


    for(int i = 0; i < pb.nbVar; i++) {
        if(i == 0) {
            pb.profit[i] = rand()%100;
            // pb.poids[i] = randRange((double)pb.k*0.00005, (double)pb.k*0.0001);
            pb.poids[i] = ((double)pb.k/(double)nbVar)*(double)randRange(200, 310)*0.01;
            // printf("%d\n", pb.poids[i]);
        } else { // correllation entre les instances
            double utilite = (double)pb.profit[0]/(double)pb.poids[0];
            pb.poids[i] = ((double)pb.k/(double)nbVar)*(double)randRange(200, 310)*0.01;
            pb.profit[i] = (int) (/*((double)randRange(999, 1000)*0.001) **/ utilite * (double)pb.poids[i]);
        }
    }

    enregistrerProbleme(&pb, nom);

    detruireProbleme(&pb);



}
