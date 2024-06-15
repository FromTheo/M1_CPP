#include <iostream>

#include "voronoi_classif.hpp"

using namespace std; 

int main()
{
    vector<Point2D> centers{ Point2D{0.0,0.0}, Point2D{5.,3.}, Point2D{-2.,4.}, Point2D{-1.,-4.} };
    Voronoi_classifier VC(centers);
    ifstream fichier("cloud.txt"); 
    VC.classify(fichier,500); 

    vector<int> nbs = VC.cluster_sizes();
    cout << "Les tailles des quatres clusters sont :";
	for(const int& n : nbs) 
    { 
        cout << n << " "; 
    }
    cout << endl; 
    // Output : Les tailles des quatres clusters sont : 138 127 107 128 

    vector<double> v_k = VC.mean_distance_square(); 
    cout << "Valeurs des v_k : "; 
    for(const double &d : v_k)
    {
        cout << d << " ";
    }
    cout << endl; 
    //Output : 4.8247 7.98358 7.25505 6.43587 

    VC.add_center(Point2D{0.,-1.});
    vector<int> nbs2 = VC.cluster_sizes();
    cout << "Les tailles des cinq clusters sont :";
	for(const int& n : nbs2) 
    { 
        cout << n << " "; 
    }
    cout << endl; 
    //Output : Les tailles des cinq clusters sont : 75 126 107 115 77 

    return 0; 
}