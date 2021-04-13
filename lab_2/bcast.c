#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    int size, node, i, x;
    double MPI_Wtime(void);     //utk dptkan masa 
    double t1, t2;
    int a, b;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);

    if(node == 0){
        a = 20000 * 30000;  // computation
        printf("I am node %d and a is %d \n", node, a);
    }

    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);   // communication started
    MPI_Barrier(MPI_COMM_WORLD);

    t1 = MPI_Wtime();

    x = 1000000000 / size;

    if(node < size){
        for (i = 0; i < x; i++) //loop ni utk distribute fairly kerja untuk beban yg diberikan
            a;      
    }

    t2 = MPI_Wtime();
    printf("Node %d a = %d MPI_Wtime = %1.6f\n", node, a, t2 - t1);
    MPI_Finalize();
}

// bila perlukan communication?
// setiap processor akan lakukan tugasan berbeza (compute, check) dan akan send..
// kepada satu sama lain 