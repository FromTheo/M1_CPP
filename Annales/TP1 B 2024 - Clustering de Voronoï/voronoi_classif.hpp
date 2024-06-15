#include <set>
#include <algorithm> 
#include <fstream> 
#include <vector> 

struct Point2D 
{
    double x,y; 
    //Point2D(double x, double y) : x(x), y(y) {} 
    double dist_2(Point2D u) const {return (x-u.x)*(x-u.x) + (y-u.y)*(y-u.y);}
    bool operator<(Point2D u) const {if( x!= u.x) return (x < u.x); else return (y < u.y);}
};

struct Cluster 
{
    Point2D center; 
    std::set<Point2D> close_points; 
};

class Voronoi_classifier
{
    private : 
    std::vector<Cluster> clusters; 
    int nb_points; 

    public : 
    // Constructeurs : 
    Voronoi_classifier(std::vector<Point2D> & v); 

    // Accesseurs / Mutateurs : 
    int nb_of_clusters() const {return clusters.size();}
    int nb_of_data_points() const {return nb_points;}

    // Méthodes : 
    void add_point(Point2D p);
    void operator+=(Point2D p); 
    std::vector<int> cluster_sizes() const;   
    void clear_clusters(); 
    void classify(std::istream& in, int nb); 
    std::vector<double> mean_distance_square() const; 
    int add_center(Point2D new_center); 
    void print(std::ostream& out) const; 

    // Fonctions amies :
    friend std::ostream& operator<<(std::ostream& out, const Voronoi_classifier& V); 
};