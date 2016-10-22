/**
 * \file BranchBound.h
 * \brief définition des fonctions de résolution de 01KP
 */

#ifndef BRANCH_BOUND_H
#define BRANCH_BOUND_H

#include "Solution.h"

/**
 * \brief résolution du problème de kp
 * \param opt la solution optimale du problème
 */
void BranchAndBound(Solution* opt);

/**
 * \brief calcule la relaxation continue du problème
 * \param sol les variables affectées et non affectées
 * \param ind l'indice de la première variable du sous-problème
 * \param borne la borne choisie pour la relaxation
 * \param sup la valeur de la relaxation
 * \param realisable vrai ssi la relaxation donne une solution réalisable
 */
void relaxation(Solution *sol, int* ind, int borne, int* sup, int* realisable);


/**
 * \brief effectue une plus profonde descente pour tenter de résoudre le problème
 * \param sol la solution en cours de construction
 * \param ind l'indice de la première variable non affectée
 */
void descente(Solution *sol, int* ind);

/**
 * \brief retour vers la dernière variable affectée à 1
 * \param sol la solution en cours de construction
 * \param ind l'indice de la dernière variable affectée à 1
 */
void backtracking(Solution *sol, int* ind);

#endif // BRANCH_BOUND_H
