import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df_mp = pd.read_csv('resultados.csv',sep=';')
df_mpi = pd.read_csv('resultados_mpi.csv',sep=';')

labels = [list(df_mp['N'].unique())]
threads = list(df_mp['threads'])
tempos_mp = list(df_mp['Tempo'])
threads_mpi = list(df_mp['threads'])
tempos_mpi = list(df_mpi['Tempo'])

NUM_THREADS = 2

t1 = []
t2 = []
t3 = []
t4 = []
for i in range(0,len(tempos_mp),NUM_THREADS):
    t1.append(tempos_mp[i])
for i in range(1,len(tempos_mp),NUM_THREADS):
    t2.append(tempos_mp[i])

for i in range(0,len(tempos_mpi),NUM_THREADS):
    t3.append(tempos_mpi[i])
for i in range(1,len(tempos_mpi),NUM_THREADS):
    t4.append(tempos_mpi[i])



x = np.arange(len(labels)) 
width = 0.20  

fig, ax = plt.subplots()
rects1 = ax.bar(x + width-0.2, t1, width, label='OpenMP - 1 thread')
rects2 = ax.bar(x + width, t2, width, label='OpenMP - 2 threads')
rects3 = ax.bar(x + width+0.4, t3, width, label='Open MPI - 1 processo')
rects4 = ax.bar(x + width+0.6, t4, width, label='Open MPI - 2 processos')

ax.bar_label(rects1,padding=3)
ax.bar_label(rects2,padding=3)
ax.bar_label(rects3,padding=3)
ax.bar_label(rects4,padding=3)
ax.set_ylabel('Tempo de execução (s)')
ax.set_title('Crivo de Eratostenes para N=1.000.000.000')
#ax.set_xticks(x)
#ax.set_xticklabels(labels)
ax.set_ylim(ymin=0,ymax=40)
ax.legend()
ax.tick_params(bottom=False,top=False,labelbottom=False,axis='x')
  
fig.tight_layout()
plt.savefig('resultados_tempo.png')