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
int*** matrixChain(int* P, size_t n){
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
    int*** res = (int*** ) malloc(sizeof(int** ) * 2);
    res[0] = m;
    res[1] = s;
    return res;
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
            printf("%fl ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void get_right_order(int* array,int** S,int i, int j , int* idx)
{
    if(i == j){
        
        return;
        
        
    }
    else{
        printf("%d %d\t", i,j );
        int k = S[i][j];
        array[*idx] = i;
        *idx-=1;
        get_right_order(array,S,i,k,idx);
        get_right_order(array,S,k + 1,j,idx);
        
    }
}

int main(){
    int mat_num;
    struct timespec b_time, e_time;
    int*** final_mtrx;
    int k;
    while(scanf("%d", &mat_num) == 1){
        
        // Scan the input for the number of matrices, allocate the memory
        // and construct the vector with dimensions
        int* dim_array = malloc( (mat_num+1) * sizeof(int)); 
        if(dim_array == NULL)
        {
            return -3;
        }
        for (int i = 0; i < mat_num; i++){
            scanf("%d", &dim_array[i]);  
        }


        dim_array[mat_num] = dim_array[0];
        clock_gettime(CLOCK_REALTIME, &b_time);
        final_mtrx = matrixChain(dim_array, mat_num );
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Dimension %d\t%lf\n",mat_num ,get_execution_time(b_time, e_time));
        print_matrix(final_mtrx[0], mat_num );
        print_matrix(final_mtrx[1], mat_num  );
        print_parenthesis(final_mtrx[1], 0, mat_num - 1 );
        printf("\n");
        printf("Maximum number of multiplication = %d \n", final_mtrx[0][0][mat_num-1]);
        
       
        float***  tensor1 = (float***) malloc(sizeof(float**) * mat_num);
        float***  tensor2 = (float***) malloc((float**) * mat_num);
        for(int i = 0; i < mat_num; i++){
            tensor1[i] = allocate_matrix_f(dim_array[i], dim_array[i+1]);
            tensor2[i] = allocate_matrix_f(dim_array[i], dim_array[i+1]);
            randomly_fill_matrix(tensor1[i],dim_array[i], dim_array[i+1]);
            copy_matrix(tensor1[i],tensor2[i],dim_array[i], dim_array[i+1])
        }
        float*** result1 = (float***) malloc(sizeof(float**) * mat_num); 
        float*** result2 = (float***) malloc(sizeof(float**) * mat_num); 

        for(int i = 0; i < mat_num-1; i++){
            result1[i] = allocate_matrix_f(dim_array[0], dim_array[i+2]);
            result2[i] = allocate_matrix_f(dim_array[0], dim_array[i+2]);
        }
        
        print_array(dim_array,mat_num+1);
        
        clock_gettime(CLOCK_REALTIME, &b_time);
        naive_matrix_mult(result1[0],tensor1[0], tensor1[1],dim_array[0], 
            dim_array[1],dim_array[1], dim_array[2]);
        for(int i = 1; i < mat_num-1; i++){
            naive_matrix_mult(result1[i],result1[i-1], tensor1[i+1],dim_array[0], 
            dim_array[i+1],dim_array[i+1], dim_array[i+2]);
        }
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Sequential multiplication\t%lf\n",get_execution_time(b_time, e_time));
        int* right_order = malloc( mat_num * sizeof(int)); 
        int* idx;
        *idx=mat_num-1;
        get_right_order(right_order, final_mtrx[1], 0, mat_num - 1,idx);
        print_array(right_order,mat_num);
         
        clock_gettime(CLOCK_REALTIME, &b_time);
        for(int i = 0; i < mat_num-1; i++){
            naive_matrix_mult(tensor2[i+1],tensor2[i], tensor2[i+1],dim_array[i], 
            dim_array[i+1],dim_array[i+1], dim_array[i+2]);
        }
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Optimal multiplication\t%lf\n",get_execution_time(b_time, e_time));
        

        for(int i = 0; i < mat_num; i++){
            deallocate_matrix(tensor1[i],dim_array[i]);
            deallocate_matrix(tensor2[i],dim_array[i]);
        }
        free(tensor2);

        for(int i = 0; i < mat_num; i++){
            deallocate_matrix_f(tensor1[i],dim_array[i]);
            deallocate_matrix(tensor2[i],dim_array[i]);
        }
        for(int i = 0; i < mat_num-1; i++){
            deallocate_matrix_f(result1[i],dim_array[0]);
            deallocate_matrix(result2[i],dim_array[0]);
        }
        
        deallocate_matrix(final_mtrx[0], mat_num  );
        deallocate_matrix(final_mtrx[1], mat_num -1 );
        free(result1);
        free(tensor1);
        free(right_order);
        free(final_mtrx);
        free(dim_array);
    }
}


