#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int size,node, i,x;
    double MPI_Wtime (void);
    double t1, t2;
    int a, b, sum, avg;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);

    t1 = MPI_Wtime();

    a = 0;
    b = 1;
    x = 100000/size;
    if (node < size) {
        for (i=0; i<x; i++)
            a = a + rand(); 
    }

    t2 = MPI_Wtime();

    MPI_Reduce(&a, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (node==0) {
        printf("Node %d  a = %d, Total from all processes %d MPI_Wtime =  %1.6f\n", node, a, sum, t2-t1);
        avg = sum/size;
        printf("The average is %d \n", avg); 
    }
    else
        printf("\nNode %d  a = %d, MPI_Wtime =  %1.6f\n", node, a, t2-t1);

    MPI_Finalize(); 
}