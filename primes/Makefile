SRC_FILES=primes.c
CFLAGS=-lm -O2
all: main

main: $(SRC_FILES)
	gcc -std=gnu11 -g -o $@ $(SRC_FILES) $(CFLAGS)

clean:
	rm -f main

run: main
	./main
