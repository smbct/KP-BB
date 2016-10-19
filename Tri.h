/**
 * \file Tri.h
 * \brief définition de fonctions de tri
 */

/**
 * \brief tri le tableau ind en fonction de certaines valeurs
 * \param nbVal le nombre de valeur des tableaux
 * \param ind les indices des éléments à trier
 * \param val les valeurs des éléments à trier
 */
void trier(int nbVal, int* ind, int* val);

/**
 * \brief procédure récursive de tri fusion
 * \param deb l'indice de début du tableau à trier
 * \param fin l'indice de fin du tableau à trier
 * \param ind les indices des valeurs à trier
 * \param val les valeurs à trier
 */
void triRec(int deb, int fin, int* ind, int* val);

/**
 * \brief fusion en un tableau trié de deux sous-tableaux triés
 * \param deb indice de départ du premier tableau
 * \param milieu indice de fin du premier tableau
 * \param fin indice de fin du deuxième tableau
 * \param ind tableaux des indices des valeurs à trier
 * \param val valeurs à trier
 */
void fusion(int deb, int milieu, int fin, int* ind, int* val);
