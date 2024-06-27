#include <iostream>

#include "my_permutation.hpp"

using namespace std; 

int main()
{
    // Première partie. 

    Permutation b(6); 
    cout << b << endl; 
    // Output : 6 : 0 1 2 3 4 5
    std::vector<int> v{2,4,5,3,1,0}; 
    Permutation a(v); 
    for(int i = 0; i <= 6; ++i)
    {
        cout << "a^" << i << "\n" << b << "\n"; 
        b = b*a; 
    }
    /* Output : 
    6 : 0 1 2 3 4 5
    a^0
    6 : 0 1 2 3 4 5
    a^1
    6 : 2 4 5 3 1 0
    a^2
    6 : 5 1 0 3 4 2
    a^3
    6 : 0 4 2 3 1 5
    a^4
    6 : 2 1 5 3 4 0
    a^5
    6 : 5 4 0 3 1 2
    a^6
    6 : 0 1 2 3 4 5 */
    std::list<int> fp = a.fixed_points(); 
    for(const int& i : fp)
    {
        cout << i << " "; 
    }
    //Output : 3 


    // Deuxième partie. 

    ifstream fichier_in_t("file_t.txt");
    Permutation in_t; 
    fichier_in_t >> in_t; 
    ifstream fichier_in_s("file_s.txt");
    Permutation in_s; 
    fichier_in_s >> in_s; 
    ofstream fichier_out("test_file_s.txt"); 
    fichier_out << in_s; 
    fichier_in_t.close(); 
    fichier_in_s.close(); 
    fichier_out.close(); 
    list<Cycle> la = a.cycles(); 
    cout << "Les cycles de a sont : "; 
    for(const Cycle & c : la)
    {
        cout << c << " "; 
    }
    // Output : Les cycles de a sont : [ 0 2 5 ] [ 1 4 ]. 
    cout << "L'ordre de la permutation a est : " << a.order() << endl; 
    // Output :  L'ordre de la permutation a est : 6.

    Permutation u = in_s * in_t.inverse(); 
    std::list<Cycle> lu = u.cycles(); 
    cout << "Les cycles de u ont pour longueurs : ";
    for(const Cycle& c : lu) {cout << c.order() << " ";}
    // Output : Les cycles de u ont pour longueurs : 11307 1739 1254 1049 26 153 682 79 30 3 51 8 3
    cout << "L'ordre de la permutation u est : " << u.order() << endl; 
    // Output : L'ordre de la permutation u est : 1484488632

    //Troisième partie. 
    std::mt19937_64 G(time(nullptr)); 
    unsigned n = 100, nb_echant = 10000, nb_derang = 0; 
    for(unsigned i = 0; i < nb_echant; ++i)
    {
        nb_derang += Permutation(n,G).is_derangement(); 
    }
    cout << "La proportion de dérangements est environ : " << nb_derang/(double)nb_echant << "\n"; 
    // Output : La proportion de dérangements est environ : 0.361 : ce résultat est asymptotiquement proche de exp{-1}. 
    return 0; 
}