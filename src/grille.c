/**
 * \file grille.c
 * code pour les grilles
 * \author Henri Macedo Gonçalves
 */
#include "grille.h"

/**
 * alloue une grille de taille l*c et initialise toutes les cellules à mortes
 * \fn void alloue_grille( int l, int c, grille* g);
 * \relatesalso grille
 * \param l lignes
 * \param c colonnes
 * \param g grille
 * \return void
 */
void alloue_grille( int l, int c, grille* g){
	g->nbl= l;
	g->nbc= c;
	g->cellules = (int**)malloc(g->nbl*sizeof(int*));
	for (int i = 0; i < g->nbl; i ++){
		g->cellules[i]=(int*)malloc(g->nbc*sizeof(int));
		for (int j = 0; j < g->nbc; j++){
			set_morte(i,j,*g);
		}
	}
	return;
}

/**
 * libère une grille
 * \fn void libere_grille(grille* g);
 * \relatesalso grille 
 * \param g grille
 * \return void
 */
void libere_grille(grille* g){
	for (int i = 0; i < g->nbl; i++){
		free(g->cellules[i]);
	}
	free(g->cellules);
	return;
}

/**
 * alloue et initialise la grille g à partir d'un fichier
 * \fn void init_grille_from_file(char* filename, grille*g);
 * \param filename nom du fichier
 * \param g grille
 * \return void
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0,non_viables = 0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", &non_viables);
	for (n=0; n< non_viables; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}
	fclose (pfile);
	return;
}

/**
 * recopie gs dans gd (sans allocation)
 * \fn void copie_grille(grille gs, grille gd);
 * \param gs grille copié de gd
 * \param gd grille
 * \return void
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
