SRC = improved_strassen.c main.c matrix.c strassen.c

all: strassen.x

strassen.x:  $(SRC)
	gcc -O3 $^ -o $@

clean:
	@rm -rf *~ */*~ strassen.x

