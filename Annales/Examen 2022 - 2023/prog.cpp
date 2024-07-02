#include <iostream> 

#include "vec.hpp"

using namespace std;

int main()
{
    const int N = 10; 
    ifstream fichier("data.txt"); 
    ofstream fichier_out("ortho.txt"); 
    std::vector<V> vecteur; 
    V v; 
    while(fichier >> v)
    {
        vecteur.push_back(v); 
    }
    gram_schmidt_in_place(vecteur); 
    for(const V&v : vecteur)
    {
        fichier_out << v << "\n"; 
    }
    fichier.close(); 
    fichier_out.close(); 
    cout << " test : " << vecteur[1](0) << endl; 
    return 0; 
}