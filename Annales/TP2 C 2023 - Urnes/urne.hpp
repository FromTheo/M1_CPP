#include <array> 
#include <algorithm> 
#include <numeric> 
#include <fstream> 
#include <random>

//Forward declarations : 
template<typename Entier, int n = 2> 
class Urne; 

template<typename Entier, int n> 
std::ostream& operator<<(std::ostream& out, const Urne<Entier,n>& U); 

template<typename Entier, int n> 
class Urne {
    private:
        std::array<Entier, n> contenu0;
        std::array<Entier, n> contenu; 

    public:
        Urne(); 

        Entier nb_boules() const; 
        void reset() {contenu = contenu0;}
        double fraction(int j) const; 
        template<typename Update, typename RNG>
        void maj(Update f, RNG& G); 
        template<typename Update, typename RNG>
        void maj_p_fois(Update f, int p, RNG& G);

        friend std::ostream& operator<< <>(std::ostream& out, const Urne<Entier,n>& U); 
};

template<typename Entier, int n> 
Urne<Entier,n>::Urne()
{
    std::fill(contenu0.begin(), contenu0.end(), 1); 
    contenu = contenu0; 
}

template<typename Entier, int n> 
Entier Urne<Entier,n>::nb_boules() const
{
    Entier number = std::accumulate(contenu.begin(), contenu.end(), 0, [](Entier acc, const Entier& d)
    {
        return acc+d; 
    }); 
    return number; 
}

template<typename Entier, int n>
double Urne<Entier,n>::fraction(int j) const
{
    return contenu[j]/(double)nb_boules(); 
}

template<typename Entier, int n> 
std::ostream& operator<<(std::ostream& out, const Urne<Entier,n>& U)
{
    out << U.nb_boules() << "\n"; 
    for(const Entier& e : U.contenu)
    {
        out << e << "\t"; 
    }
    return out; 
}

template<typename Entier, int n>
template<typename Update, typename RNG>
void Urne<Entier,n>::maj(Update f, RNG& G)
{
    std::discrete_distribution<int> random_color(contenu.begin(), contenu.end()); 
    int j = random_color(G);
    f(j,contenu); 
}

template<typename Entier, int n>
template<typename Update, typename RNG>
void Urne<Entier, n>::maj_p_fois(Update f, int p, RNG& G)
{
    for(int i = 0; i < p; ++i)
    {
        maj(f,G); 
    }
}