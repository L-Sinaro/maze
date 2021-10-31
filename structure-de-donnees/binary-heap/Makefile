CC=gcc
CFLAGS=-g -Wall -Wextra
LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image
EXEC=binary-heap

all: $(EXEC) clean

$(EXEC): binary-heap.o
	$(CC) -o $@ $^ $(LDFLAGS) 
binary-heap.o: binary-heap.c binary-heap.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

mrproper: 
	clean
	rm -f $(EXEC)