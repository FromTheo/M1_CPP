#include <iostream>
#include <cmath> 

using namespace std; 

double aire_du_cercle(double x)
{
    return M_PI*x*x; 
}

double aire_du_carre(double x)
{
    return x*x; 
}

int main()
{
    double r; 
    double l; 
    cout << "Entrez le rayon du cercle : " << endl; 
    cin >> r; 
    while(r < 0.0)
    {
        cout << "Erreur entrez une nouvelle valeur : " << endl; 
        cin >> r;    
    }
    cout << "Son aire est  : " << aire_du_cercle(r) << endl;  

    cout << "Entrez la longueur du côté du carré : " << endl; 
    cin >> l; 
    while(l < 0.0)
    {
        cout << "Erreur entrez une nouvelle valeur : " << endl; 
        cin >> l;    
    }
    cout << "Son aire est  : " << aire_du_carre(l) << endl; 
    return 0;
}