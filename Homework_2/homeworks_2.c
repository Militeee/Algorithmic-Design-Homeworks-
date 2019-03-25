#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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


// print float or integer matrices

void print_matrix(int ** m, int size)
{
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_matrix_2(float ** m, int size, int size2)
{
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size2; j++)
        {
            printf("%f ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// recursive call for multiplying using the right parenthesis

void multiply_rec(float** result, float*** tensor, int **S, int *dim_num,int i, int j, int naive)
{
	if(i==j){

        copy_matrix(tensor[i], result,dim_num[i], dim_num[i+1] );
    }
    else{
        int k;
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




int main(){
    int mat_num;
    struct timespec b_time, e_time;
    int*** final_mtrx = (int***) malloc(sizeof(int**) * 2);
    int k;
    while(scanf("%d", &mat_num) == 1){
        
        // Scan the input for the number of matrices, allocate the memory
        // and construct the vector with dimensions
        int* dim_array = malloc( (mat_num+1) * sizeof(int)); 
        if(dim_array == NULL)
        {
            return -3;
        }
        for (int i = 0; i <= mat_num; i++){
            int err = scanf("%d", &dim_array[i]);  
        }

        // calculate optimal parenthetization
        //dim_array[mat_num] = dim_array[0];
        clock_gettime(CLOCK_REALTIME, &b_time);
        matrixChain(final_mtrx,dim_array, mat_num );
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Dimension %d\t%lf\n",mat_num ,get_execution_time(b_time, e_time));
        //print_matrix(final_mtrx[0], mat_num );
        //print_matrix(final_mtrx[1], mat_num  );
        print_parenthesis(final_mtrx[1], 0, mat_num - 1 );
        printf("\n");
        printf("Maximum number of multiplication = %d \n", final_mtrx[0][0][mat_num-1]);
        
        //allocate space for the matrice, fill them
        float***  tensor1 = (float***) malloc(sizeof(float**) * mat_num);
        float***  tensor2 = (float***) malloc(sizeof(float**) * mat_num);
        for(int i = 0; i < mat_num; i++){
            tensor1[i] = allocate_matrix_f(dim_array[i], dim_array[i+1]);
            tensor2[i] = allocate_matrix_f(dim_array[i], dim_array[i+1]);
            randomly_fill_matrix(tensor1[i],dim_array[i], dim_array[i+1]);
            copy_matrix(tensor1[i],tensor2[i],dim_array[i], dim_array[i+1]);
        }

        //allocate space for the results
        float** result1 = allocate_matrix_f(dim_array[0], dim_array[mat_num]);
        float** result2 = allocate_matrix_f(dim_array[0], dim_array[mat_num]);

        clock_gettime(CLOCK_REALTIME, &b_time);
        multiply_rec(result1, tensor1, final_mtrx[1], dim_array,0, mat_num-1,1);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Serial multiplication\t%lf\n",get_execution_time(b_time, e_time));
        
        clock_gettime(CLOCK_REALTIME, &b_time);
        multiply_rec(result2, tensor2, final_mtrx[1], dim_array,0, mat_num-1,0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Optimal multiplication\t%lf\n",get_execution_time(b_time, e_time));
        
        //print_matrix_2(result2, dim_array[0] ,dim_array[mat_num] );
        //print_matrix_2(result1, dim_array[0], dim_array[mat_num]);
        //printf("%d \n",same_matrix(result2,dim_array[0], dim_array[mat_num],
            //result1,dim_array[0], dim_array[mat_num]));


        for(int i = 0; i < mat_num; i++){
            deallocate_matrix_f(tensor2[i],dim_array[i]);
        }   
        for(int i = 0; i < mat_num; i++){
            deallocate_matrix_f(tensor1[i],dim_array[i]);
        }
        deallocate_matrix(final_mtrx[0], mat_num  );
        deallocate_matrix(final_mtrx[1], mat_num  );
        deallocate_matrix_f(result1,dim_array[0]);
        deallocate_matrix_f(result2,dim_array[0]);
        free(tensor1);
        free(tensor2);
        free(dim_array);
        printf("\n \n");
    }
    free(final_mtrx);
}


