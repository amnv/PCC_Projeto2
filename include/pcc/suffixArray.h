#ifndef SUFFIX_ARRAY
#define SUFFIX_ARRAY

#include <bits/stdc++.h>
using namespace std;
/**
 * author Allyson Manoel
 **/
class Gambe
{
public:
    int ini; int fim; string line;
    static Gambe make_gambe(int,int, string);
};

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
    int ini, fim;
public:
    SuffixArray();
    vector<Gambe> gambe(string text);
    vector<int> buildSuffixTab(string text);
    map<string, int> buildSuffixArray(string text);
    void count(string path, string pattern, vector<int> suffixtab);
    void count(string path, vector<int> suffixtab);
    // bool occ(vector<string> lines, string pattern, vector<int> suffixtab);
    bool occ(string text, string pattern, vector<int> suffixTab);
    bool occ(string text, vector<int> suffixtab);
    int lp(string pattern, string text);
    int rp(string pattern, string text);
    vector<int> getSuffixTab();
    int lexcmp(string a, string b, int m);
    void debug();
    vector<int> search(string text, string pattern);
    string findLine(vector<Gambe> g, int s);
    void setPattern(string path);
    vector<int> search(string text, string pattern, vector<int> Llcp, vector<int> Rlcp);
    vector<vector<int> > build_P(string text);
    vector<int> sarr_from_P(vector<int> p);
    void fillLlcpRlcp(string txt, vector<int> sarr, int l, int r, vector<int> Llcp, vector<int> Rlcp, vector<int> p);
    int lcp(vector<string> x, vector<string> y);
    vector<Tripla>* rsort(vector<Tripla> *v, int n);

    string to_string(vector<int> v);
    vector<int> from_string(string s);
    void reset();
};

#endif