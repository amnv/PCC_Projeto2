#include <string>
#include <fstream>
#include <iostream>
#include <pcc/filewriter.h>

using namespace std;

FileWriter::FileWriter(string path, bool append) {
    this->path = path;
    this->append = append;
    this->setFile(path, append);
}

FileWriter::~FileWriter() {
    this->file.flush();
    this->file.close();
}

void FileWriter::write(string text) {
    /** Escreve no arquivo */
    this->file << text;
}

void FileWriter::write(int n) {
    /** Escreve no arquivo */
    this->file << n;
}

void FileWriter::write(char c) {
    /** Escreve no arquivo */
    this->file << c;
}

void FileWriter::flush() {
    /** salva logo o arquivo */
    this->file.flush();
}

void FileWriter::setFile(string path, bool append) {
    /** Abre um arquivo para escrita, apagando ou não os seus dados (append)  */
    file.close();
    if (append) {
        // cout << "abrindo com append" << endl;
        file.open(path, std::ios_base::app); //abre em modo append
    } else{
        // cout << "abrindo normal" << endl;
        file.open(path);
    }
}