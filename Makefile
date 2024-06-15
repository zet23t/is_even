CC = gcc
CFLAGS = -fmax-include-depth=2000

all:
	$(CC) $(CFLAGS) is_even.c -o is_even

run: all
	./is_even

code:
	$(CC) $(CFLAGS) -E is_even.c -o is_even.i