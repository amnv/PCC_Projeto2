#ifndef MANAGER
#define MANAGER

#include <string>

using namespace std;

void indexer(string file, string indexType, string compressType);

void searcher(string file, string pattern, string patterFile, bool count);

#endif