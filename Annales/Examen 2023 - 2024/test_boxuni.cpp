#include <iostream>
#include "boxuniform.hpp"

using namespace std; 

int main()
{
    mt19937_64 G(time(nullptr)); 
    std::vector<double> a{0.0,0.0,-1.0,-1.0}, b{1.0,2.0,0.0,3.0}; 
    BoxUniform B(a.begin(), a.end(), b.begin(), b.end()); 
    const int N = 100; 
    vector<double> moyenne(4); 
    for(int i = 0; i < N; ++i)
    {
        vector<double> v = B(G); 
        for(int j = 0; j < 4; ++j)
        {
            moyenne[j] += v[j]; 
        }
    }
    transform(moyenne.begin(), moyenne.end(), moyenne.begin(), [&N](double &d)
    {
        return d/(double)N;
    }); 
    for_each(moyenne.begin(), moyenne.end(), [](const double &d)
    {
        cout << d << " "; 
    });
    //Output : 0.501621 0.91756 -0.457807 1.2676 
    return 0; 
}