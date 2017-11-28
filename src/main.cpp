#include <bits/stdc++.h>
#include <getopt.h>

using namespace std;

int readParameters(int argc, char* argv[], bool& help, int& count, string& patternFile) {
    
    struct option extendedOptions[] = {
        {"pattern", required_argument, 0, 'p'},
        {"count", required_argument, 0, 'c'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    int c;
    while( ( c = getopt_long(argc, argv, "hc:p:", extendedOptions, NULL) ) != -1 ) {
        switch (c) {
            case 'h':
                help = true;
                break;
            case 'c':
                count = atoi(optarg);
                break;
            case 'p':
                patternFile = optarg;
                break;
        }
    }

}


int main(int argc, char* argv[]) {
    bool help = 0;
    int count = 0;
    string patternFile = "";
    readParameters(argc, argv, help, count, patternFile);

    if (!patternFile.empty())
        cout << "pattern file " << patternFile << endl;

    if (count)
        cout << "count " << count << endl;

    if (help) {
        cout << 
        "USO: " << argv[0] << " [OPCOES] {PADRAO|-p FILE} ARQUIVO\n\
        OPCOES:\n\
        -p --pattern patternfile\n\
        -c --count\n\
        -h --help!\n\
        \n";

        return 0;
    }    

    return 0;
}