# shell syntax: mpiexec -np BIL_PROSESOR -quiet python3 NAMA_FAIL
# contoh: mpiexec -np 4 -quiet python3 3_pi-calc.py

from random import random, seed
from mpi4py import MPI
from time import time
import math

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

masa = MPI.Wtime()
circle_count = 0
num = 1000000/size

seed(rank + time())
for i in range(int(num)):
    x = random()
    y = random()
    
    if ((x * x) + (y * y)) < 1:
        circle_count += 1

localPi = (4.0 * circle_count) / num

if rank == 0:
    print(f'rank[{rank}] pi = {localPi}')
    
kira = comm.reduce(localPi, op=MPI.SUM, root=0)

if rank == 0:
    pi = float(kira / size)
    formula = round((math.pi - pi), 4)
    
    print(f'''
Computed value of pi on {size} processors is {round(pi, 4)}
====================
Execution time: {round((MPI.Wtime() - masa), 4)} seconds
different between original pi value with computed value: {formula}''')