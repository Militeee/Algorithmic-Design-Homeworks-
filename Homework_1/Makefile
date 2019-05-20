SRC = src/improved_strassen.c main.c src/matrix.c src/strassen.c

all: main.x

main.x:  $(SRC)
	gcc -O3 -I include $^ -o $@

clean:
	@rm -rf *~ */*~ main.x

