#include <pcc/manager.h>
#include <iostream>
#include <pcc/compress.h>
#include <regex>

using namespace std;

auto reg = [](string ex, string& str) {
    regex rgx(ex);
    smatch match;
    if (regex_search(str, match, rgx)) {
        str = match[1];
        return true;
    }
    return false;
};

void indexer(string file, string indexType, string compressType) {

    if (indexType == "array") {
        //chama o array suffix
    } else { //ja passou pela verificacao no main (array | suffix)
        //chama o suffix tree
    }

    string all = "A_ASA_DA_CASA";

    
    //saida do algoritmo eh entao toda serializada e eh passada para a string all
    reg("(.*?)[.][a-zA-Z0-9]*$", file);
    Compress::create(file + ".idx", all, compressType);
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