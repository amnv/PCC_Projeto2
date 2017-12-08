#include <iostream>
#include <map>
#include <pcc/filewriter.h>
#include <pcc/filereader.h>
#include <pcc/compress.h>

using namespace std;

void Compress::create(string file, string& text) {
    FileWriter* w = new FileWriter(file, false);
    //
    // FileReader* r = new FileReader("/tmp/test");
    // string line;
    // text = "";
    // while (r->getLine(line)) {
    //     text += line + "\n";
    // }
    //
    map<string, int> D;
    D.insert(pair<string,int>("", 0));
    string temp = "";    
    for (int i=0; i<text.length(); i++) {
        char c = text[i];
        if (D.find(temp+c) == D.end()) { //nao achou o padrao
            D.insert(pair<string,int>(temp+c, D.size()));
            w->write(to_string(D[temp]));
            if (c >= '0' && c <= '9') {
                char esp = 8;
                w-> write(esp + string(1, c) + esp); //cerco numeros por caracter especial
            } else {
                w->write(string(1, c));
            }
            temp = "";
        } else {
            temp += c;
        }
    }
    w->flush();
}

string Compress::extract(string file) {
    FileReader* r = new FileReader(file);
    map<int, string> D;
    D.insert(pair<int, string>(0, ""));
    string s;
    int seq;
    bool ja_seq = false;
    while (!r->eof()) {
        if (!ja_seq) {
            seq = r->getInt();
        }
        ja_seq = false; //diz q nao carregou seq
        char c = r->getChar();
        char esp = 8;
        if (c == esp) { //se for o caracter especial
            char temp = r->getChar();
            char d = r->peek();
            if (d == esp) { //cercando o numero, ele eh ignorado
                c = temp; //pegando char numerico real
                r->getChar(); //removendo caracter sinalizador
            } else {
                seq = temp - '0'; //transformando em valor int real
                ja_seq = true; //ja pegou o valor e nao precisa pegar na proxima
            }
        }
        string t = D[seq] + c;
        s += t;
        D.insert(pair<int, string> (D.size(), t));
        // cout << s << endl;
    }
    return s;
}