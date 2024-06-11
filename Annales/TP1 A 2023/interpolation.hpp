#include <vector>
#include <fstream> 
#include <algorithm>        //std::max_element, std::min_element
#include <iterator>         //std::distance

class LagrangeInterpolation
{
    private : 
    std::vector<double> x_values; 
    std::vector<double> y_values; 

    public : 
    // Constructeurs : 
    LagrangeInterpolation() = default; 
    LagrangeInterpolation(double u, double delta, const std::vector<double>& y);
    LagrangeInterpolation(const std::vector<double>& x, const std::vector<double>& y) : x_values(x), y_values(y) {}

    // Méthodes ; 
    int nb_points() const {return x_values.size();}
    double operator()(double z) const; 
    double lower_bound() const {return *std::min_element(x_values.begin(), x_values.end());} 
    double upper_bound() const {return *std::max_element(x_values.begin(), x_values.end());}
    bool add_point(double, double); 

    // Fonctions amies : 
    friend std::ostream& operator<<(std::ostream& out, const LagrangeInterpolation& P); 
    friend std::istream& operator>>(std::istream& in, LagrangeInterpolation& P); 
    friend LagrangeInterpolation operator+(const LagrangeInterpolation& P, const LagrangeInterpolation& Q); 
};
