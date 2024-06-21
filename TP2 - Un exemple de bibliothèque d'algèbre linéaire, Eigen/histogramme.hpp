#include <vector>
#include <fstream> 
#include <algorithm> 
#include <numeric>

class Histogramme
{
    private : 
    double a; 
    double b;
    double delta; 
    std::vector<int> bars; 
    int nb_out; 

    public : 
    // Constructeur : 
    Histogramme(double a, double b, int N) : a(a), b(b), delta((b-a)/N), bars(N), nb_out(0) {} 

    // Accesseurs : 
    double lower_bound() const {return a;}
    double upper_bound() const {return b;}
    double nb_boxes() const {return bars.size();}
    int out_of_domain() const {return nb_out;}

    // Méthodes :
    void print(std::ostream& out) const; 
    void reset();

    //Surcharge : 
    bool operator+= (double x); 
};