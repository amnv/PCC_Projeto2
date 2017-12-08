#include <pcc/manager.h>
#include <iostream>
#include <pcc/compress.h>

using namespace std;

void indexer(string file, string indexType) {
    cout << "Modo de indexação " << endl;
    //chama o indexador de suffixs aqui
    

    string all = "A_ASA_DA_CASA";
    //saida do algoritmo eh entao toda serializada e eh passada para o metodo compress
    Compress c;
    c.create(file + ".idx", all);
}

void searcher(string file, string pattern, string patterFile, bool count) {
    cout << "Modo de busca " << endl;
    Compress c;
    cout << c.extract(file) << endl;
    //o metodo extract retorna uma string, essa sera deserializada 
    // e entao se tornara objeto novamente, podendo usa-lo como se não houvesse compressão

    //chama o buscador aqui, se precisar diferenciar o tipo do indexador (array,tree) eh soh
    // sinalizar colocar junto c a serializacao e entao resgatar a label aqui e tratar

}