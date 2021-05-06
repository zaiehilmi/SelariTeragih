#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define SAIZ 100000

float terkecil (int x, int y);

int main (int argc, char *argv[]) {
    int tugas, rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &tugas);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    float local = terkecil(tugas, rank);
    printf("[%d] %.1f\n", rank, local);
    //=======================================================OK
    float *kumpul = NULL;
    kumpul = (float *)malloc(tugas * 100 * sizeof(float));

    
    MPI_Gather(&local, 100, MPI_FLOAT, kumpul, 100, MPI_FLOAT, 1, MPI_COMM_WORLD);

    if (rank == 1) {
        for (int i = 0; i < tugas; i++)
            printf("[]%.1f\n", kumpul[i]);
    }

    MPI_Finalize();
}

float terkecil (int pemproses, int id) {
    int adil = SAIZ / pemproses;
    float timbal[adil], mini;

    srand(time(NULL) + id);
    for (int i = 0; i < adil; i++) {
        timbal[i] = rand();
    }

    mini = timbal[0];

    for (int i = 0; i < adil; i++) {
        if (timbal[i] < mini)
            mini = timbal[i];
    }

    return mini;
}
