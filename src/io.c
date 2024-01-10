/**
 * \file io.c
 * traitement de l'affichage
 * \author Henri Macedo Gonçalves
 */
#include "io.h"

int cyclique;
int viellissement;
int temps;

/**
 * affichage d'un trait horizontal
 * \fn void affiche_trait(int c);
 * \param c nombre de trait à afficher
 * \return void
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * affichage d'une ligne de la grille
 * \fn void affiche_ligne(int c, int* ligne);
 * \param c nombre de ligne à afficher
 * \param ligne ligne
 * \return void
 */
void affiche_ligne (int c, int* ligne){
	int i;
	if(viellissement == 1){
		for (i=0; i<c; ++i)
			if (ligne[i] == 0 ) printf ("|   "); else if (ligne[i] == -1) printf("| X "); else printf ("| %d ", ligne[i]);
		printf("|\n");
	} else {
		for (i=0; i<c; ++i)
			if (ligne[i] == 0 ) printf ("|   "); else if (ligne[i] == -1) printf("| X "); else printf ("| 0 ");
		printf("|\n");
	}

	
	return;
}

/**
 * affichage d'une grille
 * \fn void affiche_grille(grille g); 
 * @param g grille
 * \return void
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\nTemps: %d\n", temps);
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/**
 * effacement d'une grille
 * \fn void efface_grille(grille g);
 * \param g grille
 * \return void
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 * debute le jeu
 * \fn void debut_jeu(grille *g, grille *gc);
 * \param g grille
 * \param gc grille
 * \return void
 */
void debut_jeu(grille *g, grille *gc){
	compte_voisins_vivants = &compte_voisins_vivants_cycliques;
	char c = getchar();
	cyclique = 1;
	viellissement = 0;
	temps = 1;
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc,viellissement);
				efface_grille(*g);
				system("clear");
				if(cyclique == 1)	printf("\nCyclique activé\n");
				else printf("\nCyclique déactivé\n");
				if(viellissement == 1)	printf("Viellisme activé\n");
				else printf("Viellisme déactivé\n");
				affiche_grille(*g);
				printf("\n");
				break;
			}
			case 'n' :
			{ // touche "n" pour changer de fichier .txt
				libere_grille(g);
				libere_grille(gc);
				char nomFichier[50];
				printf("Nom du fichier: ");
				scanf("%s", nomFichier);
				init_grille_from_file(nomFichier, g);
				alloue_grille(g->nbl,g->nbc, gc);
				affiche_grille(*g);
				temps = 0;
				break;
			}
			case 'c' :
			{ // touche "c" pour changer entre cyclique et non-cyclique
				if (cyclique == 1){
					cyclique = 0;
					compte_voisins_vivants = &compte_voisins_vivants_non_cycliques;
				} else {
					cyclique = 1;
					compte_voisins_vivants = &compte_voisins_vivants_cycliques;	
				}
				break;
			}
			case 'v' :
			{ // touche "v" pour changer le mode vieillisme
				if (viellissement == 1){
					viellissement = 0;
				} else {
					viellissement = 1;
				}
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	temps++;
	}
	return;	
}
