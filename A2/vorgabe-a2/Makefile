CC=gcc
CFLAGS=-Wall -ansi -pedantic -D_XOPEN_SOURCE -D_POSIX_SOURCE -D_GNU_SOURCE
LDFLAGS=-pthread

prime: prime.c
	$(CC) $(CFLAGS) -o prime $< $(LDFLAGS)
	
# fuer Zusatzaufgabe 2.5:
prime-ringbuffer: prime.c
	$(CC) $(CFLAGS) -DRINGBUFFER -o prime-ringbuffer $< $(LDFLAGS)

clean:
	rm -f prime prime-ringbuffer *.o

test: prime
	./prime

.PHONY: clean test
