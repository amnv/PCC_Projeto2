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

class SuffixTree{
public:
    static const int N = 112345;
    int nodeid;
    std::string s;
    std::vector<Node> t;
    bool print_tree;

    SuffixTree(bool printTree = false){
        nodeid = 1;
        //t = std::vector<Node>(N*2, Node());
        print_tree = printTree;
        //t.push_back(Node());
    };
    
    ~SuffixTree(){};

    int new_node(int L, int R, int P){
        t[nodeid] = Node(nodeid, L, R, P);
        return nodeid++;
    };

    void print_cst(Node root, int level, std::string text){
        //std::cout << "root: " << root.r << std::endl;
        for(int i=0; i<2*level; i++){
            // std::cout << " ";
        }
        // std::cout << "[id=" << root.id << " l=" << root.l << " r=" << root.r << " chd=" << root.chd.size();

        int len = std::min(root.r, static_cast<int>(text.size()));
        len = len == -1 ? text.size() : len;
        len = len - root.l;
        // std::cout << " len=" << len;
        // std::cout << " text=" << text.substr(root.l, root.len());
        // std::cout << " p=" << root.p;
        // Nao faco ideia do que o slink eh
        // std::cout << " slink=";
        // std::cout <<  "]" << std::endl;


        for(std::map<char,int>::iterator iter = root.chd.begin(); iter != root.chd.end(); iter++){
            // print_cst(t[iter->second], level+1, text);
        }
    };

    bool build_sufix_tree(std::string text){
        if(text.size() == 0 || text == "\n")
            return false;

        t = std::vector<Node>(text.size()*2, Node());
        // Adiciona um caractere que nao aparece na string em nenhum lugar (nao ta no
        // alfabeto) no final para garantir que cada sufixo vai ter sua propria folha
        // Isso garante que nenhum sufixo eh prefixo de outro sufixo
        s = text;// + '$';

        for(int i=0; i<s.size(); i++){
            //std::cout << "i=" << i << " c=" << s[i] << std::endl;
            //cn eh o cara q eu to analisando
            //cd eh o index do caractere atual
            int cn = 0, cd = 0;

            for(int j=i; j<s.size(); j++){
                // Se eu to em um vertice e nao tenho esse filho
                if(cd == t[cn].len() && !t[cn].chd.count(s[j])){
                    //std::cout << "i=" << i << " c=" << s[i] << " cn=" << cn << " cd=" << cd << " if1" << std::endl;

                    t[cn].chd[s[j]] = new_node(j, s.size()-1, cn);
                    break;
                // Se eu to no meio e uma aresta (eu nao analisei todos os caracteres dessa
                // aresta) e o caractere atual eh diferente do cara q eu to tentando adicionar (s[j])
                // entao eu quebro a aresta em duas (crio mid)
                }else if(cd < t[cn].len() && s.substr(t[cn].l+cd, 1)[0] != s[j]){
                    //std::cout << "i=" << i << " c=" << s[i] << " cn=" << cn << " cd=" << cd << " if2" << std::endl;
                    int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].p);
                    t[mid].chd[s[j]] = new_node(j, s.size()-1, mid);
                    t[mid].chd[s.substr(t[cn].l+cd, 1)[0]] = cn;
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
                    //std::cout << "i=" << i << " c=" << s[i] << " cn=" << cn << " cd=" << cd << " if3" << std::endl;
                    cn = t[cn].chd[s[j]];
                    cd = 0;
                }
                cd++;
            }

        }

        if(print_tree)
            print_cst(t[0], 0, s);

        return true;
    };

    int check_pattern(std::string pat, bool count = false){
        if(count){
            return doTraversal(pat, t[0], 0);
        }

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
                return -1;
            }

        }

        //std::cout << "pattern found" << std::endl;
        return 1;
    };

    int traverseEdge(std::string str, int idx, int start, int end)
    {
        int k = 0;
        //Traverse the edge with character by character matching
        for(k=start; k<=end && idx < str.size(); k++, idx++)
        {
            if(s[k] != str[idx])
                return -1;  // mo match
        }
        if(idx == str.size())
            return 1;  // match
        return 0;  // more characters yet to match
    }
     
    int doTraversalToCountLeaf(Node n)
    {
        // se eh uma folha
        if(n.chd.size() == 0)
        {
            return 1;
        }
        int count = 0;
        int i = 0;
        for(std::map<char,int>::iterator iter = n.chd.begin(); iter != n.chd.end(); iter++)
        {
            count += doTraversalToCountLeaf(t[iter->second]);   
        }
        return count;
    }
     
    int countLeaf(Node n)
    {
        return doTraversalToCountLeaf(n);
    }
     
    int doTraversal(std::string str, Node n, int idx)
    {
        //std::cout << n.id << ", " << idx << ", " << n.len() << std::endl;
        int res = -1;
        if(n.r != -1)
        {
            //std::cout << "traverse " << n.id << ", " << idx << ", " << n.len() << std::endl;
            res = traverseEdge(str, idx, n.l, n.r);
            if(res == -1)
                return -1;
            if(res == 1)
            {
                if(n.chd.size() == 0)
                    return 1;
                else
                    return countLeaf(n);
            }
        }
        idx = idx + n.len();

        if(n.chd.count(str[idx]))
            return doTraversal(str, t[n.chd[str[idx]]], idx);
        else
            return -1;
    }

    std::string to_string(){
        std::string treestr = "i=" + std::to_string(nodeid) + "\n";
        treestr += "s=" + s + "\n";

        for(int i=0; i<t.size(); i++){
            if(t[i].id == 0 && i!=0)
                continue;
            treestr += "n=" + t[i].to_string() + "\n";
        }

        return treestr;
    }

    static SuffixTree from_string(std::string treestr){
        std::vector<std::string> data = split(treestr, "\n");
        SuffixTree tree;

        for(int i=0; i<data.size(); i++){
            //std::cout << "i=\"" << i << "/" << data.size() << "\" Data[i]= \"" << data[i] << "\" Size:" << data[i].size() << std::endl;
            if(data[i].size() == 0)
                continue;

            //std::cout << "Extracting header" << std::endl;
            //header
            std::string datatype = data[i].substr(0, 2);
            //std::cout << "header=" << datatype << std::endl;

            //std::cout << "Extracting content" << std::endl;
            //content
            std::string datasubs = data[i].substr(2, data[i].size()-2);
            //std::cout << "content=" << datasubs << std::endl;

            if(datatype == "i="){
                //std::cout << "  inserindo o id da tree" << std::endl;
                tree.nodeid = std::stoi(datasubs);
                //std::cout << "  done" << std::endl;
            }else if(datatype == "s="){
                //std::cout << "  inserindo a string da tree" << std::endl;
                tree.s = datasubs;
                if(tree.s.size() == 0)
                    std::cout << "tree string is empty" << std::endl;
                //std::cout << "  done" << std::endl;
                //std::cout << "  criando vector de nodes da tree" << std::endl;
                tree.t = std::vector<Node>(tree.s.size()*2, Node());
                //std::cout << "  done" << std::endl;
            }
            else if(datatype == "n="){
                Node node = Node::from_string(datasubs);
                //std::cout << "  inserindo um node com id=" << node.id << " numa tree de size=" << tree.t.size() << std::endl;
                tree.t[node.id] = node;
                //std::cout << "  done" << std::endl;   
            }
        }

        return tree;
    }

};

#endif