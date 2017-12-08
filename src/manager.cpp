#include <pcc/manager.h>
#include <iostream>
#include <pcc/compress.h>

using namespace std;

void indexer(string file, string indexType) {
    cout << "Modo de indexação " << endl;
    Compress c(file + ".idx");
    string text = "A_ASA_DA_CASA";
    c.compress(text);
}

void searcher(string file, string pattern, string patterFile, bool count) {
    cout << "Modo de busca " << endl;

}