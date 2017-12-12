#include <bits/stdc++.h>

#include "../include/pcc/suffixArray.h"
#include "../include/pcc/filereader.h"

using namespace std;

Tripla Tripla::make_tripla(int a, int b, int c)
{
	Tripla t;
    t.first = a; t.second = b; t.third = c;
	return t;
}

map<string, int> SuffixArray::buildSuffixArray(string text)
{
    map<string, int> ret;

    for(int i = 0; i < text.size(); i++)
    {
        ret[text.substr(i)] = i;
    }

    return ret;
}

vector<int> SuffixArray::buildSuffixTab(string text)
{
    map<string, int> suffixArray = this->buildSuffixArray(text);
    for(map<string, int>::iterator it = suffixArray.begin(); it != suffixArray.end(); it++)
    {
        this->suftab.push_back(it->second);
    }

    return this->suftab;
}

vector<int> SuffixArray::search(string text, string pattern)
{
  vector<int> sa;
    int lp = this->lp(pattern, text);
  //  cout << "saiu lp" << endl;
    int rp = this->rp(pattern, text);
    //cout << "saiu rp" << endl;
    //cout << "lp " << lp << " lr " << rp << endl;
    if (lp > rp) return sa;
    
    for(int i = lp; i <= rp; i++)
        sa.push_back(this->suftab[i]);
    sort(sa.begin(), sa.end());
    return sa;
}

vector<int> SuffixArray::search(string text, string pattern, vector<int> Llcp, vector<int> Rlcp)
{
    vector<int> sa;
    int lp = this->lp(pattern, text);
    cout << "saiu lp" << endl;
    int rp = this->rp(pattern, text);
    cout << "saiu rp" << endl;
    
    if (lp > rp) return sa;
    
    for(int i = lp; i <= rp; i++)
        sa.push_back(this->suftab[i]);
    sort(sa.begin(), sa.end());
    return sa;
}

int SuffixArray::lexcmp(string a, string b, int m)
{
   /** a = a.size() <= m ?a : a.substr(0, m);
    b = b.size() <= m ?b : b.substr(0, m);

    if (a < b) return -1;
    if (b < a) return 1;
    **/

    return a.compare(0,m, b, 0, m);
}

int SuffixArray::lp(string pattern, string text)
{
    int n = text.size();
    int m = pattern.size();
    int r = n -1;

    if (this->lexcmp(pattern, text.substr(this->suftab[0]), m) <= 0)
        return 0;
    if (this->lexcmp(text.substr(this->suftab[n-1]), pattern, m) < 0)
        return n;

    int l = 0;

    while ((r - l) > 1)
    {
        int h = (l+r)/2;
        if (this->lexcmp(pattern, text.substr(this->suftab[h]), m) <= 0)
            r = h;
        else l = h;
    }
    
    return r;
}
    
int SuffixArray::rp(string pattern, string text)
{
    int n = text.size();
    int m = pattern.size();


    if (this->lexcmp(text.substr(this->suftab[n-1]), pattern, m) <= 0)
        return n-1;
    if (this->lexcmp(pattern, text.substr(this->suftab[0]), m) < 0)
        return -1;
    
    int l = 0;
    int r = n-1;

    while((r - l) > 1)
    {
        int h = ceil((l+r)/2);
        if (this->lexcmp(text.substr(this->suftab[h]), pattern, m) <= 0)
            l = h;
        else
            r = h;  
    }
    return l;
}

vector<int> SuffixArray::getSuffixTab()
{
    return this->suftab;
}

vector<Tripla>* SuffixArray::rsort(vector<Tripla> *v, int n)
{
    cout << "to tentando entender" << endl;
    return v;
}

vector<vector<int> > SuffixArray::build_P(string text)
{
    cout << "chegou aqui 1" << endl;
    vector<vector<int> > p;
    int n = text.size();
    if (n == 1) 
    {
        vector<int> a;
        a.push_back(1);
        p.push_back(a);
        return p;
    }

    vector<vector<int> > bucket(256);

    for (int i = 0; i < n; i++)
    {
        bucket[text[i]].push_back(i);
    }

    cout << "chegou aqui 2" << endl;
    vector<int> p0(n, 0);
    int rank = 1;

    for (int i = 0; i < 256; i++)
    {
        if(!bucket[i].empty())
        {
            //cout << "por aqui " << i << endl;
            for (int j = 0; j < bucket.size(); j++)
            {
                p0[j] = rank;
            }
            rank++;
        }
    }
    p.push_back(p0);
    cout << "chegou aqui 3" << endl;
    int endLoop = (int) ceil(log2(n)) + 1;
    for (int k = 1; k < endLoop; k++)
    {
        int j = pow(2, k-1);
        vector<Tripla> v;
        for (int i = 0; i < n; i++)
        {
            v.push_back(Tripla::make_tripla(
                p[k-1][i],
                ((i+j) < n) ?p[k-1][i+j] :0,
                i));
        }

        cout << "chegou aqui 4" << endl;
        cout << "valor de n " << n << endl;
      //  rsort(&v, n+1);
        cout << "chegou aqui 5" << endl;
        int r = 1; 
        vector<int> Pk(n, -1);
        Pk[v[0].third] = r;
        for(int i = 1; i < n; i++)
        {
            if ((v[i].first != v[i-1].first)
                && (v[i].second != v[i-1].second)
                && (v[i].third != v[i-1].third))
            {
                r++;
            }
            Pk[v[i].third] = r;
        }
        cout << "chegou aqui 6" << endl;
        p.push_back(Pk);
    }
    return p;
}

void SuffixArray::count(string path, string pattern, vector<int> suffixTab)
{
    FileReader* r = new FileReader(path);
    string line;
    string text;
    while (r->getLine(line))
    {
        text += line;
    }
    this->suftab = suffixTab;
    cout << this->search(text, pattern).size() << endl;
    delete r;
}

void SuffixArray::count(string path, vector<int> suffixtab)
{
    string pattern;
    FileReader file(this->path_pattern);
    while(file.getLine(pattern))
    { 
        this->count(path, pattern, suffixtab);
    }   
}

bool SuffixArray::occ(string path, string pattern, vector<int> suffixTab)
{
    string text;
    FileReader file(path);
    while(file.getLine(text))
    {    
        this->suftab = suffixTab;
        vector<int> v = this->search(text, pattern);

        if (!v.empty())
        {
            cout << text << endl;
        }
    }
}

void SuffixArray::occ(string path, vector<int> suffixtab)
{
    string pattern;
    FileReader file(this->path_pattern);
    while(file.getLine(pattern))
    { 
        this->occ(path, pattern, suffixtab);
    }
}


string SuffixArray::to_string(vector<int> v)
{
   string saida = "";
   stringstream result;
   copy(v.begin(), v.end(), ostream_iterator<int>(result, " "));

    saida = result.str().c_str();
    return saida;
}

vector<int> SuffixArray::from_string(string s)
{
    stringstream iss(s);

    int number;
    vector<int> myNumbers;
    while (iss >> number)
        myNumbers.push_back(number);
    return myNumbers;
}

void SuffixArray::debug()
{
    string t = "thesharkwaskilledduringthenightIthasnoideaofwhatwasgoi123 2157$#@ngonpoorlittleshark@#$.$";
//    vector<vector<int> > p = this->build_P(t);

    //teste suffixArray
    cout << "teste suffixArray" << endl;
    map<string, int> ret = this->buildSuffixArray(t);
    for(map<string, int>::iterator i = ret.begin(); i != ret.end(); i++)
    {
        cout << i->first << " " << i->second << endl;
    }

    //teste suffix tab
    cout << "teste suffix tab" << endl;
    vector<int> v = this->buildSuffixTab(t);
    for (int i = 0; i < this->suftab.size(); i++)
    {
        cout << this->suftab[i] << endl;
    }

    //testando to_string
    cout << "testando to_string" << endl;
    string saida = this->to_string(v);
    cout << saida << endl;

    //testando from_string
    cout << "testando from_string" << endl;
    cout << this->from_string(saida).size() << endl;

    
    // teste achar occ 
    cout << "teste achar occ" << endl;
    string pat = "157$#@";
    vector<int> occ = this->search(t, pat);
    cout << "mostrando ocorrencias" << endl;
    for (int i = 0; i < occ.size(); i++)
        cout << occ[i] << endl;
    
}

void SuffixArray::setPattern(string path)
{
    this->path_pattern = path;
}