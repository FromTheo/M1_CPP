#include <random>
#include <fstream> 

class Markov2States
{
    protected : 
    int x; 
    std::bernoulli_distribution Ua; 
    std::bernoulli_distribution Ub; 

    public : 
    Markov2States(int x0 = 1, double a0 = 0.5, double b0 = 0.5) : x(x0), Ua(a0), Ub(b0) {}
    template<typename RNG> 
    int operator()(RNG& G);  
};

template<typename RNG> 
int Markov2States::operator()(RNG& G)
{
    if(Ua(G) == 1 && x == 1)
    {
        x = 2; 
    }
    if(Ub(G) == 1 && x == 2)
    {
        x = 1;
    }
    return x; 
}  

class Stat2states
{
    protected: 
    long unsigned visit1; 
    long unsigned visit2; 

    public : 
    Stat2states(int i, int j) : visit1(i), visit2(j) {}
    double operator/=(int n); 
    void operator+=(int x);
    friend std::ostream& operator<<(std::ostream& out, const Stat2states& S); 
};
