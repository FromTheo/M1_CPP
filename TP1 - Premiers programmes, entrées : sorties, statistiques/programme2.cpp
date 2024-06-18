#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

int main()
{   
    int n; 
    cout << "Entrez un nombre entier dans [0, 100] : " << endl; 
    cin >> n; 
    vector<int> tableau(n); 
    while(n > 100 or n < 0)
    {
        cout << "Error. Out of range. Retry :" << endl; 
        cin >> n; 
    } 
    for(int i = 0; i < n; ++i)
    {
        tableau[i] = i*i; 
    }
    ofstream fichier("donnees.txt"); 
    fichier << "Voici les carrés des entiers : " << endl; 
    for(int i = 0; i < n; ++i)
    {
        fichier << i << " : " << tableau[i] << endl; 
    }
    fichier.close(); 
    return 0; 
}