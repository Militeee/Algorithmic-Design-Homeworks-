SRC = main.c utils.c heap.c 
all: main.x

main.x:  $(SRC)
	gcc -O3 $^ -o $@

clean:
	@rm -rf *~ */*~ main.x

