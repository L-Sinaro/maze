CC=gcc
CFLAGS= -Wall -Wextra -g
LDFLAGS= -lSDL2 -lSDL2_ttf -lSDL2_image
EXEC=snake

all: $(EXEC) clean

$(EXEC): snake.o
	$(CC) -o $@ $^ $(LDFLAGS) 
snake.o : snake.c snake.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o
	
mrproper: 
	clean
	rm -f $(EXEC)