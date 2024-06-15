#include <random>

class SquareInDisk
{
    private : 
    std::uniform_real_distribution<double> U; 

    public : 
    SquareInDisk() : U(0.0,1.0) {}
    template<typename RNG> 
    double operator()(RNG& G);  
};

template<typename RNG> 
double SquareInDisk::operator()(RNG& G)
{
    double X = U(G); 
    double Y = U(G);
    if(X*X+Y*Y<=1) return 1;
    return 0; 
}