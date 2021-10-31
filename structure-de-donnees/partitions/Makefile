CC=gcc
CFLAGS=-g -Wall -Wextra
LDFLAGS=`pkg-config libgvc --cflags` -g -lcgraph -lgvc
EXEC=main

all: $(EXEC) clean

$(EXEC): main.o graphviz-partitions.o partitions.o liste-chainee.o
	$(CC) -o $@ $^ $(LDFLAGS) 
liste-chainee.o: liste-chainee.c liste-chainee.h
	$(CC) $(CFLAGS) -o $@ -c $<
partitions.o: partitions.c partitions.h
	$(CC) $(CFLAGS) -o $@ -c $<
graphviz-partitions.o : graphviz-partitions.c graphviz-partitions.h
	$(CC) $(CFLAGS) -o $@ -c $<
main.o : main.c main.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

mrproper: 
	clean
	rm -f $(EXEC)