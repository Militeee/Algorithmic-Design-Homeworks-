all: main.x

main.x: main.cpp src/dijkstra.cpp src/graph.cpp heap.o utils.o 
	g++ -I include -O3 $^ -o $@

heap.o utils.o : src/heap.c src/utils.c 
	gcc -I include -O3 -c $^ 
clean:
	rm *.o *.x