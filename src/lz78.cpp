#include <pcc/lz78.h>
#include <map>

using namespace std;

#define c_esp 27


void LZ78::encode(string text, FileWriter*  w) {
    w->write('8'); //marcando para decoder
    map<string, int> D;
    D.insert(pair<string,int>("", 0));
    string temp = ""; //guarda casas acumuladas por jah existirem no dicionario   
    for (int i=0; i<text.length(); i++) {
        char c = text[i];
        if (D.find(temp+c) == D.end()) { //nao achou o padrao
            D.insert(pair<string,int>(temp+c, D.size()));
            w->write(to_string(D[temp]));
            if (c >= '0' && c <= '9') { //marca numeros com caracter especial
                w->write((char)c_esp);
                w->write((char)c_esp);
            }
            w->write(c); 
            temp = ""; //gravou no dicionario, entao zera cache
        } else { //ja existe no D
            temp += c; //acumula
        }
    }
}

string LZ78::decode(FileReader* r) {
    map<int, string> D;
    D.insert(pair<int, string>(0, ""));
    string s;
    while (!r->eof()) {
        int seq = r->getInt();
        char c;
        if (!r->getChar(c))
            break;
        char esp = c_esp;
        if (c == esp) { //se for o caracter especial
            char temp;
            if (!r->peek(temp)) { //ve o proximo
                break;
            }
            if (temp == esp) { //eh o numero que entra como caracter o proximo
                r->getChar(temp); //removendo caracter especial
                r->getChar(c); //pegando numero char real
            }
        }
        string t = D[seq] + c;
        s += t;
        D.insert(pair<int, string> (D.size(), t));
        // cout << s << endl;
    }
    return s;
}