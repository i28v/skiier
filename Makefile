CC=gcc
CFLAGS=-Wall -O2 -std=c99 -pedantic
LDFLAGS=-s
INCLUDES=-I/usr/include/SDL2
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf
SRC=$(wildcard src/*.c)
OBJ=$(SRC:%.c=%.o)
OUT=skiier

$(OUT): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OUT) $(OBJ)

