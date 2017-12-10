#ifndef SUFFIX_ARRAY
#define SUFFIX_ARRAY

#include <bits/stdc++.h>
using namespace std;

class SuffixArray 
{
private:
    vector<int> suftab;
public:
    vector<int> buildSuffixTab(string text);
    map<string, int> buildSuffixArray(string text);
    void count(string text, string pattern);
    void occ(string text, string pattern);
    int lp(string pattern, string text);
    int rp(string pattern, string text);
    vector<int> getSuffixTab();
    int lexcmp(string a, string b, int m);
    void debug();


    vector<int> search(string text, string pattern, vector<int> Llcp, vector<int> Rlcp);
    vector<vector<int> > build_P(string text);
    vector<int> sarr_from_P(vector<int> p);
    void fillLlcpRlcp(string txt, vector<int> sarr, int l, int r, vector<int> Llcp, vector<int> Rlcp, vector<int> p);
    int lcp(vector<string> x, vector<string> y);
    int rsort(vector<pair<int, pair<int, int> > > v, int n);
};

#endif