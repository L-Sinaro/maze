CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS= `pkg-config libgvc --cflags` -g -lcgraph -lgvc
EXEC=composantes_connexes

all: $(EXEC) clean

$(EXEC): matrices.o main.o liste_chainee.o partition_arborescence.o implementation_graphviz.o graphe.o kruskal.o
	$(CC) -o $@ $^ $(LDFLAGS) 

matrices.o: matrices.c matrices.h
	$(CC) $(CFLAGS) -o $@ -c $<

liste_chainee.o: liste_chainee.c liste_chainee.h
	$(CC) $(CFLAGS) -o $@ -c $<

partition_arborescence.o: partition_arborescence.c partition_arborescence.h
	$(CC) $(CFLAGS) -o $@ -c $<

implementation_graphviz.o: implementation_graphviz.c implementation_graphviz.h
	$(CC) $(CFLAGS) -o $@ -c $<

graphe.o: graphe.c graphe.h partition_arborescence.h
	$(CC) $(CFLAGS) -o $@ -c $<

kruskal.o: kruskal.c kruskal.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

mrproper: 
	clean
	rm -f $(EXEC)