CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=
EXEC=tas

all: $(EXEC) clean

$(EXEC): tas.o main.o
	$(CC) -o $@ $^ $(LDFLAGS) 

tas.o: tas.c tas.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

mrproper: 
	clean
	rm -f $(EXEC)