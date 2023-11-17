.PHONY: clean build
build: perseusTest
all: perseusTest
clean:

CFLAGS := -Werror -Wall

perseusTest: main.c
	$(CC) $^ -o $@ $(CFLAGS)