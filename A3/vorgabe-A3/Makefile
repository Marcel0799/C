CC = gcc -pthread
FLAGS = -std=c11 -Wall -Wpedantic -D_POSIX_C_SOURCE=200112L

all: b c extended

clean:
	rm -f *.o 3_b 3_c 3_extended

b: 3_b

c: 3_c

extended: 3_extended

3_b: main.o 3_b.o
	$(CC) -o $@ $^

3_c: main.o 3_c.o
	$(CC) -o $@ $^

3_extended: main.o 3_extended.o
	$(CC) -o $@ $^
	
%.o: %.c main.h
	$(CC) $(FLAGS) -c -o $@ $<

.PHONY: all clean b c extended
