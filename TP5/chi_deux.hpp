#include <random>

template<class REAL, int k>
class Chi2_distribution
{
    private : 
    std::normal_distribution<REAL> N; 

    public : 
    Chi2_distribution() : N(0.0,1.0) {}
    template<class RNG>
    REAL operator()(RNG& G); 

};

template<class REAL, int k>
template<class RNG>
REAL Chi2_distribution<REAL, k>::operator()(RNG & G)
{   
    REAL Y = REAL(0); 
    for(int i = 0; i < k ; i++)
    {
        REAL X = N(G); 
        Y = Y + X*X;
    }
    return Y; 
}