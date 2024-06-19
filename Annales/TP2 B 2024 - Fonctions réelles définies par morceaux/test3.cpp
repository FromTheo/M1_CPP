#include <iostream>
#include "piecewisefunction.hpp"
#include "linearform.hpp"

using namespace std; 

template<>
bool test_if_contains(const std::vector<Segment>& S , const std::vector<double>& v)
{
    for(int i = 0; i < S.size(); ++i)
    {
        if(!S[i].contains(v[i])) return false; 
    }
    return true; 
}

int main() 
{
    ifstream fichier ("data3.txt");
    PiecewiseFn<vector<Segment>, LinearForm<double, 3>> f;  
    int nb_morceaux; 
    fichier >> nb_morceaux; 
    for(int i = 0; i < nb_morceaux; ++i)
    {
        vector<Segment> S(3); 
        for(int j = 0; j < 3; ++j)
        {
            double left, right; 
            fichier >> left >> right; 
            Segment s(left, right); 
            S[j] = s; 
        }
        vector<double> coefficients(3); 
        for(int j = 0; j < 3; ++j)
        {
            double value; 
            fichier >> value;
            coefficients[j] = value; 
        }
        LinearForm<double,3> L(coefficients); 
        f.add_piece(S,L); 
    }
    fichier.close(); 
    cout << f(vector<double>{0.3,0.1,0.4}) << endl; //Output : 1.5
    cout << f(vector<double>{1.5,0.5,3.5}) << endl; //Output : 0
    cout << f(vector<double>{2.3,1.7,3.6}) << endl; //Output : 18.5
    return 0; 
}

