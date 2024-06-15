#include <vector> 
#include <algorithm>       //std::transform
#include <fstream> 

template<typename Statistique, typename RandomVariable, typename Measurement, typename RNG> 
void MonteCarlo(Statistique& res, RandomVariable& X, const Measurement& f, RNG& G, long unsigned int n)
{
    for(int i = 0; i < n; ++i)
    {
        res += f(X(G)); 
    }
    res /= (double) n; 
}

/* Prérequis :
- La classe RandomVariable possède un template de méthode operator() renvoyant une simulation de v.a. X.
- La fonction f possède un opérateur () appelable sur type de retour de l'opérateur précédent de RandomVariable.
- Le classe Statistique possèdé un opérator += qui peremt d'incorporer une nouvelle valeur dans les statistiques,
  ainsi qu'un opérateur de normalisation /= par un double. */


class DoubleMeanVar
{
    protected : 
    double m;  //Moment d'ordre 1. 
    double v;  //Moment d'ordre 2.

    public : 
    DoubleMeanVar(double x = 0.0) : m(x), v(0.0) {}
    void operator +=(double x) {m += x; v += x*x;}
    void operator /=(double x) {m /= x; v /=x;} 
    double moyenne() const {return m;}
    double variance() const {return v-m*m;}
};

class Histogramme 
{
    protected : 
    std::vector<double> echantillon; 
    unsigned int nb_boxes; 
    double lbound; 
    double ubound;
    double box_width;  //Ce champ privé n'est pas primordial mais permet d'éviter d'exprimer la largeur avec ubound, lbound, nb_boxes.

    public : 
    Histogramme(double min, double max, unsigned int n) : echantillon(n), nb_boxes(n), lbound(min), ubound(max), box_width((ubound-lbound)/(double)nb_boxes) {}
    bool operator+= (double x); 
    void operator/= (int n); 
    friend std::ostream& operator<<(std::ostream& out, const Histogramme& H); 
};