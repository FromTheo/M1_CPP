#include <iostream> 
#include <algorithm>

#include "PPP.hpp"

using namespace std; 

int main()
{
    mt19937_64 G(time(nullptr)); 

    ifstream file("param1.txt"); 
    PoissonPointProcess<double, binomial_distribution<int>> P; 
    file >> P; 
    file.close(); 

    map<int,int> M = P.generate_point_map(G); 
    bool test = any_of(M.begin(), M.end(), [](const pair<int,int>& p)
    {
        return p.second == 1; 
    }); 
    if(test) cout << "Il existe bien un point dont l'occurence est 1." << endl; 
    else cout << "Il n'existe pas de point dont l'occurence est 1." << endl; 

    for_each(M.begin(), M.end(), [](const pair<int,int>& p)
    {
        cout << p.first << " : " << p.second << "\n";  
    });
    return 0; 
}