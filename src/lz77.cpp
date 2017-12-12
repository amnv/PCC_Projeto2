#include <pcc/lz77.h>
#include <algorithm>
#include <iostream> //remover

using namespace std;

char uni(char n, char m, int bitm) {
    int bitn = sizeof(char)*8 - bitm;
    if (bitn + bitm > sizeof(char)*8) {
        cerr << "problemas com a uniao, abortando..." << endl;
        throw 1;
        // return  0; //vai ficar em 1 char no final
    }
    return (n << bitm) | m;
}

void sep(char& z, char& n, char& m, int bitm) {
    /** recebe um char que eh a uniao de 2 numeros, o tamanho de bit do menor
     * e coloca o resultado nos parametros n e m recebidos
    */
    char aux = 0;
    int bit = bitm;
    while (bit--) {
        aux <<= 1;
        aux |= 1;
    }
    m = (z & (aux));
    n = (z & ~aux);
    while (bitm--) {
        n >>= 1;
        n &= ~(1<<sizeof(char)*8-1);
    }
}

void div2(int a, int pbit, char& big, char& little) {
    /** recebe um inteiro e o divide em 2 partes */
    little = 0;
    int bit = -1;
    while(++bit < pbit) {
        little |= ((1<<bit) & a);
    }
    big = a >> pbit;
}

void soma2(int i, int c, int nbit, char& ibig, char&ic ) {
    /** dados 2 inteiros, quebra-os em 2 char, sendo o primeiro soh com partes do inteiro i 
     * e o segundo com o inteiro c nos nbit menos significativos e o restante para o resto do i
     * */
    char big, little;
    div2(i, (sizeof(char)*8) - nbit, big, little); //divide o primeiro em 2 partes
    ic = uni(little, c, nbit);
    ibig = big;
}

void separa2(char a, char b, int nbit, int& n, int& m) {
    /** da 2 chars e os separa em 2 inteiros, sendo o primeiro o char a + alguns bits do b */

    int qtdeI = (sizeof(int)*8), qtdeC = sizeof(char)*8;
    int aa = (int)a;
    n = (aa << (sizeof(char)*8 - nbit));
    char c, d;
    sep(b, c, d, nbit);
    int cc = (int) c;
    n |= cc;
    int bb = (int)d;
    m = bb;

}


void build_dfa(string pat, int** & dfa) {
    int abcS = 256;
    int patS = pat.size();
    dfa = new int*[256];
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


void LZ77::encode(string text, FileWriter* w) {
    w->write('7'); //marcando para decoder
    
    int window_size = min((size_t)4095, text.size()); //falte caracteres
    int buffer_size = 7;
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
        // for (int i1=0; i1<256;i1++) {
        //     dfa[i1] = new int[dfa]
        //     for (int j1=0; j1<buffer_size; j1++) {

        //     }
                
        // }
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
        
        if (skip > 0) {//deu match em algum caracter entao pos != 0
            pos = pos - (skip - 1); //pegando caracter inicial que chegou no maior substring
            pos = window_end -1 - window_init - pos; //invertendo ordem de contagem
        }
       
        // w -> write((char)skip);
        // if (skip > 0) {
            // if (pos > 4095 || pos < 0 || skip > 7 || skip < 0) {
            //     cerr << "problemas" << endl;
            //     cout << pos << " " << skip << endl;
            // }
            char x, y;
            soma2(pos, skip, 3, x, y); //tranforma eles em 2 bytes, sendo 3 bits para o skip
            w -> write(x);
            w -> write(y);
        // } else {
        //     w -> write((char)skip);
        // }
        string c = "";
        if (i+skip < text.size()) { //caracter final nao aparece na ultima iteracao
            c = text[i+skip];
            w -> write(c[0]);
        }
        // cout << pos << " " << skip << " " << c << endl;
    }
    
}

string LZ77::decode(FileReader* r) {
    string s = "";

    while (!r->eof()) {       
        int pos;
        int tam;
        char x, y;
        r->getChar(x);
        r->getChar(y);
        separa2(x, y, 3, pos, tam);
        // tam = c;
        // if (tam > 0) {
        //     pos = c;
        // }
        // cout << pos << tam << endl;
        if (tam > 0) {
            // cout << "sub '" << s.substr(s.size() - 1 - pos, tam) << "'" << endl;
            s += s.substr(s.size() - 1 - pos, tam);
        }
        // cout << "Agora " << s << endl;    
        char c;
        if (!r->eof() && r->getChar(c)) {
            // cout << "c '" << c << "'"<< endl;
            s += c;
        }
        // cout << "Agora2 " << s << endl;
    }
    return s;
}