import threading
import numpy
import random

def gerar_matriz(linhas,colunas):
    linhas = 10
    colunas = 10
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



