CC = gcc
CPP = g++
CFLAGS = -W -Wall -Wextra
TEST_LIBS = -lgtest -lpthread

default: driver

linkedlist.o: linkedlist.c
	$(CC) -c $(CFLAGS) $^

driver: driver.c linkedlist.o
	$(CC) $(CFLAGS) $^ -o $@

tests: tests.cpp linkedlist.o
	$(CPP) $^ $(TEST_LIBS) -o $@

clean:
	$(RM) *.o driver tests
