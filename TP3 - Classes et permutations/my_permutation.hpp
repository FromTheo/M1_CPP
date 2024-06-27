#include <vector> 
#include <numeric>
#include <fstream> 
#include <algorithm> 
#include <list> 
#include <set> 
#include <random>
#include <ctime> 

//Forward declarations : 
class Permutation; 
class Cycle; 

long int pgcd(long int a, long int b);
long int ppcm(long int a, long int b);

class Permutation
{
    private : 
    int n; 
    std::vector<int> images; 

    public : 
    // Constructeurs : 
    Permutation(int n = 1); 
    Permutation(std::vector<int>& v) : n(v.size()), images(v) {}
    template<typename RNG>
    Permutation(int n, RNG& G); 

    // Accesseurs, Mutateurs : 
    int size() const {return n;}
    int operator[](int i) const {return images[i];}
    //int& operator[](int i) {return images[i];} À ne pas mettre car pourrait casser la structure d'une permutation (bijection). 

    // Méthodes : 
    std::list<int> fixed_points() const; 
    bool is_derangement() const {return fixed_points().empty();}
    Permutation inverse() const; 
    std::list<Cycle> cycles() const; 
    long int order() const; //C'est le PPCM de la longueur des cycles (leur ordre de manière équivalente). 

    // Fonctions amies : 
    friend std::ostream& operator<<(std::ostream& out, const Permutation& P); 
    friend std::istream& operator>>(std::istream& in, Permutation& P); 
    friend Permutation operator*(const Permutation& s,  const Permutation& t); 
};

class Cycle
{
    private :
    std::vector<int> elem; 
    void add_last_point(int i) {elem.push_back(i);}
    std::vector<int>::const_iterator find(int i) const {return std::find(elem.begin(), elem.end(),i);}

    public :  

    friend class Permutation; 

    // Accesseurs : 
    long int order() const {return elem.size();}  //L'ordre d'un cycle est le nombre de points le composant. 
    int operator[](int i) const; 

    // Méthodes : 
    Cycle inverse() const; 
    std::list<Cycle> cycles() const;

    // Fonctions amies : 
    friend std::ostream& operator<<(std::ostream& out, const Cycle& c); 
    friend bool operator<(const Cycle& c, const Cycle& d); 
};

template<typename RNG>
Permutation::Permutation(int n, RNG& G) : n(n), images(n)
{
    std::iota(images.begin(), images.end(), 0); 
    for(int i = 0; i < n-1; ++i)
    {
        std::uniform_int_distribution<int> U(i,n-1); 
        int j = U(G); 
        std::swap(images[i], images[j]); 
    }
}