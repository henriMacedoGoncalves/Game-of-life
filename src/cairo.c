/**
 * \file cairo.c
 * pour afficher graphiquement
 * \author Henri Macedo Gonçalves
 */
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "grille.h"
#include "jeu.h"
#include "io.h"

#define SIZEX 1000
#define SIZEY 1000

extern int temps;
extern int cyclique;
extern int viellissement;
/** 
 * affiche graphiquement la grille g sur la surface
 * \fn void paint(cairo_surface_t *surface, grille g);
 * \param surface surface
 * \param g grille
 */
void paint(cairo_surface_t *surface,grille g)
{
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);
	int tailleXY = 600;
	int caseX = tailleXY/g.nbc;	//8 = nbc
	int caseY = tailleXY/g.nbl;	//8 = nbl
	char evolution[20];
	sprintf(evolution,"Temps: %d",temps);
	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	// entete
	cairo_set_source_rgb (cr, 0.2, 0.2, 0.2);
	cairo_rectangle(cr,0,0,SIZEX,100);
	cairo_fill(cr);	

	cairo_set_source_rgb(cr, 0.5,0.5,1.0);
	cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,30);
	cairo_move_to(cr, SIZEX/2-75,60);
	cairo_show_text(cr,evolution);

	if(cyclique==1){
		cairo_set_source_rgb(cr, 0.5,1.0,0.5);
		cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size(cr,15);
		cairo_move_to(cr,15,50);
		cairo_show_text(cr,"Cyclique");
		cairo_fill(cr);	
	} else{
		cairo_set_source_rgb(cr, 1.0,0.5,0.5);
		cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size(cr,15);
		cairo_move_to(cr,15,50);
		cairo_show_text(cr,"Cyclique");
		cairo_fill(cr);
	}

	if(viellissement==1){
		cairo_set_source_rgb(cr, 0.5,1.0,0.5);
		cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size(cr,15);
		cairo_move_to(cr, 15,80);
		cairo_show_text(cr,"Viellissement");
		cairo_fill(cr);
	} else {
		cairo_set_source_rgb(cr, 1.0,0.5,0.5);
		cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size(cr,15);
		cairo_move_to(cr, 15,80);
		cairo_show_text(cr,"Viellissement");
		cairo_fill(cr);
	}

	cairo_set_source_rgb(cr, 1.0,1.0,1.0);
	cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,15);
	cairo_move_to(cr, SIZEX-200,30);
	cairo_show_text(cr,"c : Cyclique");
	cairo_fill(cr);

	cairo_set_source_rgb(cr, 1.0,1.0,1.0);
	cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,15);
	cairo_move_to(cr, SIZEX-200,60);
	cairo_show_text(cr,"v : Viellissement");
	cairo_fill(cr);

	cairo_set_source_rgb(cr, 1.0,1.0,1.0);
	cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,15);
	cairo_move_to(cr, SIZEX-200,90);
	cairo_show_text(cr,"n : Grille");
	cairo_fill(cr);

	// Légende
	cairo_set_source_rgb(cr, 1.0,1.0,1.0);
	cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,20);
	cairo_move_to(cr, 50 ,160);
	cairo_show_text(cr,"Vivant");
	cairo_set_source_rgb(cr, 0.5,1.0,0.5);
	cairo_rectangle(cr, 20, 145, 15, 15);
	cairo_fill(cr);

	cairo_set_source_rgb(cr, 1.0,1.0,1.0);
	cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,20);
	cairo_move_to(cr, 50 ,190);
	cairo_show_text(cr,"Non-viable");
	cairo_set_source_rgb(cr, 1.0,0.5,0.5);
	cairo_rectangle(cr, 20, 175, 15, 15);
	cairo_fill(cr);

	cairo_set_source_rgb(cr, 1.0,1.0,1.0);
	cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,20);
	cairo_move_to(cr, 50 ,220);
	cairo_show_text(cr,"Age");
	cairo_set_source_rgb(cr, 0.5,1.0,0.5);
	cairo_rectangle(cr, 20, 205, 15, 15);
	cairo_fill(cr);
	cairo_set_source_rgb(cr, 0.0,0.0,0.0);
	cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,10);
	cairo_move_to(cr, 24,217);
	cairo_show_text(cr,"5");
	cairo_fill(cr);

	// Grille
	/*cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_rectangle(cr,200,145,tailleXY-1,tailleXY-1); // 8 8
	cairo_fill(cr);

	// colonnes de la grille
	for(int i = 1; i < g.nbl; i++){
		cairo_set_source_rgb(cr,0.0,0.0,0.0);
		cairo_move_to(cr,200+i*caseX,145);
		cairo_line_to(cr,200+i*caseX,145+tailleXY);
		cairo_stroke(cr);
	}

	// lignes de la grille
	for(int i = 1; i < g.nbc; i++){
		cairo_set_source_rgb(cr,0.0,0.0,0.0);
		cairo_move_to(cr,200,145+i*caseY);
		cairo_line_to(cr,200+tailleXY,145+i*caseY);
		cairo_stroke(cr);
	}*/
	
	// les cellules
	char age[10];
	for(int i = 0; i<g.nbl; i++){
		for(int j = 0; j < g.nbc; j++){
			cairo_rectangle(cr,200+j*caseX,145+i*caseY,caseX-1,caseY-1);
			if(g.cellules[i][j]==0)	cairo_set_source_rgb(cr,1.0,1.0,1.0);
			else if(g.cellules[i][j]==-1) cairo_set_source_rgb(cr,1.0,0.5,0.5);
			else if (g.cellules[i][j]>=1){
				if(viellissement==1){
					sprintf(age,"%d",g.cellules[i][j]);
					cairo_set_source_rgb(cr, 0.5,1.0,0.5);
					cairo_fill(cr);
					cairo_set_source_rgb(cr, 0.0,0.0,0.0);
					cairo_select_font_face(cr,"monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
					cairo_set_font_size(cr,10);
					cairo_move_to(cr, (200+j*caseX)+caseX/2,(145+i*caseY)+caseY/2);
					cairo_show_text(cr,age);
				} else cairo_set_source_rgb(cr, 0.5,1.0,0.5);
			}
			cairo_fill(cr);
		}
	}
	cairo_destroy(cr); // destroy cairo mask
}

int main (int argc, char **argv){
    if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
        return 1;
	}

	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	temps =0;
	cyclique=1;
	viellissement=0;
    grille g, gc;
    init_grille_from_file(argv[1], &g);
    alloue_grille(g.nbl, g.nbc, &gc);
    
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	compte_voisins_vivants = compte_voisins_vivants_cycliques;
	// run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs,g);
		} else if(e.type==ButtonPress){
			if(e.xbutton.button==1){
				evolue(&g,&gc,viellissement);
				temps++;
				paint(cs,g);
			} else if(e.xbutton.button==3){
				break;
			}
		} else if(e.type==KeyPress){
			if(e.xkey.keycode==XKeysymToKeycode(dpy,'c')){
				if (cyclique == 1){
					cyclique = 0;
					compte_voisins_vivants = &compte_voisins_vivants_non_cycliques;
				} else {
					cyclique = 1;
					compte_voisins_vivants = &compte_voisins_vivants_cycliques;	
				}
				paint(cs,g);
			}
			if(e.xkey.keycode==XKeysymToKeycode(dpy,'v')){
				if (viellissement == 1){
					viellissement = 0;
				} else {
					viellissement = 1;
				}
				paint(cs,g);
			}
			if(e.xkey.keycode==XKeysymToKeycode(dpy,'n')){
				libere_grille(&g);
				libere_grille(&gc);
				char nomFichier[50];
				printf("Nom du fichier: ");
				scanf("%s", nomFichier);
				init_grille_from_file(nomFichier, &g);
				alloue_grille(g.nbl,g.nbc, &gc);
				temps = 0;
				paint(cs,g);
			}
			
		}
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}
