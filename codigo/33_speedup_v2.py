import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from matplotlib.ticker import ScalarFormatter

df = pd.read_csv('resultados.csv',sep=';')

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

fig, ax = plt.subplots()
x = labels 
plt.xticks(rotation=90)
plt.bar(x,t1,x,t2)
plt.plot()
plt.show()
plt.savefig('resultados_speedup.png')

