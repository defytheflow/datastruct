CC = gcc
CPP = g++
CFLAGS = -W -Wall -Wextra
TEST_LIBS = -lgtest -lpthread

# https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/

default: driver

arraylist.o: arraylist.c
	$(CC) -c $(CFLAGS) $^

driver: driver.c arraylist.o
	$(CC) $(CFLAGS) $^ -o $@

tests: tests.cpp arraylist.o
	$(CPP) $^ $(TEST_LIBS) -o $@

clean:
	$(RM) *.o driver tests
