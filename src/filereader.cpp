#include <string>
#include <fstream>
#include <iostream>
#include <pcc/filereader.h>

using namespace std;

FileReader::FileReader(string path) {
    this->path = path;
    this->setFile(path);
}

FileReader::~FileReader() {
    this->file.close();
}

bool FileReader::peek(char& c) {
    /** Retorna um char sem contar na leitura */
    if(!file.eof()) {
        c = file.peek();
        return true;
    }
    return false;
}

bool FileReader::getChar(char& c) {
    if (!file.eof()) {
        file.get(c);
        return true;
    }
    return false;
}

int FileReader::getInt() {
    int r = -1;
    if (!file.eof())
        file >> r;
    return r;
}

bool FileReader::eof() {
    return file.eof();
}

bool FileReader::getLine(string& line) {
/** Retorna se ainda consegue ler e se sim, coloca a proxima linha na var do parametro */ 
    if (!file.eof()) {
        getline(file, line);
        return true;
    } else {
        file.close();
        return false;
    }
}

void FileReader::reloadFile() {
    /** Usada qd jah leu todas linhas do arquivo e precisa ler dnv */
    this->setFile(this->path);
}

void FileReader::setFile(string path) {
    /** Abre um arquivo para leitura, fechando um anterior se existir */
    if (file && file.is_open()) {
        file.close();
    }
    // file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    // try {
        file.open(path);
    // } catch (ifstream::failure e) {
    //     cerr << "Arquivo não encontrado" << endl;
    //     exit(-1);
    // }

}

bool FileReader::exist(string fileName) {
    ifstream infile(fileName);
    bool r = infile.good();
    infile.close();
    return r;
}