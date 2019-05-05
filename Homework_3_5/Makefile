SRC = utils.c heap.c sorting.c vector.c 
all: main.x best_worst.x selection_main.x

main.x:  $(SRC)
	gcc -ggdb -O3 $^ main.c -o $@

best_worst.x:	$(SRC)
	gcc -ggdb -O3 $^ best_worst.c -o $@

selection_main.x:	$(SRC)
	gcc -ggdb -O3 $^ selection_main.c -o $@

clean:
	@rm -rf *~ */*~ main.x

