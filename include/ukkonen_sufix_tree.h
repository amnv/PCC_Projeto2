#ifndef UKKONEN_SUFIX_TREE_H
#define UKKONEN_SUFIX_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <cfloat>

const int N = 112345;
int nodeid = 1;

std::string s;
struct Node{
public:
    int id;
    //start index
    int l;
    //ending index
    int r;
    //parent
    int p;
    std::map<char, int> chd;

    Node(int Id, int L, int R, int P) : id(Id), l(L), r(R), p(P) {}
    Node() : id(0), l(0), r(-1), p(0) {}
    int len(){
        return r - l + 1;
    }
    char operator[](int i){
        return s[l+i];
    }
} t[2*N];


int new_node(int L, int R, int P){
    t[nodeid] = Node(nodeid, L, R, P);
    return nodeid++;
}

void print_cst(Node root, int level, std::string text){
    //std::cout << "root: " << root.r << std::endl;
    for(int i=0; i<2*level; i++){
        std::cout << " ";
    }
    std::cout << "[id=" << root.id << " l=" << root.l << " r=" << root.r;

    int len = std::min(root.r, static_cast<int>(text.size()));
    len = len == -1 ? text.size() : len;
    len = len - root.l;
    std::cout << " len=" << len;
    std::cout << " edge=" << text.substr(root.l, root.len());
    // Nao faco ideia do que o slink eh
    // std::cout << " slink=";
    std::cout <<  "]" << std::endl;


    for(std::map<char,int>::iterator iter = root.chd.begin(); iter != root.chd.end(); iter++){
        print_cst(t[iter->second], level+1, text);
    }
}

void build_sufix_tree(std::string text, std::string alphabet){
    // Adiciona um caractere que nao aparece na string em nenhum lugar (nao ta no
    // alfabeto) no final para garantir que cada sufixo vai ter sua propria folha
    // Isso garante que nenhum sufixo eh prefixo de outro sufixo
    s = text + '$';

    for(int i=0; i<s.size(); i++){
        std::cout << "i=" << i << std::endl;
        //cn eh o cara q eu to analisando
        //cd eh o index do filho
        int cn = 0, cd = 0;

        for(int j=i; j<s.size(); j++){
            // Se eu to em um vertice e nao tenho esse filho
            if(cd == t[cn].len() && !t[cn].chd.count(s[j])){
                t[cn].chd[s[j]] = new_node(j, s.size()-1, cn);
                break;
            // Se eu to no meio e uma aresta (eu nao analisei todos os caracteres dessa
            // aresta) e o caractere atual eh diferente do cara q eu to tentando adicionar (s[j])
            // entao eu quebro a aresta em duas (crio mid)
            }else if(cd < t[cn].len() && t[cn][cd] != s[j]){
                int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].p);
                t[mid].chd[s[j]] = new_node(j, s.size()-1, mid);
                t[mid].chd[t[cn][cd]] = cn;
                t[cn].l += cd;
                t[cn].p = mid;
                t[t[mid].p].chd[t[mid][0]] = mid;
                break;
            }
            if(cd == t[cn].len()){
                cn = t[cn].chd[s[j]];
                cd = 0;
            }
            cd++;
        }

        print_cst(t[0], 0, s);
    }
}

void check_pattern(std::string pat){
    int cn = 0;
    for(int i=0; i<pat.size(); i++){
        bool found = false;
        for(std::map<char,int>::iterator iter = t[cn].chd.begin(); iter != t[cn].chd.end(); iter++){
            Node chd = t[iter->second];
            int len = chd.len() <= pat.size()-i ? chd.len() : pat.size()-i;

            std::string chdString = s.substr(chd.l, len);
            std::string patString = pat.substr(i, len);
            if(chdString.find("$") != std::string::npos){
                patString += "$";
            }

            //std::cout << "CHD SUBS: " <<  chdString << ", PAT SUBS: " << patString << std::endl;
            if(chdString == patString){
                cn = iter->second;
                i += len - 1;
                found = true;
                break;
            }


        }

        if(!found){
            std::cout << "pattern not found" << std::endl;
            return;
        }

    }

    std::cout << "pattern found" << std::endl;
}

#endif