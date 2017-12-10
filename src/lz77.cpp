#include <pcc/lz77.h>
#include <algorithm>
#include <iostream> //remover

using namespace std;


#define c_esp 27

void build_dfa(string pat, int** & dfa) {
    int abcS = 1<<(sizeof(unsigned char)*8);
    int patS = pat.size();
    dfa = new int*[abcS];
    auto f = [&](int* & t){
        t = new int[patS];
    };
    for_each(dfa, dfa + abcS, f);
    //zerar    
    for (int ab=0; ab<abcS; ab++) { 
        dfa[ab][0] = 0; //qualquer coisa que vir no estado 0 faz reiniciar
    }
    
    dfa[pat[0]][0] = 1; //exceto, o simbolo que deveria vir (que eh a primeira letra do padrao)
    int arp = 0;
    
    for (int p=1; p<patS; p++) {
        // cout << "no bs" << p << " " << patS<< endl;
        for (int ab=0; ab<abcS;ab++) {
            dfa[ab][p] = dfa[ab][arp]; //copio a coluna do caracter arp do padrao para o caracter que foi lido
            // cout << " f " << ab<< " " <<p << endl;
        }
        dfa[pat[p]][p] = p+1; //deu match vai pro proximo caracter
        arp = dfa[pat[p]][arp]; //na coluna anterior pra onde ele mandar ir qd esse caracter atual eh lido (causa o efeito de recuo, como se voltasse um caracter do padrao)
    }
}

char uni(int n, int bitn, int m, int bitm) {
    if (bitn + bitm > sizeof(char)*8) return  0; //vai ficar em 1 char no final
    if (n > ((1<<bitn)-1) || m > ((1<<bitm)-1)) return 0;
    return (n << bitm) | m;
}

void print(int n) {
    // cout << n << endl;
    for (int i=0; i<sizeof(char)*8; i++)
        cout << (n>>(1*i) & 1);
    cout << endl;
}

int getLittleBits(int n, int q) {
    int r = 0;
    for (int i=0; i<q; i++) {
        r |= n & (1<<i);
    }
    return r;
}

int getBigBits(int n, int q) {
    n >>= (sizeof(char)*8 - q);
    // cout << (sizeof(char)*8 - q) << " " << q << endl;
    return getLittleBits(n, q);
}

void LZ77::encode(string text, FileWriter* w) {
    w->write('7'); //marcando para decoder
    
    int window_size = min((size_t)48, text.size()); //falte caracteres
    int buffer_size = 16;
    int skip = 0;
    for (int i = 0; i<text.size(); i += 1 + skip) {
        int window_init = max(i-window_size, 0); //janela comeca em 0 ate ter espaco para se mover
        int window_end = window_init + min(window_size, i); //cresce devagar, ate chegar em seu tamanho original

        int buffer_init = window_end; //window_end eh aonde terminou + 1
        int currstate=0, maxstate = 0;

        buffer_size = min((size_t) buffer_size, text.size() - window_end); //caso falte menos caracteres do q o tamanho
        // cout << (text.substr(window_init, window_end - window_init ) + " => " + text.substr(buffer_init, buffer_size)) << "\n";
        int** dfa;
        build_dfa(text.substr(buffer_init, buffer_size), dfa);
        int pos = 0;
        for (int j=window_init; j<window_end && j<text.size() && currstate < buffer_size; j++) {
            // leio todos caracteres da janela, tentando dar match e assim salvo a maior substring que encontrar
            // cout << "err? " << (int)text[j] << " " << currstate << endl;
            currstate = dfa[text[j]][currstate];
            // cout << "leu " << dfa[42][16] << endl;
            // maxstate = max(maxstate, currstate); //mais longe que chegou com o padrao
            if (currstate > maxstate) {
                maxstate = currstate;
                pos = j - window_init; //posicao em relacao somente a dentro da janela
            }
        }
        for (int l=0; l<256;l++) {
            delete(dfa[l]);
        }
        delete(dfa);

        skip = maxstate;
        char c = 0;
        if (i+skip < text.size()) { //ainda tem cacteres
            c = text[i+skip];
        }
        
        if (skip > 0) {//deu match em algum caracter entao pos != 0
            pos = pos - (skip - 1); //pegando caracter inicial que chegou no maior substring
            pos = window_end -1 - window_init - pos; //invertendo ordem de contagem
        }
       
        w -> write((char)pos);
        w -> write((char)skip);
        
        if (i+skip < text.size()) { //caracter final nao aparece na ultima iteracao
            w -> write(c);
        }
        // cout << pos << " " << skip << " " << c << endl;

    }
    
}

string LZ77::decode(FileReader* r) {
    string s = "";

    while (!r->eof()) {       
        int pos;
        int tam;
        char c;
        r->getChar(c);
        pos = c;
        r->getChar(c);
        tam = c;
        // cout << pos << tam << endl;
        if (tam > 0)
            s += s.substr(s.size() -1 - pos, tam);
        // cout << "Agora " << s << endl;    
        if (!r->getChar(c)) {
            break;
        }
        s += c;
        // cout << "Agora2 " << s << endl;            
    }
    return s;
}