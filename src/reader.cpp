#include <string>
#include <fstream>
#include <pcc/reader.h>

using namespace std;

Reader::Reader(string path) {
    this->path = path;
    this->setFile(path);
}

Reader::~Reader() {
    this->file.close();
}

bool Reader::getLine(string& line) {
/** Retorna se ainda consegue ler e se sim, coloca a proxima linha na var do parametro */ 
    if (!file.eof()) {
        getline(file, line);
        return true;
    } else {
        file.close();
        return false;
    }
}

void Reader::reloadFile() {
    /** Usada qd jah leu todas linhas do arquivo e precisa ler dnv */
    this->setFile(this->path);
}

void Reader::setFile(string path) {
    /** Abre um arquivo para leitura, fechando um anterior se existir */
    if (file && file.is_open()) {
        file.close();
    }
    file.open(path);
    

}