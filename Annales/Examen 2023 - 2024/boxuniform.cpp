#include "boxuniform.hpp"

void BoxUniform::scale(const double &s)
{
    std::transform(box_coord.begin(), box_coord.end(), box_coord.begin(), [&s](std::pair<double,double>& p)
    {
        return std::make_pair(s * p.first, s * p.second); 
    }); 
}

double BoxUniform::volume() const
{
    return std::accumulate(box_coord.begin(), box_coord.end(), 0.0, [](double acc, const std::pair<double, double>& p)
    {
        return acc + (p.second - p.first); 
    });
}

BoxUniform operator*(const BoxUniform& A, const BoxUniform& B)
{
    std::vector<double> a_A(A.dimension()); 
    std::vector<double> b_A(A.dimension()); 
    std::transform(A.box_coord.begin(), A.box_coord.end(), a_A.begin(), [](const std::pair<double, double>& p)
    {
        return p.first; 
    });  
    std::transform(A.box_coord.begin(), A.box_coord.end(), b_A.begin(), [](const std::pair<double, double>& p)
    {
        return p.second; 
    });  

    std::vector<double> a_B(B.dimension()); 
    std::vector<double> b_B(B.dimension()); 
    std::transform(B.box_coord.begin(), B.box_coord.end(), a_B.begin(), [](const std::pair<double, double>& p)
    {
        return p.first; 
    });  
    std::transform(B.box_coord.begin(), B.box_coord.end(), b_B.begin(), [](const std::pair<double, double>& p)
    {
        return p.second; 
    }); 
    std::vector<double> a(A.dimension()+B.dimension()); 
    std::vector<double> b(A.dimension()+B.dimension()); 
    std::copy(a_A.begin(), a_A.end(), a.begin()); 
    std::copy(b_A.begin(), b_A.end(), b.begin()); 
    std::copy(a_B.begin(), a_B.end(), a.begin()+A.dimension()); 
    std::copy(b_B.begin(), b_B.end(), b.begin()+B.dimension()); 
    return BoxUniform(a.begin(), a.end(), b.begin(), b.end()); 
    return BoxUniform(); 
}

std::ostream& operator<<(std::ostream& out, const BoxUniform& A)
{
    out << A.dimension() << "\n"; 
    for(const std::pair<double,double>& p : A.box_coord)
    {
        out << p.first << " " << p.second << "\n"; 
    }
    return out; 
}