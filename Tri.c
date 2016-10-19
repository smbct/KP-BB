/**
 * \file Tri.c
 * \brief implémentation de fonctions de tri
 */

#include <stdio.h>
#include <stdlib.h>

#include "Tri.h"

//------------------------------------------------------------------------------
void trierDecroissant(int nbVal, int* ind, double* val) {

    triRec(0, nbVal-1, ind, val);

}

//------------------------------------------------------------------------------
void triRec(int deb, int fin, int* ind, double* val) {

    if(deb < fin) {

        int milieu = (deb+fin)/2;

        if(deb < milieu) {
            triRec(deb, milieu, ind, val);
        }
        if(milieu+1 < fin) {
            triRec(milieu+1, fin, ind, val);
        }

        fusion(deb, milieu, fin, ind, val);

    }

}

//------------------------------------------------------------------------------
void fusion(int deb, int milieu, int fin, int* ind, double* val) {

    int* triees = malloc((long unsigned int)(fin-deb+1)*sizeof(int));

    int indGch = deb;
    int indDte = milieu+1;

    for(int i = 0; i < fin-deb+1; i++) { // parcours de toutes les valeurs à trier

        int cas = 0;

        // verif des indices
        if(indGch > milieu) { // droite doit avancer, gauche ne peut plus
            cas = 1;
        } else if(indDte > fin) { // gauche doit avancer, droite ne peut plus
            cas = -1;
        }

        // cas où la c'est l'élément du tableau de droite qui est sélectionné
        if(cas != -1 && (cas == 1 || val[ind[indDte]] > val[ind[indGch]])) {
            triees[i] = ind[indDte];
            indDte ++;
        } else { // cas où c'est l'élément de gauche
            triees[i] = ind[indGch];
            indGch ++;
        }
    }

    // copie des valeurs triees
    for(int i = deb; i <= fin; i++) {
        ind[i] = triees[i-deb];
    }

    // libération mémoire du tableau trié
    free(triees);

}
