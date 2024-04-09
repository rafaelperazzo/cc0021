import threading
import time

def soma(a,b):
    time.sleep(4)
    print("Terminou a thread...")

def tarefa2():
    global x
    x = x + 1

def tarefa3():
    global x
    x = x + 1

t1 = threading.Thread(target=soma, args=(1,2,))
x = 10
t1.start()
print("Thread iniciada...")
t2 = threading.Thread(target=tarefa2)
t3 = threading.Thread(target=tarefa3)
t2.start()
t3.start()
t1.join()
t2.join()
t3.join()
print(x)

