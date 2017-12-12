#ifndef UKKONEN_SUFIX_TREE_H
#define UKKONEN_SUFIX_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <cfloat>

std::vector<std::string> split(std::string line, std::string delimiter) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> splited;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        splited.push_back(token);
        line.erase(0, pos + delimiter.length());
    }

    if(pos = line.find(delimiter) != std::string::npos){
        pos = line.find("\n");
        token = line.substr(0, pos);
        splited.push_back(token);
    }
    else {
        splited.push_back(line);
    }

    return splited;
}

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

    std::string to_string(){
        std::string nodeStr = "";

        nodeStr += std::to_string(id) + "," + std::to_string(l) + "," + std::to_string(r) + "," + std::to_string(p);
        for(std::map<char,int>::iterator iter = chd.begin(); iter != chd.end(); iter++){
            nodeStr += ",";

            nodeStr += std::to_string((int)iter->first);
            nodeStr += "," + std::to_string(iter->second);
        }

        //std::cout << "NODE " << nodeStr << std::endl;
        return nodeStr;
    }

    static Node from_string(std::string nodeStr){
        std::vector<std::string> data = split(nodeStr, ",");
        
        Node node = Node(std::stoi(data[0]), std::stoi(data[1]), std::stoi(data[2]), std::stoi(data[3]));
        //std::cout << data[0] << ", " << data[1] << ", " << data[2] << ", " << data[3] << ", size: " << data.size() << std::endl;
        for(int i=4; i<data.size(); i+=2){
            //std::cout << "    " << data[i] << ", " << data[i+1] << std::endl;
            node.chd[std::stoi(data[i]) + '0'] = std::stoi(data[i+1]);
        }
        //std::cout << "id=" << node.id << " chd=" << node.chd.size() << std::endl;
        return node;
    }
};

class SufixTree{
public:
    static const int N = 112345;
    int nodeid;
    std::string s;
    std::vector<Node> t;

    SufixTree(){
        nodeid = 1;
        t = std::vector<Node>(N*2, Node());
        //t.push_back(Node());
    };
    
    ~SufixTree(){};

    int new_node(int L, int R, int P){
        t[nodeid] = Node(nodeid, L, R, P);
        return nodeid++;
    };

    void print_cst(Node root, int level, std::string text){
        //std::cout << "root: " << root.r << std::endl;
        for(int i=0; i<2*level; i++){
            std::cout << " ";
        }
        std::cout << "[id=" << root.id << " l=" << root.l << " r=" << root.r << " chd=" << root.chd.size();

        int len = std::min(root.r, static_cast<int>(text.size()));
        len = len == -1 ? text.size() : len;
        len = len - root.l;
        std::cout << " len=" << len;
        std::cout << " text=" << text.substr(root.l, root.len());
        std::cout << " p=" << root.p;
        // Nao faco ideia do que o slink eh
        // std::cout << " slink=";
        std::cout <<  "]" << std::endl;


        for(std::map<char,int>::iterator iter = root.chd.begin(); iter != root.chd.end(); iter++){
            print_cst(t[iter->second], level+1, text);
        }
    };

    void build_sufix_tree(std::string text){
        // Adiciona um caractere que nao aparece na string em nenhum lugar (nao ta no
        // alfabeto) no final para garantir que cada sufixo vai ter sua propria folha
        // Isso garante que nenhum sufixo eh prefixo de outro sufixo
        s = text;// + '$';

        for(int i=0; i<s.size(); i++){
            //std::cout << "i=" << i << " c=" << s[i];
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

                    std::map<char,int>::iterator it = t[t[cn].p].chd.begin();
                    for (; it != t[t[cn].p].chd.end(); ++it )
                        if (it->second == t[cn].id)
                            break;
                    
                    if(it != t[t[cn].p].chd.end())
                        t[t[cn].p].chd.erase(it);

                    t[cn].p = mid;
                    t[t[mid].p].chd[s.substr(t[mid].l, t[mid].len())[0]] = mid;
                    

                    break;
                }
                if(cd == t[cn].len()){
                    cn = t[cn].chd[s[j]];
                    cd = 0;
                }
                cd++;
            }

        }
        print_cst(t[0], 0, s);
    };

    bool check_pattern(std::string pat){
        int cn = 0;
        for(int i=0; i<pat.size(); i++){
            bool found = false;
            for(std::map<char,int>::iterator iter = t[cn].chd.begin(); iter != t[cn].chd.end(); iter++){
                Node chd = t[iter->second];
                int len = chd.len() <= pat.size()-i ? chd.len() : pat.size()-i;

                std::string chdString = s.substr(chd.l, len);
                std::string patString = pat.substr(i, len);

                if(chdString == patString){
                    cn = iter->second;
                    i += len - 1;
                    found = true;
                    break;
                }
            }

            if(!found){
                //std::cout << "pattern not found" << std::endl;
                return false;
            }

        }

        //std::cout << "pattern found" << std::endl;
        return true;
    };

    std::string to_string(){
        std::string treestr = std::to_string(nodeid) + "\n";
        treestr += s + "\n";

        for(int i=0; i<t.size(); i++){
            if(t[i].id == 0 && i!=0)
                continue;
            treestr += t[i].to_string() + "\n";
        }

        return treestr;
    }

    static SufixTree from_string(std::string treestr){
        std::vector<std::string> data = split(treestr, "\n");
        SufixTree tree;
        tree.nodeid = std::stoi(data[0]);
        tree.s = data[1];
        tree.t = std::vector<Node>(N*2, Node());

        for(int i=2; i<data.size(); i++){
            if(data[i] == "")
                continue;
            //std::cout << "Creating Node with: " << data[i] << std::endl;
            Node node = Node::from_string(data[i]);
            tree.t[node.id] = node;    
        }

        return tree;
    }

};

#endif