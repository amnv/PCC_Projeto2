#include <pcc/manager.h>
#include <iostream>
#include <pcc/compress.h>

using namespace std;

void indexer(string file, string indexType) {
    // cout << "Modo de indexação " << endl;
    if (indexType == "array") {
        //chama o array suffix
    } else { //ja passou pela verificacao no main (array | suffix)
        //chama o suffix tree
    }

    string all = "A_ASA_DA_CASA";
    //saida do algoritmo eh entao toda serializada e eh passada para o metodo compress
    Compress::create(file + ".idx", all);
}

void searcher(string file, string pattern, string patterFile, bool count) {
    // cout << "Modo de busca " << endl;
    string uncompress = Compress::extract(file);
    cout << uncompress << endl;
    //o metodo extract retorna uma string, essa deve ser deserializada 
    // e entao pode ser usada como se não houvesse compressão

    //chama o buscador aqui, se precisar diferenciar o tipo do indexador (array,tree) pode
    // colocar junto c a serializacao uma sinalizacao e entao resgata-la aqui

}