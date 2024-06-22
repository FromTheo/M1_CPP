#include <vector>
#include <random>
#include <utility>
#include <algorithm> 
#include <numeric> 
#include <fstream> 

class BoxUniform
{
    private : 
    std::vector< std::pair<double,double> > box_coord;   // Vecteur des paires (a_i, b_i)
    std::uniform_real_distribution<double> U;            // Pour générer une uniforme sur [0,1]. 

    public : 
    // Constructeurs : 
    BoxUniform() : U(0.0,1.0) {}
    template<class Iter1, class Iter2>
    BoxUniform(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2);

    // Accesseurs : 
    int dimension() const {return box_coord.size();}

    // Méthodes : 
    template<typename RNG>
    std::vector<double> operator()(RNG& G); 
    void scale(const double &s); 
    double volume() const; 

    // Fonctions amies : 
    friend BoxUniform operator*(const BoxUniform& A, const BoxUniform& B); 
    friend std::ostream& operator<<(std::ostream& out, const BoxUniform& A); 

};

template<typename RNG>
std::vector<double> BoxUniform::operator()(RNG& G)
{
    std::vector<double> resultat(dimension()); 
    for(int i = 0; i < dimension(); ++i)
    {
        resultat[i] = box_coord[i].first + (box_coord[i].second - box_coord[i].first) * U(G); 
    }
    return resultat; 
}

template<class Iter1, class Iter2>
BoxUniform::BoxUniform(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) : U(0.0,1.0) 
{
    std::vector<double> a;
    for(Iter1 it = begin1; it != end1; ++it)
    {
        a.push_back(*it); 
    }
    std::vector<double> b;
    for(Iter2 it = begin2; it != end2; ++it)
    {
        b.push_back(*it); 
    }
    std::vector<std::pair<double,double>> v_p(a.size()); 
    for(int i = 0; i < a.size(); ++i)
    {
        v_p[i] = std::make_pair(a[i], b[i]); 
    }
    box_coord = v_p; 
}