#include "histogramme.hpp"

void Histogramme::print(std::ostream& out) const
{
    double middle_point;
    double normalized_value;
    int total_number_points = nb_out + std::accumulate(bars.begin(),bars.end(),0);
    for (int i = 0; i < bars.size(); i++)
    {
        middle_point = a+(i+0.5)*delta;
        normalized_value = bars[i]/double(total_number_points);
        out << middle_point << "\t" << normalized_value << "\n";
    }    
}

void Histogramme::reset()
{
    std::fill(bars.begin(), bars.end(), 0); 
    nb_out = 0; 
}

bool Histogramme::operator+= (double x)
{
    int k = floor((x-a)/delta);
    if((k >= 0) && (k < bars.size()))
    { 
        bars[k]++;
        return true; 
    }
    else 
    { 
        nb_out++;
        return false;
    }
}