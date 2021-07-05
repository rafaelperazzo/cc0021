import multiprocessing
import queue
import random
import time

def produtor(dados):
    while True:
        item = random.randint(0,256)
        print(multiprocessing.current_process().name + " inserindo elemento...")
        dados.put(item)
        time.sleep(random.randint(0,5))

def consumidor(dados):
    while True:
        if dados.empty():
            print(multiprocessing.current_process().name + " sem dados para serem consumidos!")
            time.sleep(random.randint(0,5))
        else:
            print(multiprocessing.current_process().name + " obtendo: " + str(dados.get()))
            time.sleep(random.randint(0,5))

if __name__ == '__main__':
    dados = multiprocessing.Queue()
    p1 = multiprocessing.Process(target=produtor,args=(dados,),name="Produtor")
    p2 = multiprocessing.Process(target=consumidor,args=(dados,),name="Consumidor 1")
    p3 = multiprocessing.Process(target=consumidor,args=(dados,),name="Consumidor 2")
    p1.start() 
    p2.start()
    p3.start()
    p1.join()
    p2.join()
    p3.join()