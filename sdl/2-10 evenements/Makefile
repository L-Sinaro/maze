CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=-lSDL2
EXEC=jeu

all: $(EXEC) clean

jeu: jeu-de-la-vie-sinaro.o sdl.o
	$(CC) -o jeu jeu-de-la-vie-sinaro.o sdl.o $(LDFLAGS)

jeu-de-la-vie-sinaro.o: jeu-de-la-vie-sinaro.c jeu-de-la-vie-sinaro.h
	$(CC) -o jeu-de-la-vie-sinaro.o -c jeu-de-la-vie-sinaro.c $(CFLAGS)

sdl.o: sdl.c jeu-de-la-vie-sinaro.h sdl.h
	$(CC) -o sdl.o -c sdl.c $(CFLAGS)

clean:
	rm -f *.o
mrproper: clean
	rm -f $(EXEC)
