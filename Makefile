.PHONY: clean build
build: perseusTest
all: perseusTest
clean:

CFLAGS := -Werror -Wall

perseusTest: main.c Runtime.c InstructionStream.c
	$(CC) $^ -o $@ $(CFLAGS)