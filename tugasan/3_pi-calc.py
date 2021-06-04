#shell syntax: mpiexec -np BIL_PROSESOR -quiet python3 NAMA_FAIL
#contoh: mpiexec -np 4 -quiet python3 3_pi-calc.py

from random import random, seed
from mpi4py import MPI
from time import time

masa = time()

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

circle_count = 0
num = 10000/size

seed(rank)
for i in range(int(num)):
    x = random()
    y = random()
    if ((x * x) + (y * y)) < 1:
        circle_count += 1

mypi = (4.0 * circle_count) / num
if rank == 0:
   print(f"rank[{rank}] mypi = {mypi}")
   
kira = comm.reduce(mypi, op=MPI.SUM, root=0)

if rank==0:
    pi = float((1.0 / size) * kira)
    
    print(f"Computed value of pi on {size} processors is {pi}")
    print(f"Using {int(size * num)} samples.")
    print(f'====================\nExecution time {round((time() - masa), 4)} seconds')