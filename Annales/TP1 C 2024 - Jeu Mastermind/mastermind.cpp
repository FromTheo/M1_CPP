#include "mastermind.hpp"

using namespace std; 


CodeSecret::CodeSecret(std::vector<int>& v) : n(v.size()), code(v)
{
    v_max = *max_element(v.begin(), v.end());
}

int CodeSecret::BonneValeurBonEndroit(CodeSecret& prop) const
{
    int compteur = 0; 
    for(int i = 0; i < n; ++i)
    {
        if(prop[i] == code[i]) compteur++;
    }
    return compteur; 
}

int CodeSecret::BonneValeurMauvaisEndroit(CodeSecret& prop) const
{
    int compteur = 0; 
    for(int i = 0; i < n; ++i)
    {
        auto it = find(code.begin(), code.end(), prop[i]); 
        if(it != code.end()) compteur++; 
    }
    return compteur - BonneValeurBonEndroit(prop); 
}

std::ostream& operator<<(std::ostream& out, const CodeSecret& C)
{
    for(const int& i : C.code)
    {
        out << i << " "; 
    }
    return out; 
}


CodeSecret Decodeur::ProposerCode(int n, int v_max)
{
    cout << "Entrez un code de longueur " << n << " de valeur maximale " << v_max << ". " << endl;
    vector<int> prop; 
    for(int i = 0; i < n; ++i)
    {
        int value; 
        cout << "Valeur numéro " << i << " : "; 
        cin >> value; 
        if(prop.empty())
        {
            while(value < 0 or value > v_max)
            {
                cout << "Valeur numéro " << i << " : "; 
                cin >> value; 
            }
            prop.push_back(value); 
        }
        else
        {
            auto it = find(prop.begin(), prop.end(), value); 
            while(it != prop.end() or value < 0 or value > v_max)
            {
                cout << "Valeur numéro " << i << " : "; 
                cin >> value; 
                it = find(prop.begin(), prop.end(), value); 
            }
            prop.push_back(value);  
        }
    } 
    etape++;
    return CodeSecret(prop); 
}

bool Mastermind::jouer(Decodeur& D) const
{
    cout << " -- Bienvenue " << D.name() << " dans le jeu du Mastermind -- " << endl; 
    while(D.step() < nb_essai)
    {
        CodeSecret prop = D.ProposerCode(code.size(), code.value_max()); 
        if(code.BonneValeurBonEndroit(prop) == code.size())
        {
            cout << "Vous avez gagné."; 
            return true; 
        }
        else 
        {
            cout << "Il y a " << code.BonneValeurBonEndroit(prop) << " bonnes valeurs bien placées et " << code.BonneValeurMauvaisEndroit(prop) << " bonnes valeurs mal placées." << endl; 
        }
    }
    cout << "Vous avez perdu."; 
    cout << "Le code à trouver était : "; 
    for(int i = 0; i < code.size(); ++i)
    {
        cout << code[i] << " "; 
    }
    cout << endl; 
    return false; 
}