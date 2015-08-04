CC=gcc
SOURCE=src
LIB_TARGET=lib
BIN_TARGET=bin
CFLAGS=-g
PROGNAME=program

all: program

program: main.o bin
	$(CC) $(CFLAGS) $(LIB_TARGET)/main.o -o $(BIN_TARGET)/$(PROGNAME)

main.o: src/main.c $(LIB_TARGET)
	$(CC) $(CFLAGS) -c $(SOURCE)/main.c -o $(LIB_TARGET)/main.o

lib:
	mkdir $(LIB_TARGET)

bin:
	mkdir $(BIN_TARGET)

clean:
	rm -rf $(LIB_TARGET) $(BIN_TARGET)
