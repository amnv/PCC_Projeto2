#ifndef SUFFIX_ARRAY
#define SUFFIX_ARRAY

#include<bits/stdc++.h>
using namespace std;

class SuffixArray 
{
private:
    vector<int> suftab;
    vector<string> SuffixArray;
    string text;
    string pattern;
public:
    void buildArray();
    int search();
};

#endif