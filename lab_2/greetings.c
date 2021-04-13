#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char* argv[]){
    int my_rank, proses, sumber, destinasi, tag = 0;
    char msj[100];
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);    // bilangan pemproses yg terlibat
    MPI_Comm_size(MPI_COMM_WORLD, &proses);     // bilangan proses

    if(my_rank != proses -1){ // selain daripada rank 0 akan hantar ke rank = 0
        // cipta mesej
        sprintf(msj, "Greeting from process %d", my_rank);
        destinasi = proses -1;

        //gunakan strlen+1 supaya '\0' boleh dihantar
        MPI_Send(msj, strlen(msj)+1, MPI_CHAR, destinasi, tag, MPI_COMM_WORLD);
        // printf("Test %s\n", msj);
    } else{ //yang rank 0 akan paparkan
        for(sumber = 0; sumber < proses-1; sumber++){
            MPI_Recv(msj, 100, MPI_CHAR, sumber, tag, MPI_COMM_WORLD, &status);
            printf("Test %s\n", msj);
        }
    }
    MPI_Finalize();
}

// dia ikut sequence sbb kita guna loop
// how to make any number of processor can be run?