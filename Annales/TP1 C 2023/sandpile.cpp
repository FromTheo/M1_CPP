#include <algorithm>        //std::fill

#include "sandpile.hpp"

using namespace std; 


Sandpile::Sandpile(int m, int n, int k) : m(m), n(n), terrain(n*m), nb_ebouls(n*m)
{
    std::fill(terrain.begin(), terrain.end(), k); 
    if(k >= 4)
    {
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n ; ++j)
            {
                next_ebouls.push_back(upair(i,j)); 
            }
        }
    }
}

Sandpile::Sandpile(int m, int n, std::map<upair,unsigned>& M) : m(m), n(n), terrain(n*m), nb_ebouls(n*m)
{
    for_each(M.begin(), M.end(), [&](const std::pair<upair,unsigned>& p)
    {
        terrain[p.first.first+p.first.second*m]+=p.second; 
        if(terrain[p.first.first+p.first.second*m]>=4)
        {
            next_ebouls.push_back(p.first); 
        }
    });
}

void Sandpile::incr_and_test(upair p)
{
    h(p)++;
    if(h(p) >= 4) next_ebouls.push_back(p); 
} 

std::list<upair> Sandpile::voisins(upair p) const
{
    int i = p.first; 
    int j = p.second; 
    std::list<upair> L;
    if(i+1 < m) L.push_back(upair(i+1,j)); 
    if(j+1 < n) L.push_back(upair(i,j+1));
    if(i > 0) L.push_back(upair(i-1,j));
    if(j > 0) L.push_back(upair(i,j-1)); 
    return L;
}   

void Sandpile::eboul(upair p)
{
    if(h(p) >= 4)
    {
        nb_ebouls[p.first + p.second * m]++;
        h(p) -= 4;
        for(const upair& v : voisins(p))
        {
            incr_and_test(v); 
        }
    }
}

int Sandpile::stabil()
{
    int compteur = 0; 
    while(!next_ebouls.empty())
    {
        upair p = next_ebouls.front(); 
        eboul(p); 
        compteur++; 
        next_ebouls.pop_front(); 
    }
    return compteur; 
}

unsigned Sandpile::nb_total_ebouls() const
{
    unsigned resultat = accumulate(nb_ebouls.begin(), nb_ebouls.end(), 0, [](unsigned acc, const unsigned& i)
    {
        return acc + i;
    });
    return resultat; 
}

unsigned Sandpile::volume_total() const
{
    unsigned resultat = accumulate(terrain.begin(), terrain.end(), 0, [](unsigned acc, const unsigned& i)
    {
        return acc + i;
    });
    return resultat; 
}


std::ostream& operator<<(std::ostream& out, const Sandpile& S)
{
    for(int j = 0; j < S.n ; ++j)
    {
        for(int i = 0; i < S.m; ++i)
        {
            out << S(i,j); 
        }
        out << endl; 
    }
    return out; 
}

Sandpile operator+(const Sandpile& s, const Sandpile& t)
{
    Sandpile resultat(s.m, s.n,0); 
    for(int i = 0; i < s.m; ++i)
    {
        for(int j = 0; j< s.n; ++j)
        {
            resultat.terrain[i+j*s.m] += s.terrain[i+j*s.m] + t.terrain[i+j*s.m]; 
        }   
    }
    resultat.stabil(); 
    std::fill(resultat.nb_ebouls.begin(), resultat.nb_ebouls.end(), 0);
    return resultat;
}