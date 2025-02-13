CC = gcc
CFLAGS = -Wall -g
OBJ = main.o input.o table.o statement.o meta.o


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

db: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)