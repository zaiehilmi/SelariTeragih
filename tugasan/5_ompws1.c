#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 10
#define N 100

int main( int argc, char *argv[])
{
    int nthreads, tid, i, chunk;
    float a[N], b[N], c[N];
    double omp_get_wtime(void);
    double masa;

    masa = omp_get_wtime();
    /* Some initializations */
    for (i=0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;

    #pragma omp parallel shared (a,b,c, nthreads, chunk) private (i,tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

        printf("thread %d starting ...\n", tid);

        #pragma omp for schedule (static, chunk)
        for (i = 0; i < N; i++) {
            c[i] = a [i] + b[i];
            printf("Thread %d: c[%d] = %f\n", tid, i, c[i]);
        }

    } /* end of parallel section 1 */

    void omp_set_num_threads(int num_threads);
    omp_set_num_threads(2);

    #pragma omp parallel shared (a,b,c, nthreads, chunk) private (i,tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

        printf("thread %d starting ...\n", tid);

        #pragma omp for schedule (static, chunk)
        for (i = 0; i < N; i++) {
            c[i] = a [i] + b[i];
            printf("Thread %d: c[%d] = %f\n", tid, i, c[i]);
        }

    } /* end of parallel section 2 */

    void omp_set_num_threads(int num_threads);
    omp_set_num_threads(3);

    #pragma omp parallel shared (a,b,c, nthreads, chunk) private (i,tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

        printf("thread %d starting ...\n", tid);

        #pragma omp for schedule (static, chunk)
        for (i = 0; i < N; i++) {
            c[i] = a [i] + b[i];
            printf("Thread %d: c[%d] = %f\n", tid, i, c[i]);
        }

    } /* end of parallel section 3 */

    masa = omp_get_wtime() - masa;

    printf("Masa yang diperlukan untuk menyelesaikan tugasan = %1.6f\n", masa);

}