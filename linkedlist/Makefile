CC = gcc
CFLAGS = -W -Wall -Wextra
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

default: driver

test: test_linkedlist

linkedlist.o: src/linkedlist.c
	$(CC) -c $(CFLAGS) $^

driver: driver.c linkedlist.o
	$(CC) $(CFLAGS) $^ -o $@

test_linkedlist: tests/test_linkedlist.c linkedlist.o
	$(CC) $^ $(TEST_LIBS) -o $@

clean:
	$(RM) *.o test_linkedlist driver
