/**
 * \file jeu.c
 * code pour l'evolution du jeu
 * \author Henri Macedo Gonçalves
 */
#include "jeu.h"

/**
 * compte le nombre de voisins vivants de la cellule (i,j)
 * les bords sont cycliques
 * \fn int compte_voisins_vivants-cycliques(int i, int j, grille g);
 * \param i ligne
 * \param j colonne
 * \param g grille
 * \return v le comptage si les voisins sont vivants ou pas
 */
int compte_voisins_vivants_cycliques(int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	return v;
}
/**
 * compte le nombre de voisins vivants de la cellule (i,j)
 * les bords sont non-cycliques
 * \fn int compte_voisins_vivants_non_cycliques(int i, int j, grille g);
 * \param i ligne
 * \param j colonne
 * \param g grille
 * \return v le comptage si les voisins sont vivants ou pas
 */
int compte_voisins_vivants_non_cycliques(int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	for (int k=-1; k < 2; k++){
		for (int p=-1; p < 2; p++){
			if(i+k==-1 || i+k==l || j+p==-1 || j+p==c || (k==0 && p==0)){
				v += 0;
			}
			else {
				v+= est_vivante(i+k,j+p,g);
			}
		}
	}
	return v;
}

/**
 * fait evoluer la grille g d'un pas de temps
 * \fn void evolue(grille *g, grille *gc);
 * \param g grille
 * \param gc grille
 * \param viellissement mode de viellissement
 * \return void
 */
void evolue (grille *g, grille *gc,int viellissement){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants(i, j, *gc);

			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( (v!=2 && v!= 3) || (g->cellules[i][j] == 8 && viellissement == 1)) 
				set_morte(i,j,*g);
				else
				viellir(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
