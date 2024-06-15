#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream> 
#include <string> 
#include <random> 

class CodeSecret
{
    private : 
    int n;                 // Taille du code. 
    int v_max;             // Valeur maximale de l'ensemble des valeurs possibles. 
    std::vector<int> code; // Code secret.

    public : 
    // Constructeurs : 
    CodeSecret() : n(0), v_max(0), code() {}
    CodeSecret(std::vector<int>& v, int v_max) : n(v.size()), v_max(v_max), code(v) {}
    CodeSecret(std::vector<int>& v); 
    template<typename RNG>
    CodeSecret(int n, int v_max, RNG& G); 

    // Accesseurs, Mutateurs : 
    int size() const {return n;}
    int value_max() const {return v_max;}
    int operator[](int i) const {return code[i];}

    // Méthodes : 
    int BonneValeurBonEndroit(CodeSecret& prop) const; 
    int BonneValeurMauvaisEndroit(CodeSecret& prop) const; 

    // Fonctions amies : 
    friend std::ostream& operator<<(std::ostream& out, const CodeSecret& C); 
    
};

template<typename RNG>
CodeSecret::CodeSecret(int n, int v_max, RNG& G) : n(n), v_max(v_max)
{   
    std::uniform_int_distribution<int> U(0, v_max); 
    std::vector<int> copy; 
    for(int i = 0; i < n ; ++i)
    {
        int value = U(G); 
        if(copy.empty()) copy.push_back(value);
        else 
        {
            auto it = find(copy.begin(), copy.end(), value);
            while(it != copy.end())
            {
                value = U(G); 
                it = find(copy.begin(), copy.end(), value);
            }
            copy.push_back(value); 
        }
    }
    code = copy; 
}

class Decodeur
{
    private : 
    std::string nom; 
    int etape; 

    public :
    // Constructeurs : 
    Decodeur(const std::string& nom) : nom(nom), etape(0) {}

    // Accesseurs, Mutateurs : 
    std::string name() const {return nom;}
    int step() const {return etape;}

    // Méthodes : 
    CodeSecret ProposerCode(int n, int v_max); 
};

class Mastermind
{
    private : 
    int nb_essai;       // Nombre d'éssai total dans la partie. 
    CodeSecret code;    // Code secret à deviner.

    public : 
    // Constructeurs : 
    Mastermind(int nb, CodeSecret C) : nb_essai(nb), code(C) {}

    // Méthodes : 
    bool jouer(Decodeur& D) const; 

};