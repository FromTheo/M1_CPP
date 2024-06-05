#include <iostream>
#include <fstream> 
#include <ctime> 
#include "rw.hpp" 

using namespace std; 

int main()
{
    cout << "\n*** Question 2 ***" << endl; 
    mt19937_64 G(time(nullptr)); 
    RandomWalk RW(0,0.5); 
    for(int i = 0; i < 10; ++i)
    {
        cout << RW.time() << " " << RW.val() << endl; 
        RW.update(G);
    }
    RW.reset(); 

    cout << "\n*** Question 4 ***" << endl; 
    long int T = 10000;
    ofstream file("RWmin.txt"); 
    RandomWalk_with_Min RWM(0,0.5);
    for(int i = 0; i < T; ++i)
    {
        file << RWM.time() << " " << RWM.val() << " " << RWM.minimum() << endl; 
        RWM.update(G); 
    }
    file.close(); 
    return 0; 
}