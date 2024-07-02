#include <iostream>

#include "vec.hpp"

using namespace std; 

int main()
{
    mt19937_64 G(time(nullptr)); 
    ofstream fichier("example.txt"); 
    std::vector<V> vect = generate_random_ortho(10, G); 
    for(const V& v : vect)
    {
        fichier << v << endl; 
    }
    fichier.close(); 
    return 0; 
}