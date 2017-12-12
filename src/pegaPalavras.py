def pegaPalavras(tamanho):
    texto = open("english.txt", "r")
    lista = []
    lista = [word for word in texto if len(word) == tamanho]
    #print len(lista)
    #for i in lista:
    #   print i
    texto.close()
    return lista

def retira_espaco(path_temp, path_final):
    entrada = open(path_temp, "r")
    saida = open(path_final, "w")
    texto = ""
    for i in entrada:
        texto += " ".join(i.split())
        texto += "\n"
    saida.write(texto)
    saida.close()
    entrada.close()
        
def tira_repetidas(path_temp, path_final):
    texto = open(path_temp, "r")

    lines_seen = set() # holds lines already seen
    outfile = open(path_final, "w")
    for line in texto:
        if line not in lines_seen: # not a duplicate
            outfile.write(line)
            lines_seen.add(line)
    outfile.close()
    texto.close()

def pega_suficiente(path_temp, path_final):
    texto = open(path_temp, "r")
    saida = open(path_final, "w")
    count = 0
    size = 5
    for linha in texto:
        if len(linha) == size:
            if count < 50:
                saida.write(linha)
                count += 1
            else:
                size += 5
                count = 0        

    texto.close()
    saida.close()

def main():
    path_temp = "patternsProvisorio.txt"
    path_temp2 = "patterns_sem_repetidas.txt"
    path_temp3 = "patterns_sem_espaco.txt"
    path_final = "patterns.txt"
    #separando palavras por tamanho
    for i in range(5, 30, 5):
        palavras = pegaPalavras(i)
        saida = open(path_temp, "a")
        for j in palavras:
            saida.write(j)
        saida.close()

    tira_repetidas(path_temp, path_temp2)
    retira_espaco(path_temp2, path_temp3)
    pega_suficiente(path_temp3, path_final)

main()
