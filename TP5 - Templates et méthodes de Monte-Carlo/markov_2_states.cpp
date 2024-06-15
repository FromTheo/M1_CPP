#include "markov_2_states.hpp"

void Stat2states::operator+=(int x)
{
    if(x==1)
    {
        visit1++;
    }
    if(x==2)
    {
        visit2++; 
    }
}

double Stat2states::operator/=(int n)
{
    return (visit1+visit2)/(double)n;
}

std::ostream& operator<<(std::ostream& out, const Stat2states& S)
{
    double n=(double)S.visit1+S.visit2;
    out << (1*S.visit1)/(double)n;
    out << (2*S.visit2)/(double)n; 
    return out; 
}