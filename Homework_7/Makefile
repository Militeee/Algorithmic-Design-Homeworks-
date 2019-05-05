all: main.x

main.x: main.cpp dijkstra.cpp graph.cpp heap.o utils.o
	g++ $^ -o $@

heap.o utils.o: heap.c utils.c
	gcc $^ -o $@