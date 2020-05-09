CC = gcc
CFLAGS = -W -Wall -Wextra

default: driver

linkedlist.o: linkedlist.c
	$(CC) -c $(CFLAGS) $^ -o $@

driver: driver.c linkedlist.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) *.o driver
