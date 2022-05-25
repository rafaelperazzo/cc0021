from mpi4py import MPI
import numpy as np
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
data = None
if rank == 0:
    data = np.arange(100, dtype='i')

recvbuf = np.empty(50, dtype='i')
comm.Scatter(data, recvbuf, root=0)
print(recvbuf)