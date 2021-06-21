import threading
from random import randint
import time

def tarefa1(min,max):
    print('Iniciou: ' + threading.currentThread().getName())
    time.sleep(randint(0,10))
    print(randint(min,max))
    print('Terminou: ' + threading.currentThread().getName())

def tarefa2(n):
    print("Iniciou: " + threading.currentThread().getName())
    cont = 0
    for i in range(2,n,1):
        if (n%i==0):
            cont = cont + 1
    if (cont>0):
        print("Primo:" + str(n))
    else:
        print("Nao primo: " + str(n))
    print("Terminou: " + threading.currentThread().getName())

def main():

    thread1 = threading.Thread(target=tarefa1, args=(10,100,),name='Tarefa 01')
    thread2 = threading.Thread(target=tarefa1, args=(100,1000,),name='Tarefa 02')
    thread3 = threading.Thread(target=tarefa1, args=(1000,10000,),name='Tarefa 03')
    thread4 = threading.Thread(target=tarefa1, args=(10000,20000,), name='Tarefa 04')

    thread1.start()
    thread2.start()
    thread3.start()
    thread4.start()

    thread1.join()
    thread2.join()
    thread3.join()
    thread4.join()

    print("TERMINOU O PROGRAMA PRINCIPAL")

if __name__ == "__main__":
    main()
