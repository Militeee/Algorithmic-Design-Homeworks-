## Homeworks 2

### Matrix multiplication, best parenthesization

You can use the python script
$ input_generator.py [number of matrix multiplications] [starting power] [max ncol and nrow]
to generate the file input.txt, which contains the number (first entry of a row) and the dimensions of the matrix to be multiplied
Next compile with make and launch the file main.x < input.txt
The scripts basically generate argv[1] chains of number argv[2]^i where i goes from 1...argv[1].

