import multiprocessing
import time

def function_square(data):
    result = data*data
    return result

def square_serial(data):
    resultados = []
    for i in range(0,len(data),1):
        result = data[i]*data[i]
        resultados.append(result)
    return(resultados)

if __name__ == '__main__':
    inputs = list(range(10000000))
    #PROCESSAMENTO PARALELO
    inicio = time.time()
    pool = multiprocessing.Pool(processes=2)
    pool_outputs = pool.map(function_square, inputs)
    pool.close()
    pool.join()
    fim = time.time()
    tempo_paralelo = fim-inicio
    print("Tempo paralelo: " + str(tempo_paralelo))

    inicio = time.time()
    pool = multiprocessing.Pool(processes=1)
    pool_outputs = pool.map(function_square, inputs)
    pool.close()
    pool.join()
    fim = time.time()
    tempo_serial = fim-inicio
    print("Tempo serial: " + str(tempo_serial))
    speedup = tempo_serial/tempo_paralelo
    print(speedup)