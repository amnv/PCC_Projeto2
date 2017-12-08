#include <iostream>
#include <map>
#include <pcc/filewriter.h>
#include <pcc/filereader.h>
#include <pcc/compress.h>

using namespace std;

#define c_esp 27

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
                char esp = c_esp;
                w-> write(string(1, esp) + string(1, esp) + string(1, c)); //marca numeros com caracter especial
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
    while (!r->eof()) {

        int seq = r->getInt();
        char c = r->getChar();
        char esp = c_esp;
        if (c == esp) { //se for o caracter especial
            char temp = r->peek(); //ve o proximo
            if (temp == esp) { //eh o numero que entra como caracter o proximo
                r->getChar(); //removendo caracter especial
                c = r->getChar(); //pegando numero char real
            }
        }
        string t = D[seq] + c;
        s += t;
        D.insert(pair<int, string> (D.size(), t));
        // cout << s << endl;
    }
    return s;
}