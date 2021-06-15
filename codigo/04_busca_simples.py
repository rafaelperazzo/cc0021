'''
BUSCA SIMPLES EM UM VETOR COM THREADS

'''
import threading
import random
import time

def busca(n,vetor):
    for i in range(0,len(vetor),1):
        if n==vetor[i]:
            print(threading.currentThread().getName() + " ENCONTROU!")

def main():
    
    tamanho = 30000000
    max = 30000000
    n = 109382
    vetor = random.sample(range(0,tamanho),tamanho)
    #EXECUÇÃO SEQUÊNCIAL
    inicio = time.time()
    busca(n,vetor)
    fim = time.time()
    print("Execucao sequencial: " + str(fim-inicio) + " segundos")
    #EXECUÇÃO "CONCORRENTE"
    fatia = int(len(vetor)/4)
    thread1 = threading.Thread(target=busca,args=(n,vetor[:fatia],),name="Tarefa 1")
    thread2 = threading.Thread(target=busca,args=(n,vetor[fatia:fatia*2],),name="Tarefa 2")
    thread3 = threading.Thread(target=busca,args=(n,vetor[fatia*2:fatia*3],),name="Tarefa 3")
    thread4 = threading.Thread(target=busca,args=(n,vetor[fatia*3:],),name="Tarefa 4")
    inicio = time.time()
    thread1.start()
    thread2.start()
    thread3.start()
    thread4.start()
    thread1.join()
    thread2.join()
    thread3.join()
    thread4.join()
    fim = time.time()
    print("Execucao concorrente: " + str(fim-inicio) + " segundos")

if __name__ == "__main__":
    main()