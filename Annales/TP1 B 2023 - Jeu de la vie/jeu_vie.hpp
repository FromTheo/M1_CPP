#include <vector>
#include <fstream> 
#include <random> 

class jeu_vie 
{
    private : 
    int H, L; 
    std::vector<std::vector<bool>> config; 

    public : 
    // Constructeurs : 
    jeu_vie(int _H, int _L); 
    jeu_vie(std::istream& in); 
    template<typename RNG>
    jeu_vie(int _H, int _L, double p, RNG& G); 

    // Accesseurs : 
    int hauteur() const {return H;}
    int largeur() const {return L;}

    // Méthodes : 
    int voisins(int i, int j) const; 
    void iteration(); 
    void affichage(std::ostream& out) const; 
    int nb_cellules() const; 
};

template<typename RNG>
jeu_vie::jeu_vie(int _H, int _L, double p, RNG& G) : H(_H), L(_L)
{
    std::bernoulli_distribution B(p); 
    config.resize(H); 
    for(int h = 0; h < H; ++h)
    {
        config[h].resize(L); 
        for(int l = 0; l < L; ++l)
        {   
            int random = B(G); 
            if(random == 1) config[h][l] = true;
            else config[h][l] = false; 
        }
    }
}