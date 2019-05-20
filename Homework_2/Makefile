SRC = main.c  src/chain_matrix.c src/utils.c src/matrix.c 
all: main.x

main.x:  $(SRC)
	gcc -O3 -I include $^ -o $@

clean:
	@rm -rf *~ */*~ main.x

