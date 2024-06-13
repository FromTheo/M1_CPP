#include <iostream> 

#include "fma.hpp"
#include "geometry.hpp"

using namespace std;

int main() 
{
	ifstream fichier("atomic_data.txt"); 
	Finite_atomic_measure<double> F; 
	fichier >> F; 
	fichier.close(); 

	cout << "*** Masse totale: " << F.total_mass()<< "\n"; //Output : 42.2503
	Segment<double> S1(-3.,1.5), S2(0.5,4.2); 
	cout << "*** Mesure mu([-3,1.5]): " << F.measure(S1) << "\n";  //Output : 34.0778 
	cout << "*** Mesure mu([0.5,4.2]): " << F.measure(S2) << "\n"; //Output : 13.4099

	auto f = [](double x)->int
	{
		return (int)std::floor(x); 
	}; 
	Segment<int> S3(0,2), S4(-10,10); 
	cout << "*** Mesure de nu({0,1,2}) : " << image(F,f).measure(S3) << endl;     //Output : 16.4031
	cout << "*** Mesure de nu({-10,..,10}) : " << image(F,f).measure(S4) << endl; //output : 42.2503
	cout << "*** Mesure nu :\n" << image(F,f) << endl; 
	/* Output : 
	8
	-4 1.62706
	-3 3.32607
	-2 6.58399
	-1 12.9605
	0 8.07724
	1 6.09822
	2 2.22764
	3 1.3496  */

	
	return 0; 	
}
