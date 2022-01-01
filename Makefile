FLAGS = -Wall -g

all: graph

lib_mygraphAlgo.a: algo.o
	ar -rcs lib_mygraphAlgo.a algo.o

algo.o: algo.c graph.h
	gcc $(FLAGS) -c algo.c

main.o: main.c graph.h
	gcc $(FLAGS) -c main.c

graph: main.o algo.o lib_mygraphAlgo.a
	gcc $(FLAGS) -o graph main.o algo.o lib_mygraphAlgo.a

clean:
	rm -f *.o *.a *.so graph