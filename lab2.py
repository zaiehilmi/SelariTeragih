from mpi4py import MPI
import random
from datetime import datetime

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
saiz = comm.Get_size()

masaAwal = MPI.Wtime()
adil = int(100000 / saiz)
timbal = []

random.seed(datetime.now())

for i in range(adil):
    n = random.randint(40, 100050)
    timbal.append(n)

lokal = min(timbal)
print(f'Terkecil dalam rank {rank}: {lokal}')

glob = comm.gather(lokal, root=0)

if rank == 0:
    print(f'Paling kecil antara semua: {min(glob)}')

    masaAkhir = MPI.Wtime()
    print(f'Masa Perlaksanaan: {masaAkhir - masaAwal}')