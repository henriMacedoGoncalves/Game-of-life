/**
 * \file grille.h
 * header pour les grilles
 * \author Henri Macedo Gonçalves
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \typedef typedef struct{int nbl; int nbc; int** cellules;} grille;};
 * structure grille : nombre de lignes, nombres de colonnes, tableau de tableau de cellules
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

/**
 * rend vivante la cellule (i,j) de la grille g
 * \fn static inline void set_vivante(int i, int j, grille g);
 * \param i ligne
 * \param j colonne
 * \param g grille
 * \return void
 */
static inline void set_vivante(int i, int j, grille g){if(g.cellules[i][j] != -1) g.cellules[i][j] = 1;}

/**
 * rend morte la cellule (i,j) de la grille g
 * \fn static inline void set_morte(int i, int j, grille g);
 * \param i ligne
 * \param j colonne
 * \param g grille
 * \return void
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * teste si la cellule (i,j) de la grille g est vivante
 * \fn static inline int est_vivante(int i, int j, grille g);
 * \param i ligne
 * @param j colonne
 * @param g grille
 * \return 1 si vrai sinon 0 
 */
static inline int est_vivante(int i, int j, grille g){
    return g.cellules[i][j] > 0;
}

/**
 * incremente la valeur de la cellule(i,j) de la grille g
 * \fn static inline int viellissement(int i, int j);
 * \param i ligne
 * \param j colonne
 * \param g grille
 * \return g.cellules[i][j] + 1
 */
static inline int viellir(int i, int j, grille g){
    return ++g.cellules[i][j];
}

/**
 * rend non-viable la cellule(i,j) de la grille g
 * \fn static inline void set_non_viable(int i, int j, grille g);
 * \param i ligne
 * \param j colonne
 * \param g grille
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
