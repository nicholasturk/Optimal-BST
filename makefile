CC = gcc
CFLAGS = -Wall -ansi -g -Wall
DEPS = definitions.h
OBJ = main.o helper.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(OBJ)
	gcc -o $@ $^

clean:
	rm *.o