CC=gcc
CFLAGS= -Wall -Wextra -g
LDFLAGS= -lSDL2 -lSDL2_ttf -lSDL2_image
EXEC=game-of-life

all: $(EXEC) clean

$(EXEC): game-of-life.o sdl.o
	$(CC) -o $@ $^ $(LDFLAGS) 
game-of-life.o : game-of-life.c game-of-life.h
	$(CC) $(CFLAGS) -o $@ -c $<
sdl.o: sdl.c sdl.h game-of-life.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o
	
mrproper: 
	clean
	rm -f $(EXEC)