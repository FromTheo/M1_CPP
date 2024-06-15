#include "voronoi_classif.hpp"
#include <iostream>
#include <random>

using namespace std;

int main() 
{
    std::vector<Point2D> centers{ Point2D{0.2,0.2}, Point2D{0.8,0.8}, Point2D{0.3,0.7} };
	Voronoi_classifier VC(centers);
	VC.add_point(Point2D{0.5,0.});
	VC.add_point(Point2D{0.75,0.6});
	VC.add_point(Point2D{1.,0.2});


	cout << "--- VC contient " << VC.nb_of_clusters() << " clusters et " << VC.nb_of_data_points() << " points.\n";
	//Output : --- VC contient 3 clusters et 3 points.

	std::vector<int> nbs = VC.cluster_sizes();
    cout << "--- Les tailles des trois clusters sont :\n";
	for(int n : nbs) { cout << n << "\n"; }
	/* Output : 
	--- Les tailles des trois clusters sont :
	1
	2
	0 */

    cout << "--- Les clusters sont donnés par:\n" << VC;
	/* Output :
	--- Les clusters sont donnés par:
	Center : ( 0.2, 0.2 )
	( 0.5, 0 )
	Center : ( 0.8, 0.8 )
	( 0.75, 0.6 )
	( 1, 0.2 )
	Center : ( 0.3, 0.7 )
	Vide */

    VC.clear_clusters();
    cout << "--- Après effacement, il y a " << VC.nb_of_clusters() << " centres et " << VC.nb_of_data_points() << " point.\n";
	//Output : --- Après effacement, il y a 3 centres et 0 point.

    return 0;
}
