#include <iostream>
#include <cmath>            //std::sqrt
#include <vector> 

#include "fma.hpp" 
#include "geometry.hpp" 

using namespace std;

int main() 
{
    //Section 2.1 
    Finite_atomic_measure<int> mu;
    mu.add_mass( 3, 1.); 
    mu.add_mass( 5, 2.);
    mu.add_mass( 8, 0.5);
    cout << "*** Masse totale: " << mu.total_mass()<< "\n"; //Output : 3.5
    cout << "*** Nb points: " << mu.nb_of_atoms() << "\n";  //Output : 3
    cout << "*** Mesure nu:\n" << mu << "\n";
    /* Output : 
    3
    3 1
    5 2
    8 0.5 */
    
    //Section 2.2 
    Segment<int> S1(4,9), S2(-3,6), S3(-3,0);
	cout << "*** Mesure mu([4,9]): " << mu.measure(S1) << "\n";  //Output : 2.5
	cout << "*** Mesure mu([-3,6]): " << mu.measure(S2) << "\n"; //Output : 3.
	cout << "*** Mesure mu([-3,0]): " << mu.measure(S3) << "\n"; //Output : 0.
    cout << "*** Intégrale de sqrt: " << mu.integral([](int n) { return sqrt(n); })<< "\n"; //Output : 7.6184

    //Section 2.4
    auto f = [](int x)->double
    {
        return (x-4)*(x-4) + M_PI; 
    };
    cout << "*** Mesure image de mu par f:\n" << image(mu,f) << endl; 
    /* Output : 
    2
    4.14159 3
    19.1416 0.5 */

    //Bonus : 
    vector<int> v{0,1,2,3,4,5,6,7,8,9}; 
    Finite_atomic_measure<int> Test_constructor(v.begin(), v.end()); 
    cout << "*** Test du constructeurs : " << Test_constructor << endl; 
    /* Output : 
    10
    0 1
    1 1
    2 1
    3 1
    4 1
    5 1
    6 1
    7 1
    8 1
    9 1 */
    Finite_atomic_measure<int> sum = mu + mu; 
    cout << "*** Test de l'opérator + : \n" << sum << endl; 
    /* Ouput : 
    3
    3 2
    5 4
    8 1 */ 

    return 0;
}
