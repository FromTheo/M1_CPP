#include <iostream> 


#include "polynome.hpp"

using namespace std;

int main()
{
    //Première partie : 
    Polynome<double> q; 
    cout << "Degré de q : " << q.degre() << endl; //Ouput : Degré de q : -1

    vector<int> v1{6,3,0,1,5}; 
    Polynome<int> p1(v1); 

    vector<int> v2{1,0,1};
    Polynome<int> p2(v2);

    complex<double> a(2.0,1.0); 
    complex<double> b(0.0,1.0);
    vector<complex<double>> vc{a,b}; 
    Polynome<complex<double>> pc(vc); 

    complex<int> one = 1; 
    cout << "is_one(one) : " << is_one(one) << endl; 

    cout << is_zero(a) << endl; //Output : 0
    affiche_monome(cout, a, 3); //Output : (2,1)z^3
    cout << endl; 

    cout << "p1 : "<< p1 << endl;  //Output :  p1 : 6 + 3x + 1x^3 + 5x^4
    cout << "p2 : " << p2 << endl; //Output :  p2 : 1 + 1x^2 


    //Seconde partie : 
    Polynome<int> sum = p1+p2; 
    Polynome<int> diff = p1-p2; 
    Polynome<int> prod = p1*p2;
    cout << "Somme : " << sum << endl; // Output : Somme : 7 + 3x + 1x^2 + 1x^3 + 5x^4
    cout << "Différence : " << diff << endl; //Output : Différence : 5 + 3x + -1x^2 + 1x^3 + 5x^4
    cout << "Produit : " << prod << endl; //Output : Produit : 6 + 3x + 6x^2 + 4x^3 + 5x^4 + 1x^5 + 5x^6

    Polynome<int> div = p1/p2; 
    Polynome<int> reste = p1%p2; 
    cout << "Quotient : " << div << endl; //Output : Quotient : -5 + 1x + 5x^2
    cout << "Reste : " << reste << endl; //Output : Reste : 11 + 2x 

    cout << "p1(0) = " << p1(0) << endl; //Output : p1(0) = 6
    cout << "p1(2) = " << p1(2) << endl; //Output : p1(2) = 100

    return 0; 
}