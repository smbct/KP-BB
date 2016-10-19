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
 * \brief chargement d'une instance à partir d'un fichier et tri des variables par utilité décroissante
 * \param ord le problème à charger
 * \param nom le nom du fichier contenant l'instance
 */
void chargerProbleme(Probleme* ord, char* nom);

/**
 * \brief création d'un problème à partir d'un autre dans lequel les variables sont ordonnées par utilité
 * \param pb le problème original
 * \param ord le problème ordonné
 */
void creerProblemeOrdonne(Probleme* pb, Probleme* ord);

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

/**
 * \brief calcule des utilités des variables de l'instance pb
 * \param pb l'instance du problème
 * \param utilite les utilités calculées
 */
void calculerUtilites(Probleme* pb, double* utilite);

#endif // PROBLEME_H
