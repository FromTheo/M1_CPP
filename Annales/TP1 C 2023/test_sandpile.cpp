#include <iostream> 

#include "sandpile.hpp"

using namespace std; 

int main()
{
    cout << "*** Question 4 ***" << endl; 
    Sandpile S_test(3,2); 
    cout << S_test << endl; 
    /* Output : 
    444
    444 */

    cout << "\n*** Question 5 ***" << endl; 
    Sandpile S(8,8,5); 

    cout << "\n*** Question 8 ***" << endl;
    cout << "Le nombre de voisins de la case (0,0) est : " << S.voisins(upair(0,0)).size() << endl; //Output : 2.
    cout << "Le nombre de voisins de la case (1,2) est : " << S.voisins(upair(1,2)).size() << endl; //Output : 4. 

    cout << "\n*** Question 13 ***" << endl;
    ofstream file("stab_8x8_5.txt"); 
    S.stabil();
    int number = S.nb_total_ebouls(); 
    file << number << "\n";
    file << S; 
    file.close();

    cout << "\n*** Question 14 ***" << endl;
    ofstream file2("stab_100x100_4.txt"); 
    Sandpile t(100,100); 
    t.stabil(); 
    int number2 = t.nb_total_ebouls(); 
    file2 << number2 << "\n"; 
    file2 << t;
    file2.close();

    cout << "\n*** Question 16 ***" << endl;    
    mt19937_64 G(time(nullptr)); 
    t.add_random_grain(G,3); 
    return 0; 
}