import multiprocessing
import time
import random

def tarefa():
    nome = multiprocessing.current_process().name
    print("O processo: " + nome + " iniciou...")
    time.sleep(random.randint(3,10))
    print("O processo: " + nome + " finalizou...")

if __name__ == '__main__':
    p1 = multiprocessing.Process(target=tarefa,name="PROCESSO 1")
    p2 = multiprocessing.Process(target=tarefa,name="PROCESSO 2")
    p3 = multiprocessing.Process(target=tarefa,name="PROCESSO 3")
    inicio = time.time()
    p1.start()
    p2.start()
    p3.start()
    p1.join()
    p2.join()
    p3.join()
    fim = time.time()
    print(fim-inicio)