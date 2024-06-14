#include "regles.hpp"

void Friedman2::operator()(int j, std::array<int,2>& v)
{
    for(int i = 0; i < v.size(); ++i)
    {
        if(i == j) v[j] += q;
        else v[i] += r; 
    }
}