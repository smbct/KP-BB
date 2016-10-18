/**
 * \file Probleme.h
 * \brief définition d'une structure de donnée d'instance pour le 01KP
 */

#ifndef PROBLEME_H
#define PROBLEME_H

typedef struct {

    int nbVar;
    int* profit;
    int* poids;
    int k; // capacité

} Probleme;

/**
 * \brief chargement d'une instance à partir d'un fichier
 * \param pb le problème à charger
 * \param nom le nom du fichier contenant l'instance
 */
void chargerProbleme(Probleme* pb, char* nom);


/**
 * \brief affichage du problème en console
 * \param pb le problème à afficher
 */
void afficherProbleme(Probleme* pb);

/**
 * \brief désallocation du problème
 * \param pb le problème à désallouer
 */
void detruireProbleme(Probleme* pb);

#endif // PROBLEME_H
