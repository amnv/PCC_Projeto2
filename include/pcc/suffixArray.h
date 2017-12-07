#ifndef SUFFIX_ARRAY
#define SUFFIX_ARRAY

#include <bits/stdc++.h>
using namespace std;

class SuffixArray 
{
private:
    vector<int> suftab;
    string text;
    string pattern;
public:
    vector<int> buildSuffixTab(string text);
    map<string, int> buildSuffixArray(string text);
    void search(string text, string pattern);
    void count(map<string, int> suffixArray, string pattern);
    int lp(string pattern, string text);
    int lr(string pattern, string text);
    vector<int> getSuffixTab();
    int lexcmp(string a, string b, int m);
    void debug();
};

#endif