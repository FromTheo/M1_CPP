#include "vec.hpp"

V::V(int d, double a) : coeffs(d)
{
    fill(coeffs.begin(), coeffs.end(), a); 
}

double V::scal(const V& a) const
{
    double resultat = 0.0; 
    for(int i = 0; i < a.coeffs.size(); ++i)
    {
        resultat += coeffs[i]*a.coeffs[i]; 
    }
    return resultat; 
}

V operator+(const V& u, const V& v)
{
    std::vector<double> coeffs_w(u.coeffs.size()); 
    for(int i = 0; i < coeffs_w.size(); ++i)
    {
        coeffs_w[i] += u.coeffs[i]+v.coeffs[i];
    }
    return V(coeffs_w.begin(), coeffs_w.end()); 
}    
    
V operator*(const V&u, double a)
{
    std::vector<double> coeffs_w(u.coeffs.size()); 
    std::transform(u.coeffs.begin(), u.coeffs.end(), coeffs_w.begin(), [&a](double d)
    {
        return d*a; 
    });
    return V(coeffs_w.begin(), coeffs_w.end()); 
}

std::ostream& operator<<(std::ostream& out, const V& v)
{   
    for(const double& d : v.coeffs)
    {
        out << d << "  ";
    }
    return out; 
}

std::istream& operator>>(std::istream& in, V& v)
{
    std::vector<double> coeffs_finaux; 
    double d;
    while(in >> d)
    {
        coeffs_finaux.push_back(d); 
    }
    v.coeffs = coeffs_finaux; 
    return in; 
}