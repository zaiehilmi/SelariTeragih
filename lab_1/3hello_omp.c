// cara compile: 
// gcc -fopenmp <nama fail>.c -o <output>
// cara tukar bilangan thread: 
// export OMP_NUM_THREADS=bil thread

#include <omp.h>    //threads/shared memory
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int nthreads, tid;
    
    // Fork a team of threads giving them their own copies of variables
    #pragma omp parallel private(nthreads, tid)
    {
        //mendapatkan thread id
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        //hanya master thread akan display
        if(tid == 0){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    } //semua thread akan join master dan keluar (sync)
}