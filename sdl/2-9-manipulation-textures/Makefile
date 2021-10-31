CC=gcc
CFLAGS= -Wall -Wextra -g
LDFLAGS= -lSDL2 -lSDL2_ttf -lSDL2_image
EXEC=animation

all: $(EXEC) clean

$(EXEC): animation.o
	$(CC) -o $@ $^ $(LDFLAGS) 
animation.o : animation.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o
	
mrproper: 
	clean
	rm -f $(EXEC)