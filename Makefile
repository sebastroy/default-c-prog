all: program

program: main.o bin
	gcc -g lib/main.o -o bin/program

main.o: src/main.c lib
	gcc -g -c src/main.c -o lib/main.o

lib:
	mkdir lib

bin:
	mkdir bin

clean:
	rm -rf lib bin
