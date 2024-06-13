#include <iostream> 
#include "interpolation.hpp"

using namespace std; 

LagrangeInterpolation::LagrangeInterpolation(double u, double delta, const std::vector<double>& y) : y_values(y), x_values(y.size())
{
    for(int i = 0; i < y.size(); ++i)
    {
        x_values[i] = u + i * delta; 
    }
}   

double LagrangeInterpolation::operator()(double z) const
{
    double res = 0.0; 
    for(int j = 0; j < nb_points(); ++j)
    {
        double r_j = 1;
        for(int i = 0; i < nb_points(); ++i)
        {
            if(i != j)
            {
                r_j *= (z-x_values[i])/(x_values[j]-x_values[i]); 
            }
        }
        res += y_values[j]*r_j; 
    }
    return res; 
}

bool LagrangeInterpolation::add_point(double x, double y)
{
    auto it = find(x_values.begin(), x_values.end(), x);
    if(it != x_values.end())
    {
        cout << "Erreur : point déjà existant." << endl;
        return false;
    }
    x_values.push_back(x); 
    y_values.push_back(y); 
    return true; 
}

std::ostream& operator<<(std::ostream& out, const LagrangeInterpolation& P)
{
    out << P.nb_points() << "\n"; 
    for(int i = 0; i < P.nb_points(); ++i)
    {
        out << P.x_values[i] << " " << P.y_values[i] << "\n";
    }
    return out; 
}

std::istream& operator>>(std::istream& in, LagrangeInterpolation& P)
{
    int taille; 
    in >> taille; 
    P.x_values.resize(taille);  
    P.y_values.resize(taille);  
    for(int i = 0; i < taille; ++i)
    {
        double x, y;
        in >> x >> y;
        P.x_values[i] = x;
        P.y_values[i] = y;
    }
    return in; 
    /* Si on ne connaissait pas la taille des vecteurs à l'avance on utilise : 
    - soit une boucle while(in >> x >> y)
    - bool eof() const; */ 
}

LagrangeInterpolation operator+(const LagrangeInterpolation& P, const LagrangeInterpolation& Q)
{
    LagrangeInterpolation resultat;
    resultat.x_values.resize(P.x_values.size() + Q.x_values.size()); 
    resultat.y_values.resize(P.x_values.size() + Q.x_values.size()); 
    std::copy(P.x_values.begin(), P.x_values.end(), resultat.x_values.begin()); 
    std::copy(P.y_values.begin(), P.y_values.end(), resultat.y_values.begin()); 
    std::copy(Q.x_values.begin(), Q.x_values.end(), resultat.x_values.begin()+P.x_values.size()); 
    std::copy(Q.y_values.begin(), Q.y_values.end(), resultat.y_values.begin()+P.y_values.size()); 
    std::transform(resultat.x_values.begin(), resultat.x_values.begin()+P.nb_points(), resultat.y_values.begin(), resultat.y_values.begin()+P.nb_points(), [&](double x, double y)
    {
        return y+Q(x); 
    });
    std::transform(resultat.x_values.begin()+P.nb_points(), resultat.x_values.end(), resultat.y_values.begin()+P.nb_points(), resultat.y_values.end(), [&](double x, double y)
    {
        return y+P(x); 
    }); 
    return resultat; 
}