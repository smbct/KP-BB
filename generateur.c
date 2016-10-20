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

        sprintf(nom, "instances/rnd%d.dat", nbVar);

        genererInstance(nbVar, randRange(50, 100), nom);

        nbVar += 10;
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
        pb.profit[i] = rand()%100;
        pb.poids[i] = randRange((double)pb.k*0.2, (double)pb.k*0.5);
    }

    enregistrerProbleme(&pb, nom);

    detruireProbleme(&pb);



}
