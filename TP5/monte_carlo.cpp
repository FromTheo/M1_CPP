#include "monte_carlo.hpp"

bool Histogramme::operator+=(double x)
{
    if(x>=lbound && x<= ubound)
    {
        int index=(int)((x-lbound)/box_width);
        echantillon[index]++;
        if(x<=ubound-box_width && x<=ubound)
        {
            echantillon[nb_boxes+1]++; 
        }
        return true;
    }
    return false; 
}

void Histogramme::operator/=(int n)
{
    transform(echantillon.begin(), echantillon.end(), echantillon.begin(), [&n](double d)
    {
        return d /= (double) n; 
    });

    /* Alternative :
    for_each(echantillon.begin(), echantillon.end(), [&n](double& d)
    {
        d/=n; 
    }); */
}

std::ostream& operator<<(std::ostream& out, const Histogramme& H)
{
    for(int i=0; i< H.nb_boxes+1; i++)
    {
        out << H.lbound+i*H.box_width << "\t" << H.echantillon[i] << "\n";
    }
    return out; 
}
