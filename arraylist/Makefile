CC = gcc
CFLAGS = -W -Wall -Wextra
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

default: driver

test: test_arraylist

arraylist.o: src/arraylist.c
	$(CC) -c $(CFLAGS) $^

driver: driver.c arraylist.o
	$(CC) $(CFLAGS) $^ -o $@

test_arraylist: tests/test_arraylist.c arraylist.o
	$(CC) $(CFLAGS) $^ $(TEST_LIBS) -o $@

clean:
	$(RM) *.o test_arraylist driver
