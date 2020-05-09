CC = gcc
CFLAGS = -W -Wall -Wextra

default: driver

arraylist.o: arraylist.c
	$(CC) -c $(CFLAGS) $^ -o $@

driver: driver.c arraylist.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) *.o driver
