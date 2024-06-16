#include <iostream>
#include "linear_combination.hpp"

using namespace std; 


int main(){

    std::vector<double> coeff{2.,-1.};

    std::array<double,3> v1 = {1.,2.,3.};
    std::array<double,3> v2 = {4.,5.,6.};
    std::array<double,3> w = {-2,-1.,0.};

    LinearCombination<double> L(coeff);

    // Evaluation 
    std::vector<std::array<double,3>> Argument{v1,v2};
    std::array<double,3> res = L(Argument);


    if((res-w) == std::array<double,3>()){
        std::cout << "w est une combinaison linéaire de v1 et v2" << std::endl;
    }else{
         std::cout << "w n'est une combinaison linéaire de v1 et v2" << std::endl;
    }

    coeff = std::vector<double>({-3.,4., 5.});
    std::array<double,3> v3 = {10.,-4.,1.};

    LinearCombination<double> LC2(coeff);

    // Evaluation 
    Argument = std::vector<std::array<double,3>>({v1,v2,v3});
    res = LC2(Argument);
    
    if((res-w) == std::array<double,3>()){
        std::cout << "w est une combinaison linéaire de v1, v2 et v3" << std::endl;
    }else{
         std::cout << "w n'est pas une combinaison linéaire de v1,v2 et v3 avec ces coefficients" << std::endl;
    }

    /* Affichage sur le terminal
        w est une combinaison linéaire de v1 et v2
        w n'est pas une combinaison linéaire de v1,v2 et v3 avec ces coefficients
    */
    { 
        std::vector<double> v1{1.,2.,4.}, v2{-1.,1.,3.}, v3{1.,-1.,1.};
        std::array<double,3> w{2.,1.,3.}; 
        std::vector<LinearCombination<double>> vecteur_L(3); 
        LinearCombination<double> L1({1.,-1.,1.}); 
        LinearCombination<double> L2({2.,1.,-1.}); 
        LinearCombination<double> L3({4.,3.,1.});
        vecteur_L = {L1,L2,L3}; 
        std::pair<bool, std::array<double,3> > res =ResolutionSysteme(vecteur_L, w); 
        if(res.first == true)
        {
            cout << "Il y a une solution : "; 
            for(const double&d  : res.second)
            {
                cout << d << " "; 
            }
            cout << endl; 
            cout << "Verif :" << endl; 
            cout << res.second[0]*v1[0] + res.second[1]*v2[0] + res.second[2]*v3[0] << endl; 
            cout << res.second[0]*v1[1] + res.second[1]*v2[1] + res.second[2]*v3[1] << endl; 
            cout << res.second[0]*v1[2] + res.second[1]*v2[2] + res.second[2]*v3[2] << endl; 
        }
    }

    { 
        std::vector<double> v1{1.,3.,8.}, v2{2.,-1.,2.}, v3{-3.,2.,-2.};
        std::array<double,3> w{-1.,7.,9.}; 
        std::vector<LinearCombination<double>> vecteur_L(3); 
        LinearCombination<double> L1({1.,2.,-3.}); 
        LinearCombination<double> L2({3.,-1.,2.}); 
        LinearCombination<double> L3({8.,2.,-2.});
        vecteur_L = {L1,L2,L3}; 
        std::pair<bool, std::array<double,3> > res =ResolutionSysteme(vecteur_L, w); 
        if(res.first == true)
        {
            cout << "Il y a une solution : "; 
            for(const double&d  : res.second)
            {
                cout << d << " "; 
            }
            cout << endl; 
            cout << "Verif :" << endl; 
            cout << res.second[0]*v1[0] + res.second[1]*v2[0] + res.second[2]*v3[0] << endl; 
            cout << res.second[0]*v1[1] + res.second[1]*v2[1] + res.second[2]*v3[1] << endl; 
            cout << res.second[0]*v1[2] + res.second[1]*v2[2] + res.second[2]*v3[2] << endl; 
        }
        else
        {
            cout << "Pas de solution." << endl; 
        }
    }

    { 
        std::vector<double> v1{1.,3.,1.}, v2{2.,4.,2.}, v3{3.,5.,-2.};
        std::array<double,3> w{4.,6.,-7.}; 
        std::vector<LinearCombination<double>> vecteur_L(3); 
        LinearCombination<double> L1({1.,2.,3.}); 
        LinearCombination<double> L2({3.,4.,5.}); 
        LinearCombination<double> L3({1.,2.,-2.});
        vecteur_L = {L1,L2,L3}; 
        std::pair<bool, std::array<double,3> > res =ResolutionSysteme(vecteur_L, w); 
        if(res.first == true)
        {
            cout << "Il y a une solution : "; 
            for(const double&d  : res.second)
            {
                cout << d << " "; 
            }
            cout << endl; 
            cout << "Verif :" << endl; 
            cout << res.second[0]*v1[0] + res.second[1]*v2[0] + res.second[2]*v3[0] << endl; 
            cout << res.second[0]*v1[1] + res.second[1]*v2[1] + res.second[2]*v3[1] << endl; 
            cout << res.second[0]*v1[2] + res.second[1]*v2[2] + res.second[2]*v3[2] << endl; 
        }
        else
        {
            cout << "Pas de solution." << endl; 
        }
    }
    return 0;
}