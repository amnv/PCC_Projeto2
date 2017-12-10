#include <pcc/lz77.h>
#include <algorithm>
#include <iostream> //remover

using namespace std;


#define c_esp 27

int** build_dfa(string);

void LZ77::encode(string text, FileWriter* w) {
    int window_size = min((size_t)8, text.size()); //falte caracteres
    int buffer_size = 4;
    int skip = 0;
    for (int i = 0; i<text.size(); i += 1 + skip) {
        int window_init = max(i-window_size, 0); //janela comeca em 0 ate ter espaco para se mover
        int window_end = window_init + min(window_size, i); //cresce devagar, ate chegar em seu tamanho original

        int buffer_init = window_end; //window_end eh aonde terminou + 1
        int currstate=0, maxstate = 0;

        buffer_size = min((size_t) buffer_size, text.size() - window_end); //caso falte menos caracteres do q o tamanho
        // cout << (text.substr(window_init, window_end - window_init ) + " => " + text.substr(buffer_init, buffer_size)) << "\n";
        
        int** dfa = build_dfa(text.substr(buffer_init, buffer_size));
        int pos = 0;
        for (int j=window_init; j<window_end && j<text.size(); j++) {
            // leio todos caracteres da janela, tentando dar match e assim salvo a maior substring que encontrar
            currstate = dfa[text[j]][currstate];
            // maxstate = max(maxstate, currstate); //mais longe que chegou com o padrao
            if (currstate > maxstate) {
                maxstate = currstate;
                pos = j - window_init; //posicao em relacao somente a dentro da janela
            }
        }
        skip = maxstate;
        char c = 0;
        if (i+skip < text.size()) { //ainda tem cacteres
            c = text[i+skip];
        }
        if (skip > 0) {//deu match em algum caracter entao pos != 0
            pos = pos - (skip - 1); //pegando caracter inicial que chegou no maior substring
            pos = window_end - window_init - pos; //invertendo ordem de contagem e add 1
        }
        // string s = "";
        w -> write(pos);
        w -> write(skip);
        if (c >= '0' && c <= '9') { //o conteudo eh caracter numerico
            w->write((char)c_esp);
            w->write((char)c_esp);
        }
        w -> write(c);
    }
    
}

string LZ77::decode(FileReader* r) {
    // string s = "";

    // int ns = r->getInt();

}

int** build_dfa(string pat) {
    int abcS = 1<<(sizeof(unsigned char)*8);
    int patS = pat.size();
    int** dfa = new int*[abcS];
    auto f = [&](int* & t){
        t = new int[patS];
    };
    for_each(dfa, dfa + abcS, f);

    
    for (int ab=0; ab<abcS; ab++) { 
        dfa[ab][0] = 0; //qualquer coisa que vir no estado 0 faz reiniciar
    }

    dfa[pat[0]][0] = 1; //exceto, o simbolo que deveria vir (que eh a primeira letra do padrao)
    int arp = 0;
    
    for (int p=1; p<patS; p++) {
        for (int ab=0; ab<abcS;ab++) {
            dfa[ab][p] = dfa[ab][arp]; //copio a coluna do caracter arp do padrao para o caracter que foi lido
        }
        dfa[pat[p]][p] = p+1; //deu match vai pro proximo caracter
        arp = dfa[pat[p]][arp]; //na coluna anterior pra onde ele mandar ir qd esse caracter atual eh lido (causa o efeito de recuo, como se voltasse um caracter do padrao)
    }
    return dfa;
}
