#ifndef MANAGER
#define MANAGER

#include <string>
#include <vector>

using namespace std;

void indexer(string file, string indexType, string compressType);

void searcher(string file, string pattern, string patterFile, bool count);

vector<string> split(string s, char d);

#endif