CC=gcc
CFLAGS=-I.
OBJ=buscaminas

buscaminas: $(OBJ).o
		$(CC) -o $@ $^ $(CFLAGS)

clean:
		rm $(OBJ) $(OBJ).o
