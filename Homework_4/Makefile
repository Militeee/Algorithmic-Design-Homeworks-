SRC = main.c src/utils.c src/heap.c 
all: main.x

main.x:  $(SRC)
	gcc -O3 -I include $^ -o $@

clean:
	@rm -rf *~ */*~ main.x

