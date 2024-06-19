#include <iostream>
#include <set> 
#include "piecewisefunction.hpp"

using namespace std; 

PiecewiseFn<std::set<int>, Affine_Fn<double>> make_int_fn_from_file( std::istream & in, double default_value) 
{
    PiecewiseFn<std::set<int>, Affine_Fn<double>> f;  
    int nb_morceaux; 
    in >> nb_morceaux; 
    for(int i = 0; i < nb_morceaux; ++i)
    {
        int taille_A; 
        double c; 
        in >> taille_A >> c; 
        set<int> A; 
        for(int j = 0; j < taille_A; ++j)
        {
            int value; 
            in >> value;
            A.insert(value);
        }
        f.add_piece(A,Affine_Fn<double>(0,c)); 
    }
    return f; 
}

int main()  
{
    auto input = std::ifstream("data2.txt");
    auto f = make_int_fn_from_file(input,0.5);
    for (int i = 0; i < 20; i++)
    {
        std::cout << i << ":\t" << f(i) << "\n";
    }

    /* Output : 
    0:	3.3333
    1:	3.3333
    2:	0
    3:	4.5678
    4:	0
    5:	1.2345
    6:	0
    7:	4.5678
    8:	0
    9:	3.3333
    10:	0
    11:	0
    12:	3.3333
    13:	2.5555
    14:	0
    15:	1.2345
    16:	3.3333
    17:	1.2345
    18:	0
    19:	0 */

    return 0;
}
