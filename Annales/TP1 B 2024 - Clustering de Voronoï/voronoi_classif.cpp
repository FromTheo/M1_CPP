#include "voronoi_classif.hpp"

using namespace std; 

Voronoi_classifier::Voronoi_classifier(std::vector<Point2D> & v) : clusters(v.size()), nb_points(0)
{
    for(int i = 0; i < v.size(); ++i)
    {
        clusters[i].center = v[i]; 
    }
}

void Voronoi_classifier::add_point(Point2D p)
{
    auto it = min_element(clusters.begin(), clusters.end(), [&p](const Cluster& c1, const Cluster& c2)
    {
        return p.dist_2(c1.center) < p.dist_2(c2.center); 
    });
    (*it).close_points.insert(p); 
    nb_points++; 
}

void Voronoi_classifier::operator+=(Point2D p)
{
    add_point(p); 
}

std::vector<int> Voronoi_classifier::cluster_sizes() const
{
    std::vector<int> v(nb_of_clusters()); 
    std::transform(clusters.begin(), clusters.end(), v.begin(), [](const Cluster& c1)
    {
        return c1.close_points.size(); 
    });
    return v; 
}

void Voronoi_classifier::clear_clusters()
{
    for(Cluster& C : clusters)
    {
        C.close_points.clear(); 
    }
    nb_points = 0; 
}

void Voronoi_classifier::classify(std::istream& in, int nb)
{
    for(int i = 0; i < nb; ++i)
    {
        double x,y; 
        in >> x >> y; 
        add_point(Point2D{x,y}); 
    }
}

std::vector<double> Voronoi_classifier::mean_distance_square() const
{
    std::vector<double> res;
    for(const Cluster& C : clusters)
    {
        double to_add = 0.0; 
        for(const Point2D x : C.close_points)
        {
            to_add += x.dist_2(C.center); 
        }
        to_add /= (double)(C.close_points.size());
        res.push_back(to_add); 
    }
    return res; 
}

int Voronoi_classifier::add_center(Point2D new_center)
{
    set<Point2D> S; 
    for(int k = 0; k < nb_of_clusters(); k++)
    {
        set<Point2D> P_prime; 
        for(const Point2D& p : clusters[k].close_points)
        {
            if(new_center.dist_2(p) < clusters[k].center.dist_2(p)) S.insert(p); 
            else P_prime.insert(p); 
        }
        clusters[k].close_points = P_prime; 
    }
    clusters.push_back(Cluster{new_center,S});
    return clusters.back().close_points.size(); 
}

void Voronoi_classifier::print(std::ostream& out) const
{
    for(int k = 0 ; k < nb_of_clusters() ; ++k)
    {
        out << clusters[k].center.x << " " << clusters[k].center.y << " -1" << "\n"; 
        for(const Point2D& p : clusters[k].close_points)
        {
            out << p.x << " " << p.y << " k" << "\n"; 
        } 
    }
}


std::ostream& operator<<(std::ostream& out, const Voronoi_classifier& V)
{
    for(const Cluster& C : V.clusters)
    {
        out << "Center : ( " << C.center.x << ", " << C.center.y << " )" << "\n"; 
        if(C.close_points.empty())
        {
            out << "Vide" << "\n"; 
        }
        else
        {
            for(const Point2D& p : C.close_points)
            {
                out << "( " << p.x << ", " << p.y << " )" << "\n"; 
            }
        }
    }
    return out; 
}