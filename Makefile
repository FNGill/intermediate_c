CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic  -Wwrite-strings -Wvla -Wfloat-equal

run: main
	valgrind --leak-check=full --show-leak-kinds=all ./main

main:  main.c
	$(CC) $(CFLAGS) $^ -o $@ -lreadline

debug: CFLAGS += -DDEBUG 

clean:
	rm -f *.o main

.PHONY: run clean