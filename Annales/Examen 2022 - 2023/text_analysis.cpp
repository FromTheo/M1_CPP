#include <iostream>
#include <fstream>
#include <vector> 
#include <string> 
#include <algorithm> 
#include <numeric> 
#include <cctype> 

using namespace std; 


int main()
{
    ifstream fichier("input.txt");
    vector<string> data; 
    string s; 
    while(fichier >> s)
    {
        data.push_back(s); 
    }   
    fichier.close(); 
    double moyenne = accumulate(data.begin(), data.end(), 0.0, [](double acc, const string &s)
    {
        return acc+s.size(); 
    })/data.size(); 
    cout << "La longueur moyenne d'un mot est : " << moyenne << endl; 
    vector<string> mots_longs;  
    for(int i = 0; i < data.size(); ++i)
    {
        if(data[i].size() >=6) mots_longs.push_back(data[i]); 
    }
    for(int i = 0; i < mots_longs.size(); ++i)
    {
        string s = mots_longs[i]; 
        toupper(s.front()); 
        mots_longs[i] = s;
    }
    sort(mots_longs.begin(), mots_longs.end(), [](const string& s, const string& t)
    {
        return s < t; 
    }); 
    ofstream fichier_out("output.txt"); 
    for(const string& s: mots_longs)
    {
        fichier_out << s << " "; 
    }
    fichier_out.close(); 
    return 0; 
}