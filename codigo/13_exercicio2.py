import multiprocessing
import time
import random
import math

def busca(totais,n,inicio,fim):
    divisores = 0
    for i in range(inicio,fim+1,1):
        if (n%i)==0:
            divisores = divisores + 1
    totais.put(divisores)

if __name__ == '__main__':
    totais = multiprocessing.Queue()
    n = int(input('Digite um numero: '))
    meio = math.ceil(n/2)
    corte = math.ceil(meio/2)
    
    #SEQUENCIAL
    inicio = time.time()
    ps = multiprocessing.Process(target=busca,args=(totais,n,2,meio,))
    ps.start()
    ps.join()
    fim = time.time()
    t_serial = fim-inicio
    
    #PARALELO
    inicio = time.time()   
    p1 = multiprocessing.Process(target=busca,args=(totais,n,2,corte,))
    p2 = multiprocessing.Process(target=busca,args=(totais,n,corte+1,meio,))
    p1.start()
    p2.start()
    p1.join()
    p2.join()
    fim = time.time()
    t_paralelo = fim-inicio

    #ANALISE DE DESEMPENHO
    print("*********************************")
    print("ANALISE DE DESEMPENHO")
    print("*********************************")
    print("Tempo serial: " + str(t_serial))
    print("Tempo paralelo: " + str(t_paralelo))
    speedup = t_serial/t_paralelo
    eficiencia = speedup/2
    print("Speedup: " + str(speedup))
    print("Eficiencia: " + str(eficiencia))