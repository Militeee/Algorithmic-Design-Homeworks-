SRC = src/utils.c src/heap.c src/sorting.c src/vector.c 
all: main.x best_worst.x selection_main.x

main.x:  $(SRC)
	gcc  -O3 -I include $^ main.c -o $@

best_worst.x:	$(SRC)
	gcc  -O3 -I include $^ best_worst.c -o $@

selection_main.x:	$(SRC)
	gcc  -O3 $^ -I include selection_main.c -o $@

clean:
	@rm -rf *~ */*~ *main.x best_worst.x

