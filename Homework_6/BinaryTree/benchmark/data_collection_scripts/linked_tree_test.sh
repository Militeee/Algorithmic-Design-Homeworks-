N_SEQ="10000 20000 40000 60000 80000 100000 120000 140000 160000"
BNAME=bench_ll.x
FIRST=1
LAST=10

echo "N;LINKED_LIST_TREE"
for i in $(seq $FIRST $LAST); do
	for i in $N_SEQ; do       
       		N=$i
		./$BNAME $N
	done
done
exit
