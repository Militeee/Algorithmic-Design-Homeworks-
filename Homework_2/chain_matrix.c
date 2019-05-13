#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "utils.h"
#include "matrix.h"
#define INFINITY INT_MAX



// fiils the m and s matrix with the optimal subsequence multiplication ost

void matrixChainAux(int* P, int** m, int** s, size_t i, size_t j){
    m[i][j] = INFINITY;
    for(size_t k=i; k < j; k++){
        int q = m[i][k] + m[k+1][j] + P[i]*P[k+1]*P[j+1];
        if (q < m[i][j]){
            m[i][j] = q;
            s[i][j] = k;
            
        }
    }
}

/*
    Compute the matrix m and s iteratively
    returns a tensor with output[0] = m and output[1] = s

*/
void matrixChain(int*** res,int* P, size_t n){
    int** m = allocate_matrix(n,n);
    int** s = allocate_matrix(n,n);
    for(size_t i = 0; i < n  ; i++){
        m[i][i] = 0;
    }
    for(size_t l = 1; l < n; l++){
        for (size_t i = 0; i < n-l; i++){
            size_t j = i + l;
            matrixChainAux(P,m,s,i,j);
        }
    }
    res[0] = m;
    res[1] = s;
    return;
}


// prints the ordered sequence for multiplication

void print_parenthesis(int** S,int i, int j){
    if (i == j)
        printf("A%d",i);
    else{
        printf("(");
        int k = S[i][j];
        print_parenthesis(S,i,k);
        print_parenthesis(S,k + 1,j);
        printf(")");
    }
}



// recursive call for multiplying using the right parenthesis

void multiply_rec(float** result, float*** tensor, int **S, int *dim_num,int i, int j, int naive)
{
	if(i==j){

        copy_matrix(tensor[i], result,dim_num[i], dim_num[i+1] );
    }
    else{
        int k;
        // way to choose if use the best parenthesization or start from the middle
        if(naive)
            k = (i+j)/2;
        else
            k = S[i][j];
        float** A1 = allocate_matrix_f(dim_num[i], dim_num[k+1]);
        float** A2 = allocate_matrix_f(dim_num[k+1], dim_num[j+1]);
        multiply_rec(A1, tensor,S,dim_num,i,k,naive);
        multiply_rec(A2, tensor,S,dim_num,k + 1,j,naive);
        naive_matrix_mult(result,A1,A2, dim_num[i],
                        dim_num[k+1], dim_num[k+1], dim_num[j+1]);
        deallocate_matrix_f(A2,dim_num[k+1]);
        deallocate_matrix_f(A1,dim_num[i]);
    }
   
}

