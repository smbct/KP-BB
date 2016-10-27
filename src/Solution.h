/**
 * \file Solution.h
 * \brief def d'une structure pour représenter une solution et de fonctions pour la manipuler
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "Probleme.h"

typedef struct {
    int* valeur; // valeurs des variables
    int residu; // capacité résiduelle
    int z; // valeur de la fonction objectif
    Probleme* pb; // instance du problème
} Solution;

/**
 * \brief création d'une solution
 * \param pb l'instance du problème
 * \param sol la solution créée
 */
void creerSolution(Probleme* pb, Solution* sol);

/**
 * \brief désallocation mémoire d'une solution
 * \param sol la solution à désallouer
 */
void detruireSolution(Solution* sol);

/**
 * \brief affichage d'une solution
 * \param sol la solution à afficher
 */
void afficherSolution(Solution* sol);

/**
 * \brief copie d'une solution dans une autre
 * \param sol la solution à copier
 * \param copie la copie de la solution
 */
void copierSolution(Solution* sol, Solution* copie);

#endif // SOLUTION_H
