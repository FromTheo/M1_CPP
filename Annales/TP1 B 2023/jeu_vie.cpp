#include "jeu_vie.hpp"

using namespace std; 

jeu_vie::jeu_vie(int _H, int _L) : H(_H), L(_L) 
{
    config.resize(H);
    for(int i = 0; i < H; ++i)
    {
        config[i].resize(L);
        for(int j = 0; j < L; ++j)
        {
            config[i][j] = false; 
        }
    }
}

jeu_vie::jeu_vie(std::istream& in)
{
    int _H, _L; 
    in >> _H >> _L; 
    H = _H; 
    L = _L; 
    config.resize(H); 
    for(int h = 0; h < H; ++h)
    {
        config[h].resize(L); 
        for(int l = 0; l < L; ++l)
        {
            char x; 
            in >> x;
            if(x == '.') config[h][l] = false; 
            else config[h][l] = true; 
        }
    }
}

int jeu_vie::voisins(int i, int j) const
{
    int compteur = 0; 
    for(int h = i-1; h <= i+1; h++)
    {
        for(int l = j-1; l <= j+1; l++)
        {
            if(!(l>=L or l<0) and !(h>=H or h<0) and !(h==i and l==j))
            {
                compteur+=config[h][l];
            }
        }
    }
    return compteur;
}

void jeu_vie::iteration()
{
    vector<vector<bool>> copy = config; 
    for(int h = 0; h < H; ++h)
    {
        for(int l = 0; l < L; ++l)
        {
            if(voisins(h,l) == 3) copy[h][l] = true; 
            else if(voisins(h,l) >= 4 or voisins(h,l) <= 1) copy[h][l] = false; 
        }
    }
    config = copy; 
}

void jeu_vie::affichage(std::ostream& out) const
{
    out << H << " " << L << "\n"; 
    for(int h = 0; h < H; ++h)
    {
        for(int l = 0; l < L; ++l)
        {
            if(config[h][l]) out << "X"; 
            else out << ".";
        }
        out << "\n"; 
    }
}

int jeu_vie::nb_cellules() const
{   
    int compteur = 0; 
    for(int h = 0; h < H; ++h)
    {
        for(int l = 0; l < L; ++l)
        {
            compteur += config[h][l];
        }
    }
    return compteur;
}