import threading
import time


def tarefa1():
    print("Tarefa 1 em execução")
    time.sleep(7)
    print("Tarefa 1 terminada...")

def tarefa2():
    print("Tarefa 2 em execução")
    time.sleep(3)
    print("Tarefa 2 terminada...")


def tarefa3():
    print("Tarefa 3 em execução")
    time.sleep(2)
    print("Tarefa 3 terminada...")


t1 = threading.Thread(target=tarefa1)
t2 = threading.Thread(target=tarefa2)
t3 = threading.Thread(target=tarefa3)

t1.start()
t2.start()
t3.start()

print("Linha de execução principal continuando o processamento...")
time.sleep(3)

t1.join()
t2.join()
t3.join()