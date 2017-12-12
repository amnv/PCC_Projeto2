#include <pcc/manager.h>
#include <iostream>
#include <pcc/compress.h>
#include <regex>
#include <pcc/filereader.h>
#include <vector>
#include <pcc/suffixArray.h>
#include <ukkonen_sufix_tree.h>
// std::string text = "Let me split this into words";
// std::vector<std::string> results;

using namespace std;

auto reg = [](string ex, string& str) {
    regex rgx(ex);
    smatch match;
    if (regex_search(str, match, rgx)) {
        str = match[1];
        return true;
    }
    return false;
};

vector<string> split(string s, char d) {
    vector<string> r;
    int m = 0;
    s+= d;
    for (int i=0; i<s.size(); i++) {
        cout << s[i] << endl;
        if (s[i] == d) {
            r.push_back(s.substr(m, i-m));
            m = i + 1;
        }
    }
    return r;
}

void indexer(string file, string indexType, string compressType) {

    vector<SuffixTree> v;
    string all = "";
    FileReader* r = new FileReader(file);
    if (indexType == "array") {
        //chama o array suffix
        SuffixArray s;
        string line;
        string texto;
        while (r->getLine(line)) {
            texto += line;
        }
        vector<int> array = s.buildSuffixTab(texto);
        all = s.to_string(array);
        all += "IIiseparadoriII";
        all += texto;

    } else { //ja passou pela verificacao no main (array | suffix)
        //chama o suffix tree

        string line;
        while (r->getLine(line)) {
            SuffixTree s;
            s.build_sufix_tree(line);
            v.push_back(s);
        }
        
        for (int i=0; i<v.size(); i++) {
            all += v[i].to_string() + (char) 0;
        }

    }
    
    
    //TEMPORARIO PARA TESTAR COMPRESSAO
    // {
    //     FileReader* r = new FileReader(file);
    //     string line;
    //     all = "";
    //     while (r->getLine(line)) {
    //         all += line + "\n";
    //     }
    // }
    //FIM TEMPORARIO

    
    //saida do algoritmo eh entao toda serializada e eh passada para a string all
    reg("(.*?)[.][a-zA-Z0-9]*$", file);
    Compress::create(file + ".idx", all, indexType, compressType);
}

void searcher(string file, string pattern, string patternFile, bool count) {
    // cout << "Modo de busca " << endl;
    string suffix = "";
    string uncompress = Compress::extract(file, suffix);
    cout << uncompress << endl;
    if (suffix == "array") {
        string array = uncompress, texto = uncompress;
        reg("(.*)IIiseparadoriII", array);
        reg("IIiseparadoriII(.*)", texto);
        SuffixArray s;
        vector<int> v = s.from_string(array);
        

        if (!patternFile.empty()) { //passou
            s.setPattern(patternFile);
            if (count)
                s.count(texto, v);
            else {
                vector<string> lines = split(texto, ' ');
                for (int i=0; i<lines.size(); i++){
                    string line = lines[i]; 
                    s.occ(line, v);
                }
                s.reset();
            }
        } else {
            if (count)
                s.count(texto, pattern, v);
            else {
                vector<string> lines = split(texto, ' ');
                for (int i=0; i<lines.size(); i++){
                    string line = lines[i];
                    s.occ(line, pattern, v);
                }
                s.reset();
            }
        }
        // s.search(texto, patternFile);

    } else {
        vector<string> suffix = split(uncompress, (char) 0);
        FileReader* r;
        if (!patternFile.empty()) {
            r = new FileReader(patternFile);
        }
        string pat = "";
        bool one = true;
        while ((one && patternFile.empty()) || (!patternFile.empty() && r->getLine(pat)) ) {
            long c = 0; //contador
            if (patternFile.empty()) {
                pat = pattern;
                one = false;
            }
            for (int i=0; i<suffix.size(); i++) {
                SuffixTree t = SuffixTree::from_string(suffix[i]);
                if (!count && t.check_pattern(pat))
                    cout << t.s << endl;
                if (count) {
                    c += t.check_pattern(pat, true);
                }
            }
            if (count) {
                cout << c << endl;
            }
        }
    
        
    }
    


    //o metodo extract retorna uma string, essa deve ser deserializada 
    // e entao pode ser usada como se não houvesse compressão

    //chama o buscador aqui, se precisar diferenciar o tipo do indexador (array,tree) pode
    // colocar junto c a serializacao uma sinalizacao e entao resgata-la aqui

}