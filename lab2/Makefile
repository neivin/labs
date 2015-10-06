CC = gcc
EXE = program
all: $(EXE)

$(EXE): hello.o main.o
	$(CC) hello.o main.o -o $(EXE) -lm

main.o: hello.h main.c
	$(CC) -c main.c

hello.o: hello.h hello.c 
	$(CC) -c hello.c
clean:
	rm -f hello.o
	rm -f main.o
	rm -f $(EXE)
