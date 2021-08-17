import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from matplotlib.ticker import ScalarFormatter

def notacao_cientifica(numero):
    nc = "{:.0e}".format(numero)
    return(nc)

df = pd.read_csv('resultados.csv',sep=';')
df['N'] = df['N'].map(lambda x: notacao_cientifica(x)).astype(str)
labels = list(df['N'].unique())
threads = list(df['threads'])
tempos = list(df['speedup'])

NUM_THREADS = 2

t1 = []
t2 = []
t3 = []
t4 = []
for i in range(0,len(tempos),NUM_THREADS):
    t1.append(tempos[i])
for i in range(1,len(tempos),NUM_THREADS):
    t2.append(tempos[i])
'''
for i in range(2,len(tempos),NUM_THREADS):
    t3.append(tempos[i])
for i in range(3,len(tempos),NUM_THREADS):
    t4.append(tempos[i])
'''

x = np.arange(len(labels)) 
#x = np.array(labels)

width = 0.20  

fig, ax = plt.subplots()

rects1 = ax.bar(x + width-0.2, t1, width, label='1 thread')
rects2 = ax.bar(x + width, t2, width, label='2 threads')
#rects3 = ax.bar(x + width+0.2, t3, width, label='3 threads')
#rects4 = ax.bar(x + width+0.4, t4, width, label='4 threads')

ax.set_ylabel('Tempo de execução')
ax.set_title('Speedup x quantidade de UPs')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()

ax.bar_label(rects1, padding=3)
ax.bar_label(rects2, padding=3)

#x_formatter = ScalarFormatter()
#x_formatter.set_scientific(True)
#x.xaxis.set_major_formatter(x_formatter)
#ax.ticklabel_format(useMathText=True,style="scientific",scilimits=(0,0))

plt.xticks(rotation=70)
fig.tight_layout()
plt.savefig('resultados_speedup.png')

