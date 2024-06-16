#include <iostream>
#include <cmath> 
#include "linear_combination.hpp"

using namespace std; 

int main()
{
    std::ifstream fichier("data.txt"); 
    std::pair<vector<double>,vector<double> > pair = ReadData(fichier); 
    std::vector<double> x_values = pair.first; 
    std::vector<double> y_values = pair.second; 
    fichier.close(); 
    std::vector<double> exp_values(x_values.size()); 
    std::vector<double> cos_values(x_values.size()); 
    std::transform(x_values.begin(), x_values.end(), exp_values.begin(), [](const double& d)
    {
        return std::exp(4*d); 
    }); 
    std::transform(x_values.begin(), x_values.end(), cos_values.begin(), [](const double& d)
    {
        return std::cos(6*d); 
    }); 
    // ou bien utiliser AppFct 
    cout << "*** 1. ***" << endl; 
    std::vector<double> coefficients1{-2.0,0.1}; 
    for(int i=0; i<x_values.size(); i++)
    {
        cout << "L(x_" << i << ") = " << coefficients1.front()*cos_values[i]+coefficients1.back()*exp_values[i] << endl; 
    }
    double erreur1 = 0.; 
    for(int i=0; i<x_values.size(); i++)
    {
        erreur1 +=(coefficients1.front()*cos_values[i]+coefficients1.back()*exp_values[i]-y_values[i])*(coefficients1.front()*cos_values[i]+coefficients1.back()*exp_values[i]-y_values[i]);
    }
    cout << "ERREUR : " << erreur1 << endl;
    cout << "\n\n\n";

    cout << "*** 2. *** " << endl; 
    std::vector<double> coefficients2{2.0,0.9}; 
    for(int i=0; i<x_values.size(); i++)
    {
        cout << "L(x_" << i << ") = " << coefficients2.front()*cos_values[i]+coefficients2.back()*exp_values[i] << endl; 
    }
    double erreur2 = 0.; 
    for(int i=0; i<x_values.size(); i++)
    {
        erreur2 = erreur2 + (coefficients2.front()*cos_values[i]+coefficients2.back()*exp_values[i]-y_values[i])*(coefficients2.front()*cos_values[i]+coefficients2.back()*exp_values[i]-y_values[i]);
    }
    cout << "ERREUR : " << erreur2 << endl; 
    cout << "\n\n\n";

    cout << "*** 3. *** " << endl; 
    std::vector<double> coefficients3{-10.0, 0.2}; 
    for(int i=0; i<x_values.size(); i++)
    {
        cout << "L(x_" << i << ") = " << coefficients3.front()*cos_values[i]+coefficients3.back()*exp_values[i] << endl; 
    }
    double erreur3 = 0.; 
    for(int i=0; i<x_values.size(); i++)
    {
        erreur3 = erreur3 + (coefficients3.front()*cos_values[i]+coefficients3.back()*exp_values[i]-y_values[i])*(coefficients3.front()*cos_values[i]+coefficients3.back()*exp_values[i]-y_values[i]);
    }
    cout << "ERREUR : " << erreur3 << endl; 




    return 0; 
}

