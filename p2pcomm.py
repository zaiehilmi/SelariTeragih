from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

bahagi = comm.Get_size() / 2

if rank < bahagi:
    data = {'a': 7, 'b': 3.14}
    comm.send(data, dest=(rank + bahagi), tag=11)

    dpt = comm.recv(source=(rank + bahagi), tag=11)
    print(f'dapat mesej: {dpt}')

else:
    data = 'bruh'
    dpt = comm.recv(source=(rank - bahagi), tag=11)
    print(f'dapat mesej: {dpt}')
    comm.send(data, dest=(rank - bahagi), tag=11)



# print(f'rank: {rank} data: {data}')