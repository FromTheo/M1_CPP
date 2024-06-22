#include <vector>
#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#include <utility>

template<class E, class F>
std::map<F, std::set<E>> image_reciproque(const std::map<E,F>& M)
{
    std::map<F, std::set<E>> resultat; 
    for(const std::pair<E,F>& p : M)
    {
        resultat[p.second].insert(p.first); 
    }
    return resultat; 
}

int main()
{
    const int N = 100; 
    std::vector<double> v(N); 
    double s = 0.0; 
    for(double& x : v)
    {
        s += 1.5; 
        x = s*s; 
    }
    int n = std::count_if(v.begin(), v.end(), [](const double & u)
    {
        return u < 30.0;
    });
    std::cout << "Le nombre d'élements de v inférieurs à 30 est : " << n << "\n"; 
    // Output : Le nombre d'élements de v inférieurs à 30 est : 3
    return 0;
}
