CC = gcc
CFLAGS = -Wall -Wextra -g

build: main.c pinyin.c pinyin.h main.h
	$(CC) $(CFLAGS) main.c pinyin.c -o build

run: build
	./build

clean:
	rm -f build

.PHONY: run clean
