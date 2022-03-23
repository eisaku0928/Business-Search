all: map1 map2

map1: main.o data.o tree.o utils.o
	gcc -Wall -o map1 main.o data.o tree.o utils.o -g -lm

map2: main2.o data2.o tree2.o utils2.o
	gcc -Wall -o map2 main2.o data2.o tree2.o utils2.o -g -lm

main.o: main.c
	gcc -Wall -c main.c -g

main2.o: main2.c
	gcc -Wall -c main2.c -g

data.o: data.c data.h
	gcc -Wall -c data.c -g

data2.o: data2.c data2.h
	gcc -Wall -c data2.c -g

tree.o: tree.c tree.h
	gcc -Wall -c tree.c -g

tree2.o: tree2.c tree2.h
	gcc -Wall -c tree2.c -g

utils.o: utils.c utils.h
	gcc -Wall -c utils.c -g

utils2.o: utils2.c utils2.h
	gcc -Wall -c utils2.c -g
