#include <iostream>
#include <getopt.h>
#include <pcc/manager>

using namespace std;

int readParameters(int argc, char* argv[], string& mode, string& pattern, string& file, bool& help, bool& count, string& patternFile, string& index) {

    struct option extendedOptions[] = {
        {"pattern", required_argument, 0, 'p'},
        {"count", no_argument, 0, 'c'},
        {"indextype", required_argument, 0, 'i'},        
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    int c;
    while( ( c = getopt_long(argc, argv, "hcp:i:", extendedOptions, NULL) ) != -1 ) {
        switch (c) {
            case 'h':
                help = true;
                break;
            case 'c':
                count = true;
                break;
            case 'p':
                patternFile = optarg;
                break;
            case 'i':
                index = optarg;
                break;
        }
    }

    if (argc > optind)
        mode = argv[optind++];

    if (mode != "index" && argc > optind && patternFile.empty()) { //se nao passar o file pattern
        pattern = argv[optind++];
    }
    if (argc > optind)
        file = argv[optind++];

}

void debugParams(string mode, string pattern, string file, bool help, bool count, string patternFile, string index) { 
    if (!mode.empty())
        cout << "Mode: " << mode << endl;
    
    if (!pattern.empty())
        cout << "Pattern: " << pattern << endl;

    if (!patternFile.empty())
        cout << "PatternFile: " << patternFile << endl;

    if (!file.empty())
        cout << "File: " << file << endl;

    if (help)
        cout << "Help ativado!" << endl;

    if (count)
        cout << "Count ativado!" << endl;

    if (!index.empty())
        cout << "IndexType: " << index << endl;
} 

int main(int argc, char* argv[]) {
    string file = "", indexType = "", pattern = "", mode = "";
    bool help = false, count = false;
    string patternFile = "";
    readParameters(argc, argv, mode, pattern, file, help, count, patternFile, indexType);
    
    // debugParams(mode, pattern, file, help, count, patternFile, indexType);
    if (help) {
        cout << 
        "USO: " << argv[0] << " index [OPCOES] ARQUIVO\n     " << argv[0] << " search [OPCOES] {PADRAO|-p FILE} ARQUIVO\n\n\
OPCOES (index):\n\
  -i, --indextype {tree|array} \t Escolha do algoritmo de indexacao.\n\
  -h, --help \t\t\t Mostra esse help.\n\n\
OPCOES (search):\n\
  -p, --pattern FILE \t\t Le os padroes de um arquivo.\n\
  -c, --count \t\t\t Modo de contagem de ocorrencias.\n\
  -h, --help \t\t\t Mostra esse help.\n\
";

        return 0;
    }

    if (mode != "index" && mode != "search") {
        cout << "Modo invalido. Tente index ou search." << endl;
        return 1;
    }

    if (file.empty()) {
        cout << "Falta arquivo." << endl;
        return 1;
    }

    Manager m (file, mode, indexType, pattern, patternFile, count);
    
    return 0;
}