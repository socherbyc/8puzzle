CC=gcc
# valgrind ./8puzzle
# CFLAGS=-Iheaders -Wall -O0 -lm -g
# gprof ./8puzzle
# CFLAGS=-Iheaders -Wall -O2 -lm -pg
# production
CFLAGS=-Iheaders -Wall -O2 -lm -finline-functions
OBJ=src/puzzle.o src/stack.o src/factoradic.o src/bitset.o
MAIN=src/main.o $(OBJ)
TESTS=tests/assert_bitset.c

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

8puzzle: $(MAIN)
	$(CC) -o $@.out $^ $(CFLAGS)

assert_bitset: tests/assert_bitset.c $(OBJ)
	$(CC) -o $@.out $^ $(CFLAGS)

assert_factoradic: tests/assert_factoradic.c $(OBJ)
	$(CC) -o $@.out $^ $(CFLAGS)

assert_stack: tests/assert_stack.c $(OBJ)
	$(CC) -o $@.out $^ $(CFLAGS)

clean:
	rm -f src/*.o