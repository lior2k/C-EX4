FLAGS = -Wall -g
CC = gcc

all: graph

lib_mygraphAlgo.a: algo.o node.o
	ar -rcs lib_mygraphAlgo.a algo.o node.o

algo.o: algo.c graph.h node.h algo.h
	$(CC) $(FLAGS) -c algo.c

main.o: main.c graph.h node.h algo.h
	$(CC) $(FLAGS) -c main.c

graph: main.o algo.o node.o lib_mygraphAlgo.a
	$(CC) $(FLAGS) -o graph main.o node.o algo.o lib_mygraphAlgo.a

node.o: node.c graph.h node.h
	$(CC) $(FLAGS) -c node.c

clean:
	rm -f *.o *.a *.so graph