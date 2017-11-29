#include <pcc/manager>
#include <iostream>

using namespace std;

Manager::Manager(string file, string mode, string indexType, string pattern, string patternFile, bool count) {
    cout << file << mode << indexType << pattern << patternFile << count;
    if (mode == "index") {
        // Indexer i(file, indexType);

    } else {
        // Searcher s(file, pattern, patternFile, count);

    }
}
