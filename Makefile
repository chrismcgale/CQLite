CC = gcc
CFLAGS = -Wall -g
OBJ = main.o


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

my_program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)