CC = gcc
CFLAGS= -Wall -g
EXE = codemon

all: $(EXE)

$(EXE): packager.o checker.o parser.o loader.o client.o codemon.o
	$(CC) packager.o checker.o parser.o loader.o client.o codemon.o -o $(EXE)

codemon.o: arch.h common.h loader.h parser.h checker.h packager.h codemon.c
	$(CC) -c codemon.c

packager.o: arch.h common.h parser.h checker.h packager.h packager.c
	$(CC) -c packager.c

checker.o: arch.h common.h parser.h checker.h checker.c
	$(CC) -c checker.c

parser.o: arch.h common.h parser.h parser.c
	$(CC) -c parser.c

loader.o: arch.h common.h loader.h loader.c
	$(CC) -c loader.c

client.o: arch.h common.h client.c
	$(CC) -c client.c

clean:
	rm -f codemon
	rm -f client.o loader.o parser.o checker.o packager.o codemon.o