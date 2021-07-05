import multiprocessing
import time
import random
import math

def busca(indices):
    total = 0
    global n
    global vetor
    for i in range(0,len(indices),1):
        if vetor[i]==n:
            total = total + 1
    return(total)

def busca_sequencial(vetor,n):
    total = 0
    for i in range(0,len(vetor),1):
        if (vetor[i]==n):
            total = total + 1

if __name__ == '__main__':
    tamanho = 10000000
    n = 20
    p = 2
    vetor = random.sample(range(0,tamanho),tamanho)
    indice1 = list(range(0,math.ceil(tamanho/p)))
    indice2 = list(range(math.ceil(tamanho/p),tamanho))
    indices = [indice1,indice2]
    print("INICIANDO...")
    pool = multiprocessing.Pool(processes=p)
    inicio = time.time()
    pool_outputs = pool.map(busca,indices)
    pool.close()
    pool.join()
    fim = time.time()
    tempo_paralelo = fim - inicio
    print(pool_outputs)
    print("Tempo paralelo: " + str(tempo_paralelo))
    inicio = time.time()
    busca_sequencial(vetor,n)
    fim = time.time()
    tempo_sequencial = fim - inicio
    speedup = tempo_sequencial/tempo_paralelo
    print("Tempo sequencial: " + str(tempo_sequencial))
    print(speedup)