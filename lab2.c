#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define SAIZ 100000

int terkecil (int pemproses, int rank);

int main (int argc, char *argv[]) {
    int numtask, rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //ambil masa awal untuk mengetahui masa perlaksanaan
    double masaAwal = MPI_Wtime();

    // dapatkan nilai terkecil daripada setiap pemproses
    int local = terkecil(numtask, rank);
    printf("[rank %d] %d\n", rank, local);

    // mengumpulkan nilai terkecil dan dihimpun pada pemproses 1
    int kumpul[SAIZ];
    MPI_Gather(&local, 1, MPI_INT, kumpul, 1, MPI_INT, 1, MPI_COMM_WORLD);

    if (rank == 1) {
        // rank 1 membuat perbandingan daripada nilai dihimpun
        local = kumpul[0];
        for (int i = 0; i < numtask; i++){
            if (kumpul[i] < local)
                local = kumpul[i];
        }
        
        printf("Nilai terkecil: %d\n\n", local);

        double masaAkhir = MPI_Wtime();
        printf("Masa perlaksanaan: %1.4f saat\n", masaAkhir - masaAwal);
    }
    
    MPI_Finalize();
}

int terkecil (int pemproses, int id) {
    // mengagihkan beban per bilangan pemproses
    int adil = SAIZ / pemproses;
    int timbal[adil], mini;

    // menghasilkan nilai rawak pada setiap pemproses
    srand(time(NULL) + id);
    for (int i = 0; i < adil; i++) {
        timbal[i] = rand();
    }

    // mengambil nilai terkecil
    mini = timbal[0];
    for (int i = 0; i < adil; i++) {
        if (timbal[i] < mini)
            mini = timbal[i];
    }

    return mini;
}