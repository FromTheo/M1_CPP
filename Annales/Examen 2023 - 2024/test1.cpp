#include <iostream> 
#include <algorithm>

#include "PPP.hpp"

using namespace std; 

int main()
{
    mt19937_64 G(time(nullptr)); 

    ifstream file("param1.txt"); 
    PoissonPointProcess<double, uniform_real_distribution<int>> P; 
    file >> P; 
    file.close(); 

    vector<double> v = P.generate_point_vector(G); 
    int n = count_if(v.begin(), v.end(), [](const double &d)
    {
        return d >= 1.5 && d <= 4.5; 
    }); 
    cout << "Le nombre de points dans l'intervalle [1.5,4.5] est : " << n << endl; 

    sort(v.begin(), v.end()); //Tri réalisé par défaut. 
    /* On aurait tout de même pu faire : 
    sort(v.begin(), v.end(), [](const double &a, const double &b)
    {
        return a < b;
    }); */ 

    ofstream file_out("points.txt"); 
    for(const double &d : v)
    {
        file_out << d << " "; 
    }
    file_out.close(); 
    return 0; 
}