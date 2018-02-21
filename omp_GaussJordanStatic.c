/* File:
*        omp_GaussJordan1.c
*
* Purpose:
*                               y=A*x
*        Solves a linear system of equations using Gauss-Jordan
*        elimination. Implementation uses OpenMP to parallelize
*        the algorithm. 
*
*  Input:
*        n: matrix and vector dimension
*        A: n by n matrix
*        y: n by 1 vector
*
*
*  Output:
*        x: n by 1 solution vector
*
*  Note:
*        - TODO: 
*
*  Compile:
*        gcc -g -Wall -o 
*  Usage:
*
*
*  Students:
*        Breno Bahia (ID: 1449808)        
*        Derek Shultz (ID: XXXXXXX)
*/

// Preprocessing directives

// Include headers
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "Lab3IO.h"
#include "timer.h"


// Begin main
int main(int argc, char* argv[]){
    int i, j, k, size;
    int thread_count;
    double** Au;
    double* X;
    int* index;
    double temp;
    double start, end;

    // Safe-guard for input from commandline
    if (argc<=1){   
        printf("Insufficient input!\n");
        return 1;
    }
    thread_count=strtol(argv[1], NULL, 10);

    /*Calculate the solution by serial code*/
    Lab3LoadInput(&Au, &size);
    X = CreateVec(size);
    index = malloc(size * sizeof(int));
    for (i = 0; i < size; ++i){
        index[i] = i;
   }
    
    GET_TIME(start);
    
    // If n=1, solution is straightforward
    if (size == 1)
        X[0] = Au[0][1] / Au[0][0];
    else{
    
         // Begin parallel portion
         #pragma omp parallel num_threads(thread_count) \
         default(none) shared(Au, index, size) \
         private(i, j, k,  temp) 
    
        // Begin Gauss-Jordan elimination with partial pivoting
        for (k = 0; k < size - 1; ++k){
        
            // Pivoting
            /*
               This cannot be done in parallel.
               One idea would be to try to generalize some
               algorithm like the bubble sort to perform
               pivoting
            */
            #pragma omp single 
            {
               temp = 0;
               for (i = k, j = 0; i < size; ++i)
                  // Find max abs value in k-th column
                   if (temp < Au[index[i]][k] * Au[index[i]][k]){
                       temp = Au[index[i]][k] * Au[index[i]][k];
                       j = i;
                   }
                  // Swap rows
                  if (j != k){
                      i = index[j];
                      index[j] = index[k];
                      index[k] = i;
                  }
            } // Implict Barrier

            // Gaussian elimination
            #pragma omp for schedule(static)
            for (i = k + 1; i < size; ++i){
                temp = Au[index[i]][k] / Au[index[k]][k];
                for (j = k; j < size + 1; ++j){
                    Au[index[i]][j] -= Au[index[k]][j] * temp;
                }
            }       
        }
      
      GET_TIME(end);
      printf("Elapsed time %f\n\n", end-start);       
        
            // Jordan elimination
             #pragma omp for schedule(static)
            for (k = size - 1; k > 0; --k){
                for (i = k - 1; i >= 0; --i ){
                   temp = Au[index[i]][k] / Au[index[k]][k];
                   Au[index[i]][k] -= temp * Au[index[k]][k];
                   Au[index[i]][size] -= temp * Au[index[k]][size];
               } 
            }
      GET_TIME(end);
      printf("Elapsed time %f\n\n", end-start);       


     // Solution
     #pragma omp for schedule(static)   
     for (k=0; k< size; ++k){
         X[k] = Au[index[k]][size] / Au[index[k]][k];     
     }

} // End else
   
    GET_TIME(end);

    Lab3SaveOutput(X, size, end - start); 
    printf("Elapsed time %f\n\n", end-start); 

    DestroyVec(X);
    DestroyMat(Au, size);
    free(index);

    return 0;   
}
