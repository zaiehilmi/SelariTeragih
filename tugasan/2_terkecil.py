# shell syntax: mpiexec -np BIL_PROSESOR -quiet python3 NAMA_FAIL
# contoh: mpiexec -np 4 -quiet python3 2_terkecil.py

from mpi4py import MPI
import random
import time

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
saiz = comm.Get_size()

masa = MPI.Wtime()
adil = int(100000 / saiz)
timbal = []

random.seed(rank + int(round(time.time() * 1000)))

for i in range(adil):
    n = random.randint(40, 100050)
    timbal.append(n)

lokal = min(timbal)
print(f'[rank {rank}]: {lokal}')

glob = comm.gather(lokal, root=0)

if rank == 0:
    print(f'Paling kecil antara semua: {min(glob)}')

    masa = round((MPI.Wtime() - masa), 4)
    print(f'Masa Perlaksanaan: {masa} saat')