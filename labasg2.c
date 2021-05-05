#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define SAIZ 100000

int main (int argc, char *argv[]) {
    int tugas, rank, bilangan, punca;
    float kecil[1];
    
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &tugas);

    float timbalterima[SAIZ], timbalhantar[tugas][SAIZ], minglobal[tugas];
    srand(time(0));
    for (int i = 0; i < tugas; i++){
        for (int j = 0; j < SAIZ; j++){
            timbalhantar[i][j] = rand();
        }
    }
    // printf("%f\n", timbalhantar[1][2]);
    punca = 1;
    bilangan = SAIZ;

    MPI_Scatter(timbalhantar, bilangan, MPI_FLOAT,
                timbalterima, bilangan, MPI_FLOAT,
                punca, MPI_COMM_WORLD);
    // printf("[rank %d] menerima %.1f\n", rank, timbalterima[2]);

    kecil[0] = timbalterima[0];
    int kira = sizeof(timbalterima) / sizeof(timbalterima[0]);
    for (int i = 0; i < kira; i++){
        if (timbalterima[i] < kecil[0])
            kecil[0] = timbalterima[i];
    }
    printf("[rank %d] nilai terkecil %.1f\n", rank, kecil[0]);
    MPI_Gather(kecil, 1, MPI_FLOAT, 
                minglobal, tugas, MPI_FLOAT, 
                punca, MPI_COMM_WORLD);
    
    if (rank == 1) {
        kecil[0] = minglobal[0];
        int kiraglobal = sizeof(minglobal) / sizeof(minglobal[0]);
        for (int i = 0; i < tugas; i++){
            if (minglobal[i] < kecil[0])
                kecil[0] = minglobal[i];
        
            printf("[rank %d] nilai global terkecil %.1f\n", rank, kecil[0]);
        }

    }

    MPI_Finalize();
}