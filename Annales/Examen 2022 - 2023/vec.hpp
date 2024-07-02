#include <vector>
#include <algorithm> 
#include <fstream> 
#include <random> 

#include "gram_schmidt.hpp"

class V
{
    private : 
    std::vector<double> coeffs; 

    public : 
    // Constructeurs : 
    V() {}
    V(int d, double a);
    template<class Iter>
    V(Iter begin, Iter out);  

    // Accesseurs / Mutateurs : 
    double operator()(int i) const {return coeffs[i];}
    double& operator()(int i) {return coeffs[i];}

    // Méthodes : 
    double scal(const V& a) const;  

    // Fonctions amies : 
    friend V operator+(const V& u, const V& v); 
    friend V operator*(const V&u, double a); 
    friend std::ostream& operator<<(std::ostream& out, const V& v); 
    friend std::istream& operator>>(std::istream& in, V& v); 
};

template<class Iter>
V::V(Iter begin, Iter out)
{   
    for(Iter it = begin; it != out; ++it)
    {
        coeffs.push_back(*it); 
    }
}

template<class RNG> 
std::vector<V> generate_random_ortho(int N, RNG& G)
{
    std::vector<V> matrice(N); 
    std::normal_distribution<double> norm(0.0,1.0); 
    for(int i = 0; i < N; ++i)
    {
        V v(N,0.0); 
        for(int j = 0; j < N; ++j)
        {
            v(j) = norm(G); 
        }
        matrice[i] = v; 
    }
    gram_schmidt_in_place(matrice); 
    normalize(matrice.begin(), matrice.end()); 
    return matrice; 
}