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
        // cout << s[i] << endl;
        if (s[i] == d) {
            // cout << "de boa" << endl;
            r.push_back(s.substr(m, i-m));
            // cout << "oh no" << endl;
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
            texto += line + "\n";
        }
        // cout << texto << endl;
        vector<int> array = s.buildSuffixTab(texto);
        all = s.to_string(array);
        all += "IIiseparadoriII";
        all += texto;
        // cout << "text " << texto << endl;
        // cout << all << endl;

    } else { //ja passou pela verificacao no main (array | suffix)
        //chama o suffix tree
        string line;
        int i=0;
        while (r->getLine(line)) {
            //cout << "line " << line << endl;
            // std::cout << "Building sufix tree n=" << i << " lsize=" << line.size() << std::endl;
            SuffixTree s;
            if(s.build_sufix_tree(line)){
                //v.push_back(s);
                // std::cout << "Converting sufix tree to string" << std::endl;
                all += s.to_string() + (char) 0;
                //v.erase(v.begin());
                i++;
            }
        }
        //while(v.size() > 0) {
        //    all += v[0].to_string() + (char) 0;
        //    v.erase(v.begin());
        //}

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

    // cout << all << endl;
    //saida do algoritmo eh entao toda serializada e eh passada para a string all
    reg("(.*?)[.][a-zA-Z0-9]*$", file);
    Compress::create(file + ".idx", all, indexType, compressType);
}

void searcher(string file, string pattern, string patternFile, bool count) {
    // cout << "Modo de busca " << endl;
    string suffix = "";
    string uncompress = Compress::extract(file, suffix);
    // cout << uncompress << suffix << endl;
    if (suffix == "a") {
        string array = uncompress, texto = uncompress;
        reg("(.*)IIiseparadoriII", array);
        string opa = "IIiseparadoriII";
        // for (int i=0; i< uncompress; i++ ){
            int posi = uncompress.find(opa);
            texto = uncompress.substr(posi + opa.size());
        // }
        // reg("IIiseparadoriII(.*\\s.*)", texto);
        // cout << "text " << texto << endl;
        SuffixArray s;
        vector<int> v = s.from_string(array);


        if (!patternFile.empty()) { //passou
            s.setPattern(patternFile);
            if (count)
                s.count(texto, v);
            else {
                // vector<string> lines = split(texto, '\n');
                s.occ(texto, v);
                s.reset();
            }
        } else {
            if (count)
                s.count(texto, pattern, v);
            else {
                // cout << "here '" << texto << "'" << endl;
                // vector<string> lines = split(texto, '\n');
                // cout << "opa" << endl;
                // for (int i=0; i<lines.size(); i++){
                //     string line = lines[i];
                //     cout << "123" << endl;
                s.occ(texto, pattern, v);
                    // cout << "line " << line << endl;
                // }
                // cout << "opa2" << endl;
                // s.reset();
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
        // cout << "aqui tree" << endl;
        while ((one && patternFile.empty()) || (!patternFile.empty() && r->getLine(pat)) ) {
            long c = 0; //contador
            if (patternFile.empty()) {
                pat = pattern;
                one = false;
            }
            for (int i=0; i<suffix.size(); i++) {
                if(suffix[i].size() == 0 || suffix[i] == "\n")
                    continue;
                
                SuffixTree t = SuffixTree::from_string(suffix[i]);
                if (!count && t.check_pattern(pat) == 1)
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