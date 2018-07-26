import time

def selection_sort(lista):
    start = time.time()
    for i in range(len(lista)):
        imenor = i
        k = i
        for k in range(i, len(lista)):
            if (int(lista[k]) < int(lista[imenor])):
                imenor = k
    aux = lista[int(i)]
    lista[int(i)] = lista[imenor]
    lista[imenor]=aux
    print("\n ordenação com selection :" + str(lista))
    print("\n" + str(time.time()-start) + " segundos")

def insertion_sort( lista ):
    start = time.time()
    for i in range(1, len(lista)):
        aux = lista[i]
        k = i
        while k > 0 and int(aux) < int(lista[k - 1]):
            lista[k] = lista[k - 1]
            k -= 1
        lista[k] = aux
    print("\n ordenação com insertion :" + str(lista))
    print("\n" + str(time.time()-start) + " segundos")

try:
    filename = input("digite o nome do arquivo: ")
    #filename = "aqui.txt"
    file = open(filename, 'r')
    lista = []
    lista = file.readlines()
    print(lista)
    print("tamanho = " + str(len(lista)))
    insertion_sort(lista)
    selection_sort(lista)
    
finally:
    file.close()

