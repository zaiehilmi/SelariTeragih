#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    int numtasks, rank, dest, source, rc, count, tag = 1;
    int bahagi = 0;
    // char x[2], y[2];
    int x, y;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    bahagi = numtasks / 2;

    if(rank < bahagi) {
        // char y[2] = "9";
        int y = 9;
        dest = rank + bahagi;
        source = rank + bahagi; 
        MPI_Send(&y, 5, MPI_INT, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&x, 5, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        printf("Node %d terima mesej = %d daripada node %d\n", rank, x, status.MPI_SOURCE);
    }
    else {
        // char x[2] = "10";
        int x = 10;
        dest = rank - bahagi;
        source = rank - bahagi; 
        MPI_Send(&x, 5, MPI_INT, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&y, 5, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        printf("Node %d terima mesej = %d daripada node %d\n", rank, y, status.MPI_SOURCE);
    }

    // MPI_Get_count(&status, MPI_INT, &count);

    // printf("Task %d: Received %d digit(s) from task %d with tag %d \n", rank, count, status.MPI_SOURCE, status.MPI_TAG);
    // printf("Node %d terima mesej = %s daripada node %d\n", rank, x, status.MPI_SOURCE);
    MPI_Finalize();
}