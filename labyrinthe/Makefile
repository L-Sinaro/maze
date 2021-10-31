CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS= -lSDL2 -lSDL2_ttf -lSDL2_image -lm
EXEC=labyrinthe

all: $(EXEC) clean

$(EXEC): sdl.o main.o liste_chainee.o partition_arborescence.o graphe.o kruskal.o labyrinthe.o djikstra.o tas.o Aetoile.o parcours_profondeur.o
	$(CC) -o $@ $^ $(LDFLAGS) 

sdl.o: sdl.c sdl.h
	$(CC) $(CFLAGS) -o $@ -c $<

liste_chainee.o: liste_chainee.c liste_chainee.h
	$(CC) $(CFLAGS) -o $@ -c $<

partition_arborescence.o: partition_arborescence.c partition_arborescence.h
	$(CC) $(CFLAGS) -o $@ -c $<

graphe.o: graphe.c graphe.h partition_arborescence.h
	$(CC) $(CFLAGS) -o $@ -c $<

kruskal.o: kruskal.c kruskal.h
	$(CC) $(CFLAGS) -o $@ -c $<

labyrinthe.o: labyrinthe.c labyrinthe.h
	$(CC) $(CFLAGS) -o $@ -c $<

djikstra.o: djikstra.c djikstra.h
	$(CC) $(CFLAGS) -o $@ -c $<

tas.o: tas.c tas.h
	$(CC) $(CFLAGS) -o $@ -c $<

Aetoile.o: Aetoile.c Aetoile.h
	$(CC) $(CFLAGS) -o $@ -c $<

parcours_profondeur.o: parcours_profondeur.c parcours_profondeur.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

mrproper: 
	clean
	rm -f $(EXEC)