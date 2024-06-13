#include <iostream> 

#include "interpolation.hpp"

using namespace std; 

int main()
{
    cout << " *** PARTIE 1 ***" << endl; 
    const LagrangeInterpolation P(0., 0.25, {1.,3.,2.,4.});
    cout << "P = " << endl << P << endl; 
    /* Output : 
    P = 
    4
    0 1
    0.25 3
    0.5 2
    0.75 4 */
    cout << "P contient " << P.nb_points() << " couples." << endl;     //Output : 4.
    cout << "L'abscisse minimale est  : " << P.lower_bound() << endl;  //Output : 0.
    cout << "L'abscisse maximale est : " << P.upper_bound() << endl;   //Output : 0.75 
    cout << "P(0.75) = " << P(0.75) << endl; //Output : 4.
    cout << "P(0.4) = " << P(0.4) << endl;   //Output : 2.376.
    cout << "P(0.1) = " << P(0.1) << endl;   //Output : 2.544. 

    LagrangeInterpolation Q(0., 0.25, {1.,3.,2.,4.}); 
    cout << "Ajout de (0.5,7) à Q : " << Q.add_point(0.5,7) << endl; //Output : Erreur : point déjà existant. 0.
    cout << "Ajout de (0.4,1.2) à Q : " << Q.add_point(0.4,1.2) << endl; //Output : 1. 
    cout << "Q = " << endl << Q << endl; 
    /* Output :
    Q = 
    5
    0 1
    0.25 3
    0.5 2
    0.75 4
    0.4 1.2 */
    cout << "Q(0.75) = " << Q(0.75) << endl; //Output : 4.
    cout << "Q(0.4) = " << Q(0.4) << endl;   //Output : 1.2.
    cout << "Q(0.1) = " << Q(0.1) << endl;   //Output : 4.728. 





    return 0; 
}