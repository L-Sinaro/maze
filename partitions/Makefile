CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS= `pkg-config libgvc --cflags` -g -lcgraph -lgvc
EXEC=partition

all: $(EXEC) clean

$(EXEC): partition_marqueurs.o main.o liste_chainee.o partition_arborescence.o implementation_graphviz.o
	$(CC) -o $@ $^ $(LDFLAGS) 
main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<
partition_marqueurs.o: partition_marqueurs.c partition_marqueurs.h
	$(CC) $(CFLAGS) -o $@ -c $<

liste_chainee.o: liste_chainee.c liste_chainee.h
	$(CC) $(CFLAGS) -o $@ -c $<

partition_arborescence.o: partition_arborescence.c partition_arborescence.h
	$(CC) $(CFLAGS) -o $@ -c $<

implementation_graphviz.o: implementation_graphviz.c implementation_graphviz.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

mrproper: 
	clean
	rm -f $(EXEC)