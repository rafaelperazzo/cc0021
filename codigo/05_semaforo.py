import threading
import time
import random

semaforo = threading.Semaphore(0)
shared = 0

def produtor():
    global shared
    time.sleep(5)
    shared = random.randint(0,1000)
    print("Gerado o numero: %s" %shared)
    semaforo.release()

def consumidor():
    print("Aguardando liberacao do recurso compartilhado...")
    semaforo.acquire()
    print("Consegui acessar o recurso compartilhado: %s" %shared)

if __name__ == '__main__':
    t1 = threading.Thread(target=produtor)
    t2 = threading.Thread(target=consumidor)
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    print("FIM")