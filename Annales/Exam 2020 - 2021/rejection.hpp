#include <random>
#include <cmath> 
#include <vector>
#include <algorithm> 
#include <fstream> 
#include <tuple> 
#include <chrono> 
#include <numeric> 

template<class RV, class DensityY, class DensityX, class E>
class Rejection_distribution;

class PiecewiseConstant_distribution;

struct Box;

class PiecewiseConstant_distribution; 


template<class RV, class DensityY, class DensityX, class E>
class Rejection_distribution
{
    private : 
    RV X; 
    DensityY fY; 
    DensityX fX; 
    double C; 
    std::uniform_real_distribution<double> U; 
    unsigned int steps;

    public : 
    Rejection_distribution(const RV& X0, const DensityY& fY0, const DensityX& fX0, double C0) : X(X0), fY(fY0), fX(fX0), C(C0), U(0.0,1.0), steps(0) {}

    template<class RNG>
    E operator()(RNG& G); 
    double density_wanted(const E& x) const {return fY(x);}
    double density_simulated(const E& x) const {return fX(x);} 
    double constante() const {return C;}
    double& constante() {return C;}
    unsigned int get_steps() const {return steps;}


};

template<class RV, class DensityY, class DensityX, class E>
template<class RNG>
E Rejection_distribution<RV, DensityY, DensityX, E>::operator()(RNG& G)
{
    steps = 0; 
    bool rejet = true; 
    int compteur = 0; 
    E x; 
    double u; 
    while(rejet)
    {
        x = X(G); 
        u = U(G); 
        compteur++; 
        if(u*C*density_simulated(x) < density_wanted(x))
        {
            rejet = false; 
        }
    }
    steps += compteur;
    return x; 
}

struct Box
{
    double left;   //a_k 
    double right;  //b_k 
    double height; //h_k
    Box(double l = 0, double r = 0, double h = 0) : left(l), right(r), height(h) {}
    friend std::ostream& operator<<(std::ostream& out, const Box& B); 
    friend std::istream& operator>>(std::istream& in, Box& B); 
};

class PiecewiseConstant_function
{
    private : 
    std::vector<Box> boxes; 

    public : 
    friend class PiecewiseConstant_distribution;
    PiecewiseConstant_function() {} 
    template<class Iter>
    PiecewiseConstant_function(Iter leftbegin, Iter leftend, Iter rightbegin, Iter heightbegin); 
    double operator()(double x) const; 
    int nb_of_boxes() const {return boxes.size();}
    bool check_ranges() const; 
    bool check_disjoint() const;
    friend std::ostream& operator<<(std::ostream& out, const PiecewiseConstant_function& f);  
    friend std::istream& operator>>(std::istream& in, PiecewiseConstant_function& f);  
};

template<class Iter>
PiecewiseConstant_function::PiecewiseConstant_function(Iter leftbegin, Iter leftend, Iter rightbegin, Iter heightbegin)
{
    std::vector<double> gauche; 
    for(Iter it = leftbegin; it != leftend; ++it)
    {
        gauche.push_back(*it); 
    }
    std::vector<double> droite(gauche.size()), haut(gauche.size()); 
    for(int i = 0; i < gauche.size(); ++i)
    {
        droite[i] = *rightbegin; 
        haut[i] = *heightbegin; 
        rightbegin++; 
        heightbegin++; 
    }
    std::vector<Box> boites(gauche.size()); 
    for(int i = 0; i < gauche.size(); ++i)
    {
        boites[i] = Box(gauche[i], droite[i], haut[i]);
    }
    std::sort(boites.begin(), boites.end(), [](const Box& a, const Box& b)
    {
        return a.right < b.right;
    }); 
    boxes = boites; 
}

class PiecewiseConstant_distribution
{
    private : 
    PiecewiseConstant_function f; 
    std::uniform_real_distribution<double> U; 
    std::vector<double> cumul_area; //CA_k 

    public : 
    template<class Iter>
    PiecewiseConstant_distribution(Iter leftbegin, Iter leftend, Iter rightbegin, Iter heightbegin); 

    int random_box(double u) const; 
    template<class RNG> 
    double operator()(RNG& G); 


};

template<class Iter>
PiecewiseConstant_distribution::PiecewiseConstant_distribution(Iter leftbegin, Iter leftend, Iter rightbegin, Iter heightbegin) : U(0.0,1.0)
{
    f = PiecewiseConstant_function(leftbegin, leftend, rightbegin, heightbegin); 
    std::vector<double> CA(f.nb_of_boxes()); 
    double acc = 0.0; 
    for(int i = 0; i < CA.size(); ++i)
    {
        acc += f.boxes[i].height * (f.boxes[i].right - f.boxes[i].left); 
        CA[i] = acc; 
    }
    cumul_area = CA; 
}

template<class RNG> 
double PiecewiseConstant_distribution::operator()(RNG& G)
{
    double u = U(G);
    int k = random_box(u); 
    return f.boxes[k].left + u * (f.boxes[k].right - f.boxes[k].left);
}

template<class RealDistri, class RNG>
std::tuple<double, double, double> eval_perf(RealDistri& X, RNG& G, int nb_samples)
{
    auto start = std::chrono::system_clock::now(); 
    std::vector<double> v(nb_samples);
    for(int i = 0; i < v.size(); ++i)
    {
        v[i] = X(G); 
    }
    auto stop = std::chrono::system_clock::now(); 
    std::chrono::duration<double> diff = stop - start; 
    double t = diff.count(); 
    double m = std::accumulate(v.begin(), v.end(), 0.0, [](double acc, double &d)
    {
        return acc+d;
    })/(double)v.size(); 
    double var = std::accumulate(v.begin(), v.end(), 0.0, [&m](double acc, double &d)
    {
        return acc + (d-m)*(d-m); 
    })/(double)v.size(); 
    double sigma = std::sqrt(var); 
    return std::make_tuple(t,m,sigma); 
}   