#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "chain_matrix.h"
#include "utils.h"
#include "matrix.h"



int main(){
    int mat_num;
    struct timespec b_time, e_time;
    // store S and M
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
        
        //allocate space for the matrices, fill them
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
        // non optimal parenthesis
        multiply_rec(result1, tensor1, final_mtrx[1], dim_array,0, mat_num-1,1);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Serial multiplication\t%lf\n",get_execution_time(b_time, e_time));
        
        clock_gettime(CLOCK_REALTIME, &b_time);
        // optmila parenthesis
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


