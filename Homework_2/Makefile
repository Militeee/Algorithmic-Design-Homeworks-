SRC = main.c  chain_matrix.c utils.c matrix.c 
all: main.x

main.x:  $(SRC)
	gcc -O3 $^ -o $@

clean:
	@rm -rf *~ */*~ main.x

