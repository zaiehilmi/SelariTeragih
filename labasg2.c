#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define KIRA 100000

int main (int argc, char *argv[]) {
    int saiz, rank;
    int bilhantar, bilterima, punca;
    float kecil[1], besar;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &saiz);

    float itemhantar[saiz][KIRA], itemterima[KIRA];


    for (int i = 0; i < saiz; i++) {
        for (int j = 0; j < KIRA; j++) {
            itemhantar[i][j] = rand();
        }
    } 
    // int o = itemhantar[0][0];
    // printf("rank[%d] hantar: %d\n", rank, o);
    punca = 0;
    bilhantar = KIRA;
    bilterima = KIRA;
    MPI_Scatter(itemhantar, bilhantar, MPI_FLOAT, 
                itemterima, bilterima, MPI_FLOAT, 
                punca, MPI_COMM_WORLD);
    
    // printf("rank [%d]\n", rank);
    kecil[0] = itemterima[0];

    int _size = sizeof(itemterima)/sizeof(itemterima[0]);

    for (int k = 0; k < _size; k++) {
        if (itemterima[k] < kecil[0]) {
            itemterima[0] = itemterima[k];
        }
    }
    printf("rank[%d] terkecil: %.1f\n", rank, itemterima[0]);

    MPI_Gather(itemterima, bilhantar, MPI_FLOAT, 
                itemhantar, bilhantar, MPI_FLOAT, 
                punca, MPI_COMM_WORLD);
    if (rank == 0){
        float *_kecil = itemhantar[0];
        for (int k = 0; k < _size; k++) {
            printf("index %d: %f", k, *itemhantar[k]);
            // if (itemhantar[0] < _kecil) {
            //     _kecil = itemhantar[0];
            // }
        }
        printf("terkecil dalam dunia ini ialah ==== %.1f\n", *_kecil);
    }
        

    MPI_Finalize();
}