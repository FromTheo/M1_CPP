#include <iostream>
#include <vector>

#include "urne.hpp"
#include "regles.hpp"

using namespace std;

int main() 
{
    //Question 5 : 
    Urne<int> urne2; 
    cout << urne2 << endl; 
    /* Output : 
    2
    1	1 */ 

    //Question 10 : 
    mt19937_64 G(time(nullptr)); 
    auto updatePolya2 = [](int j, array<int,2>& v)
    {
        v[j]++;
    }; 

    //Question 11 : 
    int size_prop = 10000; 
    vector<double> prop (size_prop); 
    for(int i = 0; i < size_prop; ++i)
    {
        urne2.maj_p_fois(updatePolya2, 1000, G); 
        prop[i] = urne2.fraction(0); 
        urne2.reset(); 
    }

    //Question 13 : 
    sort(prop.begin(), prop.end()); 
    /* std::sort tri par défaut par ordre croissant. On aurait pu écrire : 
    sort(prop.begin(), prop.end(), [](const double & a, const double & b)
    {
        return a < b; 
    }); */
    for(int j = 0; j < 10; ++j)
    {
        cout << prop[size_prop/10*j] << endl; 
    }
    /* Output : 
    0.000998004
    0.101796
    0.199601
    0.301397
    0.40519
    0.5
    0.602794
    0.695609
    0.799401
    0.903194 */

    //Question 14 : 
    Urne<long, 7> urne7; 
    urne7.maj(updatePolyaN<long,7>,G); 
    cout << urne7 << endl; 
    /* Output : 
    8
    1	1	1	1	2	1	1 */ 

    //Question 16 : 
    Friedman2 updateF(7,2); 

    //Qestion 17 : 
    urne2.reset(); 
    vector<double> prop2 (size_prop); 
    for(int i = 0; i < size_prop; ++i)
    {
        urne2.maj_p_fois(updateF, 1000, G); 
        prop2[i] = urne2.fraction(0); 
        urne2.reset(); 
    }
    sort(prop2.begin(), prop2.end()); 
    for(int j = 0; j < 10; ++j)
    {
        cout << prop2[size_prop/10*j] << endl; 
    }
    /* Output : 
    0.395579
    0.462231
    0.47445
    0.483337
    0.492224
    0.5
    0.508331
    0.516108
    0.52555
    0.537769 */

    return 0;
}

