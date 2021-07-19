import multiprocessing
import time
import random
import math

def busca(inicio,fim,n):
    global vetor
    total = 0
    for i in range(inicio,fim,1):
        if vetor[i]==n:
            total = total + 1

if __name__ == '__main__':
    tamanho = 500000
    n = 20
    p = 2
    vetor = random.sample(range(0,tamanho),tamanho)
    print("INICIANDO...")
    p1 = multiprocessing.Process(target=busca,args=(0,1*(math.ceil(tamanho/p)),n,),name="Processo 1")
    p2 = multiprocessing.Process(target=busca,args=(1*(math.ceil(tamanho/p)),tamanho,n,),name="Processo 2")
    inicio = time.time()
    p1.start()
    p2.start()
    p1.join()
    print('p1 terminou')
    p2.join()
    print('p2 terminou')
    fim = time.time()
    tempo_paralelo = fim - inicio
    print("Tempo paralelo: " + str(tempo_paralelo))
    p5 = multiprocessing.Process(target=busca,args=(0,tamanho-1,n),name="Processo SERIAL")
    inicio = time.time()
    p5.start()
    p5.join()
    fim = time.time()
    tempo_serial = fim - inicio
    print("Tempo serial: " + str(tempo_serial))
    speedup = tempo_serial/tempo_paralelo
    print("Speedup: " + str(speedup))
    
    