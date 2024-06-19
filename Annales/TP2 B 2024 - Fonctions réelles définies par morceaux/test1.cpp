#include <iostream>
#include "piecewisefunction.hpp"

using namespace std; 

PiecewiseFn<Segment,Affine_Fn<double>> make_tent_function(double a, double b, double h)
{
    PiecewiseFn<Segment, Affine_Fn<double>> f; 
    Segment s1(a, (a+b)/2), s2((a+b)/2,b); 
    Affine_Fn<double> g((2*h)/(b+a), -a*2*h/(b+a)); 
    Affine_Fn<double> k(-(2*h)/(b+a), b*2*h/(b+a)); 
    f.add_piece(s1,g);
    f.add_piece(s2,k); 
    return f; 
}   

int main() {
    auto Tent = make_tent_function(-1.,3.,5.);
    for(double x=-2.; x<4. ; x += 0.25 ) 
    {
        cout << x << ":\t" << Tent(x) << "\n"; 
    } 
    /*Output : 
    -2:	0
    -1.75:	0
    -1.5:	0
    -1.25:	0
    -1:	0
    -0.75:	1.25
    -0.5:	2.5
    -0.25:	3.75
    0:	5
    0.25:	6.25
    0.5:	7.5
    0.75:	8.75
    1:	0
    1.25:	8.75
    1.5:	7.5
    1.75:	6.25
    2:	5
    2.25:	3.75
    2.5:	2.5
    2.75:	1.25
    3:	0
    3.25:	0
    3.5:	0
    3.75:	0*/
    return 0;
}
