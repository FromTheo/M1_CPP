#include <iostream> 

#include "interpolation.hpp"

using namespace std; 

int main()
{
    ifstream file ("points.txt"); 
    LagrangeInterpolation P; 
    file >> P; 
    file.close();

    cout << "P = " << endl << P << endl;
    /* Output :
    P =  
    27
    -0.287352 -1.57932
    2.22556 8.25345
    0.623697 -0.948897
    0.0598242 -1.74259
    1.08238 0.6471
    1.85673 5.23665
    0.316851 -1.54253
    -0.259274 -1.61102
    0.167277 -1.69212
    2.30233 8.94864
    2.24968 8.46933
    0.58651 -1.04124
    2.00915 6.41844
    0.89086 -0.12169
    2.43587 10.2133
    -0.278406 -1.58978
    2.47702 10.6171
    0.516863 -1.19909
    0.878531 -0.166165
    0.125961 -1.71717
    0.319345 -1.53926
    -0.24615 -1.62472
    0.0744182 -1.73854
    1.79205 4.76274
    1.22085 1.2938
    1.22868 1.33266
    0.655491 -0.865518 */
    cout << "L'abscisse minimale est  : " << P.lower_bound() << endl;  //Output : -0.287352.
    cout << "L'abscisse maximale est : " << P.upper_bound() << endl;   //Output : 2.47702.
    cout << "P(0.5) = " << P(0.5) << endl;   //Output : -1.23435.
    cout << "P(1.0) = " << P(1.0) << endl;   //Output : 0.297951.
    return 0; 
}
