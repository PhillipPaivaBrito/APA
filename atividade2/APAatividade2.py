import time

def merge_Sort(lista):
	
        if (len(lista) > 1):
                meio = len(lista)//2

                listaDaEsquerda = lista[:meio]
                listaDaDireita = lista[meio:]

                merge_Sort(listaDaEsquerda)
                merge_Sort(listaDaDireita)

                i = 0
                j = 0
                k = 0

                while i < len(listaDaEsquerda) and j < len(listaDaDireita) :
                        if listaDaEsquerda[i] < listaDaDireita[j] :
                                lista[k]=listaDaEsquerda[i]
                                i += 1
                    
                        else:
                                lista[k]=listaDaDireita[j]
                                j += 1
        
                        k += 1
                                        
                while i < len(listaDaEsquerda) :
                    lista[k]=listaDaEsquerda[i]
                    i += 1
                    k += 1

                while j < len(listaDaDireita) :
                    lista[k]=listaDaDireita[j]
                    j += 1
                    k += 1
	
def quick_Sort(lista, ini, fim):
    
	i = ini
	j = fim
	
	pivo = lista[((ini + fim) // 2)]
	
	while i < j :
		while  lista[i] < pivo :
			i = i + 1
			
		while lista[j] > pivo :
			j = j - 1
			
		if  i < j :
			aux = lista[i]
			lista[i] = lista[j]
			lista[j] = aux
			i = i + 1
			j = j - 1
			
	if ini < j :
		quick_Sort(lista, ini, j-1)
		
	if i < fim :
		quick_Sort(lista, i, fim-1)
		
try:
    filename = input("digite o nome do arquivo: ")
    #filename = "couting.txt"
    file = open(filename, 'r')
    lista = []
    lista = file.readlines()
    print(lista)
    print("tamanho = " + str(len(lista)))

    start = time.time()
    merge_Sort(lista)
    print("\n ordenação com merge :" + str(lista))
    print("\n" + str(time.time()-start) + " segundos")
    start = time.time()
    quick_Sort(lista,0,(len(lista)-1))
    print("\n ordenação com quick :" + str(lista))
    print("\n" + str(time.time()-start) + " segundos")
    
finally:
    file.close()

