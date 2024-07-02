#include <iostream>

#include "gamer.hpp"

using namespace std;

int main()
{
    Game G("Alex", "Jean"); 
    G.wins(1,3.); 
    G.wins(2,4.); 
    auto winner_name = G.the_winner_is(); 
    cout << "Number of turns already played : " << G.turns() << endl; 
    ofstream fichier("jeu.txt"); 
    G.write(fichier); 
    return 0; 
}