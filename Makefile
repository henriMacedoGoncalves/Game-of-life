.PHONY: docs

CFLAGS = -g -Wall
IFLAGS = -Iinclude
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
LIB = -L -ljeu
OPATH = obj
CREP = mkdir -p

vpath %.h include
vpath %.c src
vpath %.o obj

ifeq (TEXTE,$(MODE))
main : main.o libjeu.a
	$(CC) $(CFLAGS) -o $@ $(OPATH)/main.o lib/libjeu.a $(CFLAGS) $(LDFLAGS) $(LIB)
	$(CREP) bin
	mv $@ bin

main.o : src/main.c
	$(CC) $(CPPFLAGS) $(LIB) -c $< $(LDFLAGS)

else
cairo : cairo.o libjeu.a
	$(CC) $(CFLAGS) -o $@ $(OPATH)/cairo.o lib/libjeu.a $(CFLAGS) $(LDFLAGS) $(LIB)
	$(CREP) bin
	mv $@ bin

cairo.o : src/cairo.c
	$(CC) $(CPPFLAGS) $(LIB) -c $< $(LDFLAGS)

endif

#main.o : main.c grille.h io.h jeu.h
#cairo.o : cairo.c grille.h io.h jeu.h
#jeu.o : jeu.c jeu.h grille.h	
#io.o : io.c io.h grille.h jeu.h
#grille.o : grille.c grille.h

#%.o : %.c
#	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

libjeu.a : jeu.o io.o grille.o
	ar rcs $@ $^
	ranlib $@
	$(CREP) $(OPATH) lib
	mv *.o $(OPATH)
	mv $@ lib

clean :
	rm -r bin $(OPATH) docs/html docs/latex lib

dist : 
	tar -Jcvf MacedoGonçalvesHenri-GoL-version.tar.xz src include docs Makefile README.md

docs:
	doxygen docs/doxyfile
