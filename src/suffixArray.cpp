#include "../include/pcc/suffixArray.h"
#include<bits/stdc++.h>

using namespace std;

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

void SuffixArray::search(string text, string pattern)
{
    
    int lp = this->lp(pattern, text);
    int lr = this->lr(pattern, text);


}

int SuffixArray::lexcmp(string a, string b, int m)
{
    a = a.size() <= m ?a : a.substr(0, m);
    b = b.size() <= m ?b : b.substr(0, m);

    if (a < b) return -1;
    else if ( b < a) return 1;

    return 0;
}

int SuffixArray::lp(string pattern, string text)
{
    int m = pattern.size();
    int n = text.size();
    int r = n -1;

    if (this->lexcmp(pattern, text.substr(this->suftab[0]), m) <= 0)
        return 0;
    else if (this->lexcmp(text.substr(this->suftab[0]), pattern, m) < 0)
        return n;
    else 
    {
        int l = 0;

        while ((r-1) > 1)
        {
            int h = (l+r)/2;
            if (this->lexcmp(pattern, text.substr(this->suftab[h]), m) <= 0)
                r = h;
            else l = h;
        }
    }

    return r;
}
    
int SuffixArray::lr(string pattern, string text)
{
    int n = text.size();
    int m = pattern.size();


    if (this->lexcmp(text.substr(this->suftab[n-1]), pattern, m)<=0)
        return n-1;
    if (this->lexcmp(pattern, text.substr(this->suftab[n-1]), m) < 0)
        return -1;
    
    int l = 0;
    int r = n-1;

    while((r-1) > 1)
    {
        int h = (l+r)/2;
        if (this->lexcmp(text.substr(this->suftab[h]), pattern, m) <= 0)
            l = h;
        else
            r = h;  
    }
    return l;
}

void SuffixArray::debug()
{
    string t = "mississippi$";
    //teste suffixArray
    cout << "teste suffixArray" << endl;
    map<string, int> ret = this->buildSuffixArray(t);
    for(map<string, int>::iterator i = ret.begin(); i != ret.end(); i++)
    {
        cout << i->first << " " << i->second << endl;
    }

    //teste suffix tab
    cout << "teste suffix tab" << endl;
    this->buildSuffixTab(t);
    for (int i = 0; i < this->suftab.size(); i++)
    {
        cout << this->suftab[i] << endl;
    }
}

vector<int> SuffixArray::getSuffixTab()
{
    return this->suftab;
}