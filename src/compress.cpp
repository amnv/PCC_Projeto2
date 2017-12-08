#include <iostream>
#include <map>
#include <pcc/compress.h>

using namespace std;

Compress::Compress(string file) {
    w = new FileWriter(file, false);
}

void Compress::compress(string& text) {
    map<string, int> D;
    D.insert(pair<string,int>("", 0));
    string temp = "";    
    for (int i=0; i<text.length(); i++) {
        char c = text[i];
        if (D.find(temp+c) == D.end()) { //nao achou o padrao
            D.insert(pair<string,int>(temp+c, D.size()));
            if (c >= '0' && c <= '9') {
                w->write(to_string(D[temp]), " ");
            } else {
                w->write(to_string(D[temp]));
            }
            w-> write(string(1, c));
            temp = "";
        } else {
            temp += c;
        }
    }
    w->flush();
}

string Compress::extract(string file) {
    
}