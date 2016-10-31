/**
 * \file BranchBound.c
 * \brief implémentation des fonctions de résolution de 01KP
 */

#include "BranchBound.h"
#include <stdio.h>
#include <math.h>

//------------------------------------------------------------------------------
void BranchAndBound(Solution* opt, int borne) {

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

            // relaxation du problème et calcule d'une borne supérieure
            switch(borne) {
                case 1:
                    relaxation1(&sol, &ind, &relax, &realisable);
                    break;
                case 2:
                    relaxation2(&sol, &ind, &relax, &realisable);
                    break;
                case 3:
                    relaxation3(&sol, &ind, &relax, &realisable);
                    break;
                default:
                    relaxation1(&sol, &ind, &relax, &realisable);
                    break;
            }


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
void relaxation1(Solution *sol, int* ind, int* sup, int* realisable) {

    *realisable = 0;

    // relaxation linéaire du problème
    int affecter = 1;

    int indVar = *ind;

    int relax = sol->z;
    int capa = sol->residu;

    // détermination de l'élément critique
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
        // relaxation continue
        relax += (int)floor(((double)capa/(double)sol->pb->poids[indVar])*(double)sol->pb->profit[indVar]);
    }

    *sup = relax;
}

//------------------------------------------------------------------------------
void relaxation2(Solution *sol, int* ind, int* sup, int* realisable) {

    *realisable = 0;

    // relaxation linéaire du problème
    int affecter = 1;

    int indVar = *ind;

    int relax = sol->z;
    int capa = sol->residu;

    // détermination de l'élément critique
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

        // bornes de Martello and Toth

        int U0 = -1, U1 = -1;
        if(indVar+1 < sol->pb->nbVar) {
            U0 = (int)floor( (double)capa * ( (double)sol->pb->profit[indVar+1] / (double)sol->pb->poids[indVar+1] ) );
        }
        if(indVar > *ind) {
            U1 = (int) floor( (double)sol->pb->profit[indVar] - ((double)sol->pb->poids[indVar] - (double)capa) * ((double)sol->pb->profit[indVar-1] / (double)sol->pb->poids[indVar-1]) );
        }
        relax += (U0 > U1 ? U0 : U1);

    }

    *sup = relax;
}


//------------------------------------------------------------------------------
void relaxation3(Solution* sol, int* ind, int* sup, int* realisable) {

    /*printf("début relaxation : \n");
    afficherSolution(sol);
    printf("z = %d\n", sol->z);*/

    *realisable = 0;

    // relaxation linéaire du problème
    int affecter = 1;

    int indVar = *ind;

    int relax = sol->z;
    int capa = sol->residu;

    // détermination de l'élément critique
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
    } else { // si la solution n'est pas réalisable, il faut annuler les changements et calculer les bornes

        for(int i = *ind; i < indVar; i++) {
            sol->valeur[i] = 0;
        }

        // calcule des bornes en imposant respectivement x_s = 1 et x_s = 0
        // calcule des nouveaux éléments critiques correspondant aux nouvelles contraintes
        int s_1 = *ind, s_0 = *ind;
        int j = *ind;
        int cs_0 = sol->residu, cs_1 = sol->residu-sol->pb->poids[indVar]; // les capacités résiduelles pour les nouveaux éléments critiques
        int sommePs_0 = 0, sommePs_1 = sol->pb->profit[indVar];
        int trouves1 = 0, trouves0 = 0;
        while(!trouves0 && j < sol->pb->nbVar) {

            if(!trouves0 && cs_0 >= sol->pb->poids[j]) {
                if(j != indVar) {
                    cs_0 -= sol->pb->poids[j];
                    sommePs_0 += sol->pb->profit[j];
                    if(s_0 < sol->pb->nbVar-1 && s_0+1 != indVar) {
                        s_0 ++;
                    } else if(s_0 + 1 == indVar) { // l'élément critique est sauté
                        s_0 += 2;
                    } else {
                        trouves0 = 1;
                    }
                }
            } else { // s_0 sera nécessairement >= à s_1
                trouves0 = 1;
            }

            if(!trouves1 && cs_1 >= sol->pb->poids[j]) {
                if(j != indVar) {
                    cs_1 -= sol->pb->poids[j];
                    sommePs_1 += sol->pb->profit[j];
                }
                if(s_1 < sol->pb->nbVar-1 && s_1+1 != indVar) {
                    s_1 ++;
                } else if(s_1 + 1 == indVar) { // on s'assure d'éviter l'élément critique
                    s_1 += 2;
                } else {
                    trouves1 = 1;
                }
            } else {
                trouves1 = 1;
            }

            j ++;
        }

        /*printf("debut : %d, fin : %d, s0 : %d, s1 : %d, indvar : %d\n", *ind, sol->pb->nbVar-1, s_0, s_1, indVar);
        printf("sommePs_0 : %d, cs_0 : %d, sommePs_1 : %d, cs_1 : %d\n", sommePs_0, cs_0, sommePs_1, cs_1);*/

        int U0 = sommePs_0;
        int U1 = sommePs_1;
        if(s_0 >= *ind && s_0 < sol->pb->nbVar) {
            U0 += (int)floor((double)cs_0 * ( (double)sol->pb->profit[s_0] / (double)sol->pb->poids[s_0] ) );
        }
        if(s_1 >= *ind && s_1 < sol->pb->nbVar) {
            U1 = sommePs_1 + (int)floor((double)cs_1 * ( (double)sol->pb->profit[s_1] / (double)sol->pb->poids[s_1] ) );
        }

        relax = sol->z + (U0 > U1 ? U0 : U1);

        /*printf("U0 : %d, U1: %d\n", sol->z + U0, sol->z + U1);
        printf("nouvelle borne : %d\n\n\n", relax);*/

        // printf("relax meilleure : %d\n", relax);

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

    while(continuer && *ind >= 0) {
        if(sol->valeur[*ind] == 1) { // mise à jour de la solution et arret du backtracking
            sol->valeur[*ind] = 0; // réaffectation de la variable à 0
            sol->z -= sol->pb->profit[*ind];
            sol->residu += sol->pb->poids[*ind];
            continuer = 0;
        } else { // la dernière valeur affectée à 1 n'a pas été trouvée
            *ind -= 1;
        }
    }

    *ind += 1;

}
