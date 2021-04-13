#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    int numtasks, rank, dest, source, rc, count, tag = 1;
    char inmsg, outmsg = 'x';
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank % 2 == 0) {
        dest = rank + 1;
        source = rank + 1; 
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
    }
    else {
        dest = rank - 1;
        source = rank - 1; 
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }

    MPI_Get_count(&status, MPI_CHAR, &count);

    printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, status.MPI_SOURCE, status.MPI_TAG);

    MPI_Finalize();
}