#include <pcc/lz77.h>
#include <algorithm>


using namespace std;


#define c_esp 27

void LZ77::encode(string text, FileWriter* w) {
    // int swindow = 10;
    // int sbuffer = 5;

}

string LZ77::decode(FileReader* r) {
    
}

int** build_dfa(string pat) {
    string abc = "0"; //precisa ter 1 caracter para chars ficarem c valores correspondentes (abc['1'] = '1')
    int abcS = 1<<(sizeof(unsigned char)*8);
    for (unsigned char c=1; c!= 0 && c<abcS; c++) {
        abc += c;
    }
    int patS = pat.size();
    int** dfa = new int*[abcS];
    auto f = [&](int* & t){
        t = new int[patS];
    };
    for_each(dfa, dfa + abcS, f);
    // for (int i=0; i<abcS; i++) {
    //     dfa[i] = new int[patS];
    // }
    
    for (int ab=0; ab<abcS; ab++) { 
        dfa[ab][0] = 0; //qualquer coisa que vir no estado 0 faz reiniciar
    }

    dfa[pat[0]][0] = 1; //exceto, o simbolo que deveria vir (que eh a primeira letra do padrao)
    int arp = 0;
    
    for (int p=1; p<patS; p++) {
        for (int ab=0; ab<abcS;ab++) {
            dfa[ab][p] = dfa[ab][arp]; //copio a coluna do caracter arp do padrao para o caracter que foi lido
        }
        if (p!= patS-1) {
            dfa[pat[p]][p] = p+1; //deu match vai pro proximo caracter
            arp = dfa[pat[p]][arp]; //na coluna anterior pra onde ele mandar ir qd esse caracter atual eh lido (causa o efeito de recuo, como se voltasse um caracter do padrao)
        }
    }
    return dfa;
}
