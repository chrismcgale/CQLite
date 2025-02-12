CC = gcc
CFLAGS = -Wall -g
OBJ = main.o


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

db: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)