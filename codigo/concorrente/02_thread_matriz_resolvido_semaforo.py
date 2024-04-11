import threading
import numpy
import random

def gerar_matriz(linhas,colunas):
    m = numpy.zeros((linhas,colunas))
    for i in range(0,linhas):
        for j in range(0,colunas):
            m[i][j] = random.randint(1,100)

    return(m)

def soma_linha(m,linha):
    soma = 0
    for j in range(0,len(m[0])):
        soma = soma + m[linha][j]
    
    print(soma)
    
    #Acessando a "região crítica"
    global soma_total
    global semaforo
    semaforo.acquire()
    soma_total = soma_total + soma
    semaforo.release()
    
#GERANDO MATRIZ ALEATÓRIA
m = gerar_matriz(3,3)
print(m)

#Criando o Lock
semaforo = threading.Semaphore(1)

#Criando a variável compartilhada
soma_total = 0

#CRIANDO THREADS
threads = []
for i in range(0,len(m)):
    t = threading.Thread(target=soma_linha,args=(m,i))
    threads.append(t)
    t.start()

#AGUARDANDO THREADS
for t in threads:
    t.join()

#MOSTRANDO A SOMA TOTAL
print(soma_total)

print("FIM")

