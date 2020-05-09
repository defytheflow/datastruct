CC = gcc
CFLAGS = -W -Wall -Wextra

default: test_vector

vector.o: vector.c
	$(CC) -c $(CFLAGS) $^ -o $@

test_vector: test_vector.c vector.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) *.o test_vector

