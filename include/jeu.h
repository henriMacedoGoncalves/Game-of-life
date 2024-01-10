#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * modulo modifié pour traiter correctement les bords i=0 et j=0
 * dans le calcul des voisins avec bords cycliques
 * \fn static inline int modulo(int i, int m);
 * \param i ligne ou colonne
 * \param m modulo
 * \return ligne ou colonne
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

int compte_voisins_vivants_cycliques (int i, int j, grille g);

int compte_voisins_vivants_non_cycliques (int i, int j, grille g);

/**
 * pointeur de fonction
 */
int (*compte_voisins_vivants)(int, int, grille);

void evolue (grille *g, grille *gc,int viellissement);

#endif
