CC = gcc
CFLAGS = -W -Wall -Wextra
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

default: driver

test: test_vector

vector.o: src/vector.c
	$(CC) -c $(CFLAGS) $^

driver: driver.c vector.o
	$(CC) $(CFLAGS) $^ -o $@

test_vector: tests/test_vector.c vector.o
	$(CC) $(CFLAGS) $^ $(TEST_LIBS) -o $@

clean:
	$(RM) *.o test_vector driver
