/**
 * \file glpkSolver.c
 * \brief solver basé sur glpk pour le problème du sac à dos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glpk.h>

#include "Probleme.h"
#include "Solution.h"

/**
 * \brief résolution du problème du sac à dos avec glpk
 * \param pb l'instance du problème à résoudre
 * \param sol une solution optimale du problème
 * \param temps_ecoule le temps mis pour résoudre l'instance
 */
void resoudre(Probleme* pb, Solution* sol, double* temps_ecoule);

//------------------------------------------------------------------------------
int main(int argc, char** argv) {

    if(argc > 1) {

        Probleme pb;

        chargerProbleme(&pb, argv[1]);

        // afficherProbleme(&pb);

        Solution sol;
        creerSolution(&pb, &sol);

        double temps_ecoule;
        resoudre(&pb, &sol, &temps_ecoule);

        printf("\nSolution optimale du problème avec glpk : \n");
        // afficherSolution(&sol);
        printf("z = %d\n\n\n", sol.z);
        printf("temps écoulé : %fs\n", temps_ecoule);

        detruireSolution(&sol);

        detruireProbleme(&pb);

    } else {
        printf("Veuillez donner le nom d'une instance valide avec le programme.\n");
    }


    return 0;
}

//------------------------------------------------------------------------------
void resoudre(Probleme* pb, Solution* sol, double* temps_ecoule) {

    //désactivation du log de glpk
    glp_term_out(0);

    glp_prob* prob;
    prob = glp_create_prob();
    glp_set_prob_name(prob, "01kp");
    glp_set_obj_dir(prob, GLP_MAX);

    glp_add_rows(prob, 1); // une seule contrainte, sac monodimensionnel

    glp_set_row_bnds(prob, 1, GLP_UP, 0.0, (double)pb->k); // contrainte du problème

    // ajout des variables
    glp_add_cols(prob, pb->nbVar);
    for(int i = 0; i < pb->nbVar; i++) {
        glp_set_col_kind(prob, i+1, GLP_BV); // type de variable
        glp_set_col_bnds(prob, i+1, GLP_DB, 0.0, 1.0); // bornes sur les variables
        glp_set_obj_coef(prob, i+1, (double)pb->profit[i]);
    }

    // matrice creuse des contraintes
    int* ia = malloc((long unsigned int)(pb->nbVar+1)*sizeof(int)); // indices des lignes
    int* ja = malloc((long unsigned int)(pb->nbVar+1)*sizeof(int)); // indices des colonnes
    double* ar = malloc((long unsigned int)(pb->nbVar+1)*sizeof(double));

    // initialisation de la matrice des contraintes, f***ing glpk -> indices à 1
    for(int i = 0; i < pb->nbVar; i++) {
        ia[i+1] = 1; // ligne 1
        ja[i+1] = i+1; // colonne i+1
        ar[i+1] = (double)pb->poids[i];
    }

    // chargement de la matrice
    glp_load_matrix(prob, pb->nbVar, ia, ja, ar);

    clock_t begin = clock();
    // résolution
    glp_simplex(prob, NULL);
    glp_intopt(prob, NULL);
    clock_t end = clock();

    *temps_ecoule = (double)(end - begin) / CLOCKS_PER_SEC;

    sol->z = (int)glp_mip_obj_val(prob);
    for(int i = 0; i < pb->nbVar; i++) {
        sol->valeur[i] = (int)(glp_mip_col_val(prob, i+1)+0.5);
    }

    free(ia);
    free(ja);
    free(ar);

    glp_delete_prob(prob);
}
