from mpi4py import MPI
import numpy as np
from numpy.random import seed
from numpy.random import randint
from datetime import datetime

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
seed(int(datetime.timestamp(datetime.now()))+rank)
sendbuf = np.zeros(10, dtype='i') + rank
sendbuf = randint(0, 100, 10)
sendbuf = sendbuf.astype('i')
recvbuf = None
if rank == 0:
    recvbuf = np.empty([size, 10], dtype='i')
comm.Gather(sendbuf, recvbuf, root=0)
if rank==0:
    print(recvbuf)

