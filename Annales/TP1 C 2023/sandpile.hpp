#include <vector>       //std::vector
#include <utility>      //std::pair
#include <list>         //std::list
#include <fstream>
#include <numeric>      //std::accumulate
#include <random> 
#include <map>          //std::map

using upair = std::pair<unsigned,unsigned>;

class Sandpile
{
    private : 
    unsigned m; 
    unsigned n;
    std::vector<unsigned> terrain; 
    std::vector<unsigned> nb_ebouls; 
    std::list<upair> next_ebouls; 
    void incr_and_test(upair p); 

    public : 
    // Constructeurs : 
    Sandpile(int m, int n, int k = 4); 
    Sandpile(int m, int n, std::map<upair,unsigned>& M);

    // Accesseurs & Mutateurs : 
    unsigned operator()(unsigned i, unsigned j) const {return terrain[i+j*m];}
    unsigned h(upair p) const {return terrain[p.first + p.second * m];}
    unsigned& h(upair p) {return terrain[p.first + p.second * m];}

    // Méthodes : 
    std::list<upair> voisins(upair p) const; 
    void eboul(upair p);
    int stabil(); 
    unsigned nb_total_ebouls() const; 
    template<typename RNG> 
    int add_random_grain(RNG& G, int k = 1); 
    unsigned volume_total() const; 

    // Fonctions amies : 
    friend std::ostream& operator<<(std::ostream& out, const Sandpile& S);
    friend Sandpile operator+(const Sandpile& s, const Sandpile& t); 
};

template<typename RNG> 
int Sandpile::add_random_grain(RNG& G, int k = 1)
{
    std::uniform_int_distribution<int> U(1,m-1);
    std::uniform_int_distribution<int> V(1,n-1);
    for(int l = 0; l < k; ++l)
    {
        int i = U(G); 
        int j = V(G); 
        h(upair(i,j))++;
    }
    stabil(); 
    return stabil(); 
}
