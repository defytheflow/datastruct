CC = gcc
CFLAGS = -W -Wall -Wextra
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

default: driver

test: test_list

list.o: src/list.c
	$(CC) -c $(CFLAGS) $^

driver: driver.c list.o
	$(CC) $(CFLAGS) $^ -o $@

test_list: tests/test_list.c list.o
	$(CC) $^ $(TEST_LIBS) -o $@

clean:
	$(RM) *.o test_list driver
