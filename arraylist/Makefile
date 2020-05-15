CC = gcc
CFLAGS = -W -Wall -Wextra
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

default: example

example: example_arraylist

test: test_arraylist

arraylist.o: src/arraylist.c
	$(CC) -c $(CFLAGS) $^

example_arraylist: examples/example_arraylist.c arraylist.o
	$(CC) $(CFLAGS) $^ -o $@

test_arraylist: tests/test_arraylist.c arraylist.o
	$(CC) $(CFLAGS) $^ $(TEST_LIBS) -o $@

clean:
	$(RM) *.o *_arraylist
