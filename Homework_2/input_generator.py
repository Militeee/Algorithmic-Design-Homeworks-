import sys
import random

#script to create input file: first argumetn is the number of trials, second the starting power
# of matrices, the third is the maximum number of cols and rows in a matrix
# ex. $ python input_generator 10 2 100 // stops at 2^10

if len(sys.argv) < 4:
    print("Not enough arguments")
else: 
    with open("input.txt",'w') as f:
        for r in range(1,int(sys.argv[1])+1):
            rand = [str(random.randint(1,int(sys.argv[3]))) for x in range(int(sys.argv[2])**r)]
            print(int(sys.argv[2])** r,' '.join(rand), file = f)


