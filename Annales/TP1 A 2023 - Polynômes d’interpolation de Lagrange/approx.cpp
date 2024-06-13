#include <iostream> 
#include <cmath> 

#include "interpolation.hpp"

using namespace std; 

std::vector<double> generate_x(int N)
{
    std::vector<double> resultat(N); 
    for(int i = 1; i < N; ++i)
    {
        resultat[i] = resultat[i-1] + M_PI / ((double)N);
    }
    return resultat; 
}

std::vector<double> generate_t(int N)
{
    std::vector<double> resultat(N); 
    for(int i = 0; i < N; ++i)
    {
        resultat[i] = (2 * i + 1) * M_PI / ((double) 2 * N);  
    }
    return resultat;
}

int main()
{
    auto f = [](double x)
    {
        return sin(x);
    }; // Pour améliorer la clarté du code. 

    for(int N = 4; N < 1024; N *= 2)
    {
        vector<double> x_values = generate_x(N); 
        vector<double> t_values = generate_t(N); 
        vector<double> y_values(N); 
        transform(x_values.begin(), x_values.end(), y_values.begin(), [&f](const double &d)
        {
            return f(d); 
        });
        LagrangeInterpolation P(x_values, y_values); 
        vector<double> ecarts(N); 
        for(int k = 0; k < N; ++k)
        {
            ecarts[k] = abs(f(t_values[k]) - P(t_values[k])); 
        }
        double delta = *max_element(ecarts.begin(), ecarts.end()); 
        cout << "Pour N = " << N << ", delta = " << delta << endl; 
    }

    return 0; 
}