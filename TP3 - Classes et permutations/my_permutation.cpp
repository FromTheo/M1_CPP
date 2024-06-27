#include "my_permutation.hpp"

using namespace std; 

long int pgcd(long int a, long int b)
{ 
    while(b!=0)
    { 
        long int temp=b;
        b=a%b;
        a=temp;
    }
    return a; 
}

long int ppcm(long int a, long int b)
{ 
    return a*b/pgcd(a,b);
}

Permutation::Permutation(int n) : n(n), images(n)
{
    std::iota(images.begin(), images.end(), 0); 
}

std::list<int> Permutation::fixed_points() const
{
    std::list<int> L; 
    for(int i = 0; i < size(); ++i)
    {
        if(images[i] == i) L.push_back(i); 
    }   
    return L; 
}

Permutation Permutation::inverse() const
{
    std::vector<int> res(size()); 
    for(int i = 0; i < size(); ++i)
    {
        res[images[i]] = i; 
    }
    return Permutation(res); 
}

std::list<Cycle> Permutation::cycles() const
{   
    std::list<Cycle> L; 
    std::set<int> S; 
    for(int i = 0; i < n; ++i) {S.insert(i);}
    while(!S.empty())
    {
        int x = *S.begin();
        S.erase(S.begin()); 
        if(images[x] != x)
        {
            Cycle c; 
            c.add_last_point(x); 
            int suivant = images[x]; 
            while(suivant != x)
            {
                S.erase(suivant); 
                c.add_last_point(suivant); 
                suivant = images[suivant]; 
            }
            L.push_back(c); 
        }

    }
    return L;
}

long int Permutation::order() const
{
    std::list<Cycle> L = cycles(); 
    return std::accumulate(L.begin(), L.end(), 1, [](int acc, const Cycle &c)
    {
        return ppcm(acc,c.order()); 
    });
}

std::ostream& operator<<(std::ostream& out, const Permutation& P)
{
    out << P.n << " :"; 
    for(const int& i : P.images)
    {
        out << " " << i; 
    } 
    return out; 
}

std::istream& operator>>(istream& in, Permutation& P)
{ 
    int n; 
    in >> n;
    P.n = n; 
    char garbage;
    in >> garbage; 
    vector<int> res(n); 
    for(int i=0; i<n; i++)
    {
        int value; 
        in >> value; 
        res[i] = value; 
    }
    P.images = res; 
    return in;
}

Permutation operator*(const Permutation& s,  const Permutation& t)
{   
    std::vector<int> res(std::max(s.n, t.n)); 
    for(int i = 0; i < res.size(); ++i)
    {
        res[i] = s[t[i]]; 
    }
    return Permutation(res); 
}

std::ostream& operator<<(std::ostream& out, const Cycle& c)
{
    out << "[ ";
    for(const int& i : c.elem)
    {
        out << i << " ";
    }
    out << "]"; 
    return out; 
}

bool operator<(const Cycle& c, const Cycle& d)
{ 
    if(c.order()<d.order())
    { 
        return true; 
    }
    else if(c.order() > d.order())
    { 
        return false;
    }
    else 
    {
        return lexicographical_compare(c.elem.begin(),c.elem.end(), d.elem.begin(), d.elem.end());
    }
}

int Cycle::operator[](int i) const
{
    if(find(i) == elem.end()) return i;
    else if(*find(i) == *(elem.end()-1))
    {
        return elem.front();
    }
    else
    {
        return *find(i)+1;
    }
}

Cycle Cycle::inverse() const
{ 
    Cycle resultat(*this);
    for(int i=1; i<order(); i++)
    { 
        resultat.elem[i]=elem[order()-1];
    }
    return resultat;
}

list<Cycle> Cycle::cycles() const
{ 
    return list<Cycle>(1,*this);
}