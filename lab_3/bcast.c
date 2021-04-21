#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv){
    int size, node, i, x;
    double MPI_Wtime(void);     //utk dptkan masa 
    // double t1, t2;
    // int a, b;
    char msj[20];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);

    if(node == 0){
        char msj[20] = "ohaiyo";
        printf("%s from node %d\n", msj, node);
    }

    MPI_Bcast(&msj, 6, MPI_CHAR, 0, MPI_COMM_WORLD);   // communication started
    MPI_Barrier(MPI_COMM_WORLD);

    // x = 1000000000 / size;

    // if(node < size){
    //     for (i = 0; i < x; i++) //loop ni utk distribute fairly kerja untuk beban yg diberikan
    //         a;      
    // }

    // t2 = MPI_Wtime();
    printf("Node %d mesej = %s\n", node, msj);
    MPI_Finalize();
}

// bila perlukan communication?
// setiap processor akan lakukan tugasan berbeza (compute, check) dan akan send..
// kepada satu sama lain 