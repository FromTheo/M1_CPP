#include <vector>
#include <map> 
#include <random>
#include <fstream>

template<class E, class Probmeas>
class PoissonPointProcess; 

template<class E, class Probmeas>
std::ostream& operator<<(std::ostream& out, const PoissonPointProcess<E,Probmeas>& P); 

template<class E, class Probmeas>
std::istream& operator>>(std::istream& in, PoissonPointProcess<E,Probmeas>& P); 

template<class E, class Probmeas>
class PoissonPointProcess
{
    private : 
    Probmeas p; 
    double muE; 

    public : 
    // Constructeurs : 
    PoissonPointProcess() : p(), muE(1) {}  

    // Accesseurs, Mutateurs : 
    double mass() const {return muE;}
    double& mass() {return muE;} 

    // Méthodes : 
    template<class RNG>
    std::vector<E> generate_point_vector(RNG& G); 
    template<class RNG>
    std::map<E,int> generate_point_map(RNG& G);
    template<class Iter, class RNG>
    void generate_point_iterator(RNG& G); 

    // Fonctions amies : 
    friend std::ostream& operator<< <>(std::ostream& out, const PoissonPointProcess<E,Probmeas>& P);
    friend std::istream& operator>> <>(std::istream& in, PoissonPointProcess<E,Probmeas>& P);

};

template<class E, class Probmeas>
template<class RNG>
std::vector<E> PoissonPointProcess<E,Probmeas>::generate_point_vector(RNG& G)
{
    std::poisson_distribution Poisson(muE); 
    int N = Poisson(G); 
    std::vector<E> v(N); 
    for(int i = 0; i < N; ++i)
    {  
        v[i] = p(G); 
    }
    return v; 
}

template<class E, class Probmeas>
template<class RNG>
std::map<E,int> PoissonPointProcess<E,Probmeas>::generate_point_map(RNG& G)
{
    std::poisson_distribution Poisson(muE); 
    int N = Poisson(G); 
    std::map<E,int> M; 
    for(int i = 0; i < N; ++i)
    {  
        E value = p(G); 
        M[value]++; 
    }
    return M; 
}

template<class E, class Probmeas>
std::ostream& operator<<(std::ostream& out, const PoissonPointProcess<E,Probmeas>& P)
{
    out << P.p << "\n"; 
    out << P.muE; 
    return out; 
}

template<class E, class Probmeas>
std::istream& operator>>(std::istream& in, PoissonPointProcess<E,Probmeas>& P)
{
    in >> P.p >> P.muE; 
    return in; 
}


