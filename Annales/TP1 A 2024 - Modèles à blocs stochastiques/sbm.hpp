#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <fstream>
#include <algorithm> 
#include <vector> 
#include <random>

using MatDouble = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>; 
using VecDouble = Eigen::Vector<double,Eigen::Dynamic>; 
using MatInt = Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic>; 
using VecInt = Eigen::Vector<int,Eigen::Dynamic>; 

class Graph
{
    private : 
    MatInt m_adj; 
    bool m_directed;
    VecInt m_Z; 

    public : 
    // Constructeurs : 
    Graph(MatInt A, bool directed = true, VecInt Z = VecInt()) : m_adj(A), m_directed(directed), m_Z(Z) {}
    Graph(std::istream& in); 

    // Accesseurs : 
    MatInt matrice_adjacence() const {return m_adj;}
    bool dirige() const {return m_directed;}
    VecInt var_latentes() const {return m_Z;}

    // Méthodes : 
    int nb_noeuds() const {return m_adj.cols();}
    int nb_blocs() const; 
    MatInt one_hot_Z() const; 
    VecInt count_statistics_s() const; 
    MatInt count_statistics_a() const; 
    MatInt count_statistics_b() const; 

    // Fonctions amies : 
    friend std::ostream& operator<<(std::ostream& out, const Graph& G); 
};

class SBM 
{
    private : 
    std::vector<double> m_pi; 
    double m_alpha; 
    bool m_directed; 

    public : 
    SBM(std::vector<double> pi, double alpha, bool directed) : m_pi(pi), m_alpha(alpha), m_directed(directed) {}

    int get_K() const {return m_pi.size();}
    Graph generate_graph(int n, std::mt19937_64& G); 
};