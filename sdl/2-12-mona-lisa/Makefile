CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image
EXEC=game

all: $(EXEC) clean

$(EXEC): scoring.o game-engine.o sdl.o
	$(CC) -o $@ $^ $(LDFLAGS) 
scoring.o: scoring.c scoring.h
	$(CC) $(CFLAGS) -o $@ -c $<
game-engine.o: game-engine.c game-engine.h
	$(CC) $(CFLAGS) -o $@ -c $<
sdl.o: sdl.c scoring.h game-engine.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

mrproper: 
	clean
	rm -f $(EXEC)