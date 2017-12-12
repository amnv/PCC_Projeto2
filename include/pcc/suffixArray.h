#ifndef SUFFIX_ARRAY
#define SUFFIX_ARRAY

#include <bits/stdc++.h>
using namespace std;

class Tripla
{
public:
	int first, second, third;
	static Tripla make_tripla(int a, int b, int c);
};

class SuffixArray 
{
private:
    vector<int> suftab;
    string path_pattern;
public:
    vector<int> buildSuffixTab(string text);
    map<string, int> buildSuffixArray(string text);
    void count(string path, string pattern, vector<int> suffixtab);
    void count(string path, vector<int> suffixtab);
    void occ(string path, string pattern, vector<int> suffixtab);
    void occ(string path, vector<int> suffixtab);

    int lp(string pattern, string text);
    int rp(string pattern, string text);
    vector<int> getSuffixTab();
    int lexcmp(string a, string b, int m);
    void debug();
    vector<int> search(string text, string pattern);

    void setPattern(string path);
    vector<int> search(string text, string pattern, vector<int> Llcp, vector<int> Rlcp);
    vector<vector<int> > build_P(string text);
    vector<int> sarr_from_P(vector<int> p);
    void fillLlcpRlcp(string txt, vector<int> sarr, int l, int r, vector<int> Llcp, vector<int> Rlcp, vector<int> p);
    int lcp(vector<string> x, vector<string> y);
    vector<Tripla>* rsort(vector<Tripla> *v, int n);

    string to_string(vector<int> v);
    vector<int> from_string(string s);
};

#endif