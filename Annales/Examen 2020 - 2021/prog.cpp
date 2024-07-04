#include <iostream>

#include "rejection.hpp"

using namespace std; 

int main()
{   
    auto density_exp = [](double x)
    {
        return std::exp(-x); 
    };

    auto density_y = [](double x)
    {
        return std::sqrt(2/M_PI)*std::exp(-x*x/2); 
    };
    const int N = 10; 
    mt19937_64 G(time(nullptr)); 
    double C = sqrt(2*exp(1)/M_PI); 
    exponential_distribution<double> X(1.0); 
    Rejection_distribution<exponential_distribution<double>, decltype(density_y), decltype(density_exp), double> RD(X, density_y, density_exp, C); 
    for(int i = 0; i < N; ++i)
    {
        cout << RD(G) << " avec steps = " << RD.get_steps() << endl; 
    }
}