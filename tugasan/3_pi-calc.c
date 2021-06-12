#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define BEBAN 10000

int main(int argc, char* argv[]) {
    int saiz, rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &saiz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double mula = MPI_Wtime();
    int circle_count = 0;
    int num = BEBAN / saiz;

    srand(time(NULL) + rank);
    for (int i = 0; i < num; i++) {
        double x = (float)rand() / RAND_MAX;
        double y = (float)rand() / RAND_MAX;

        if (((x * x) + (y * y)) < 1)
            circle_count++;
    }

    double localPi = (4.0 * circle_count) / num;

    if (rank == 0)
        printf("rank[%d] local PI = %.4f\n", rank, localPi);

    double kira[1];
    MPI_Reduce(&localPi, kira, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = kira[0] / saiz;
        
        printf("Computed value of pi on %d processors is %.4f\n", saiz, pi);
        printf("===================\n");
        printf("Execution time %.4f\n", (MPI_Wtime() - mula));
    }

    MPI_Finalize();
}