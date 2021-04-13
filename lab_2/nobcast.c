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

    a = 20000 * 30000;      //create some computation
    t1 = MPI_Wtime();
    x = 1000000000 / size;  //ada 1 juta load dibahagi dgn size

    if(node < size){
        for (i = 0; i < x; i++) //loop ni utk distribute fairly kerja untuk beban yg diberikan
            a;      
    }

    t2 = MPI_Wtime();
    printf("Node %d a = %d MPI_Wtime = %1.6f\n", node, a, t2 - t1);
    MPI_Finalize();
}

// is there any communication happening in this code?
// no because all invoked processor is just reading and running the code simultaneously w/o any communication
// they assigned with the given chunk. <tak call bcast, mpi_send, mpi_recv>
// sama macam deep learning, average value of a number