/**
 * \file BranchBound.c
 * \brief implémentation des fonctions de résolution de 01KP
 */

#include "BranchBound.h"
#include <stdio.h>
#include <math.h>

//------------------------------------------------------------------------------
void BranchAndBound(Solution* opt) {

    Solution sol;
    creerSolution(opt->pb, &sol);

    int inf = 0, sup = -1;
    int ind = 0; // indice de la première variable du sous problème étudié

    int relax;
    int realisable;

    int continuer = 1;
    while(continuer) {

        // une feuille de l'arbre a été atteinte
        if(ind == sol.pb->nbVar) {

            if(sol.z > inf) { // amélioration de la solution actuelle
                inf = sol.z;
                copierSolution(&sol, opt);
            }

            if(sol.z == sup) {
                continuer = 0;
            } else {
                backtracking(&sol, &ind);
            }


        } else {

            // relaxation continue du problème
            relaxation(&sol, &ind, &relax, &realisable);

            // la borne supérieure est initialisée
            if(sup == -1) {
                sup = relax;
            }

            if(realisable) { // la relaxation est une solution réalisable, chance !

                // meilleure solution trouvée, mise à jour
                if(relax > inf) {
                    inf = relax; // une meilleure solution a été trouvée
                    copierSolution(&sol, opt);
                }

                if(ind == 0 || relax == sup) {
                    continuer = 0;
                } else {
                    backtracking(&sol, &ind);
                }


            } else { // la relaxation ne donne pas de solution réalisable

                // l'exploration est obligatoire
                if(relax > inf) {
                    descente(&sol, &ind);
                } else { // backtracking
                    backtracking(&sol, &ind);
                }

            }
        }

        if(ind == 0) {
            continuer = 0;
        }

    }

    detruireSolution(&sol);

}


//------------------------------------------------------------------------------
void relaxation(Solution *sol, int* ind, int* sup, int* realisable) {

    *realisable = 0;

    // relaxation linéaire du problème
    int affecter = 1;

    int indVar = *ind;

    int relax = sol->z;
    int capa = sol->residu;

    while(affecter && indVar < sol->pb->nbVar) {

        // ajout d'un objet à la solution tant que possible
        if(capa >= sol->pb->poids[indVar]) {
            capa -= sol->pb->poids[indVar];
            relax += sol->pb->profit[indVar];
            sol->valeur[indVar] = 1;
            indVar ++;
        } else { // arrêt dès que ça ne l'est plus
            affecter = 0;
        }
    }

    if(capa == 0) {
        *realisable = 1;
        sol->residu = 0;
        *ind = sol->pb->nbVar;
        sol->z = relax;
    } else { // si la solution n'est pas réalisable, il faut annuler les changements
        for(int i = *ind; i < indVar; i++) {
            sol->valeur[i] = 0;
        }
    }

    if(capa > 0 && indVar < sol->pb->nbVar) { // toutes les variables n'ont pas été affectées et toute la capacite n'a pas été utilisée
        relax += (int)floor(((double)capa/(double)sol->pb->poids[indVar])*(double)sol->pb->profit[indVar]);
    }

    *sup = relax;
}

//------------------------------------------------------------------------------
void descente(Solution *sol, int* ind) {

    while(*ind < sol->pb->nbVar) {

        // ajout de tous les objets possibles et mise à jour de la solution
        if(sol->pb->poids[*ind] <= sol->residu) {
            sol->valeur[*ind] = 1;
            sol->residu -= sol->pb->poids[*ind];
            sol->z += sol->pb->profit[*ind];
        }
        *ind += 1;

    }
    // la descente conduit toujours à une feuille de l'arbre
    *ind = sol->pb->nbVar;

}

//------------------------------------------------------------------------------
void backtracking(Solution *sol, int* ind) {

    int continuer = 1;

    while(continuer && *ind > 0) {
        if(sol->valeur[*ind] == 1) { // mise à jour de la solution et arret du backtracking
            sol->valeur[*ind] = 0; // réaffectation de la variable à 0
            sol->z -= sol->pb->profit[*ind];
            sol->residu += sol->pb->poids[*ind];
            continuer = 0;
            *ind += 1;
        } else { // la dernière valeur affectée à 1 n'a pas été trouvée
            *ind -= 1;
        }
    }

}
