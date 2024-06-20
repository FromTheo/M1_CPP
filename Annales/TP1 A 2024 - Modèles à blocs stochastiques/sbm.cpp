#include "sbm.hpp"

Graph::Graph(std::istream& in)
{
    int n; 
    bool directed; 
    in >> n;
    in >> directed; 
    m_directed = directed; 
    MatInt A = MatInt::Zero(n,n); 
    VecInt Z = VecInt::Zero(n); 
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            int x;
            in >> x;
            A(i,j) = x; 
        }
    }
    if(!in.eof())
    {
        for(int i = 0; i < n; ++i)
        {
            int x; 
            in >> x;
            Z(i) = x;
        }
    }
    m_adj = A; 
    m_Z = Z; 
}

int Graph::nb_blocs() const
{
    return *std::max_element(m_Z.begin(), m_Z.end())+1;
}

MatInt Graph::one_hot_Z() const
{
    MatInt resultat = MatInt::Zero(nb_noeuds(), nb_blocs()); 
    for(int i = 0; i < nb_noeuds(); ++i)
    {
        resultat(i, m_Z(i)) = 1; 
    }
    return resultat; 
}

VecInt Graph::count_statistics_s() const
{
    MatInt M = one_hot_Z(); 
    VecInt s = VecInt::Zero(nb_blocs()); 
    for(int k = 0; k < nb_blocs(); ++k)
    {
        for(int i = 0; i < nb_noeuds(); ++i)
        {
            s(k) += M(i,k); 
        }
    }   
    return s; 
} 

MatInt Graph::count_statistics_a() const
{
    MatInt M = one_hot_Z(); 
    MatInt A = MatInt::Zero(nb_blocs(), nb_blocs());
    for(int k = 0; k < nb_blocs(); ++k)
    {
        for(int l = 0; l < nb_blocs(); ++l)
        {
            for(int i = 0; i < nb_noeuds(); ++i)
            {
                for(int j = 0; j < nb_noeuds(); ++j)
                {
                    if(i != j) A(k,l) += M(i,k) * M(j,l) * m_adj(i,j); 
                }
            }
        }
    }
    if(!m_directed)
    {
        for(int i = 0; i < nb_blocs(); ++i)
        {
            A(i,i) /= 2; 
        }
    }
    return A; 
}

MatInt Graph::count_statistics_b() const
{
    MatInt M = one_hot_Z(); 
    MatInt B = MatInt::Zero(nb_blocs(), nb_blocs());
    for(int k = 0; k < nb_blocs(); ++k)
    {
        for(int l = 0; l < nb_blocs(); ++l)
        {
            for(int i = 0; i < nb_noeuds(); ++i)
            {
                for(int j = 0; j < nb_noeuds(); ++j)
                {
                    if(i != j) B(k,l) += M(i,k) * M(j,l) * (1 - m_adj(i,j)); 
                }
            }
        }
    }
    if(!m_directed)
    {
        for(int i = 0; i < nb_blocs(); ++i)
        {
            B(i,i) /= 2; 
        }
    }
    return B; 
}

std::ostream& operator<<(std::ostream& out, const Graph& G)
{
    out << G.nb_noeuds() << "\n"; 
    out << G.dirige() << "\n"; 
    for(int i = 0; i < G.nb_noeuds(); ++i)
    {
        for(int j = 0; j < G.nb_noeuds(); ++j)
        {
            out << G.m_adj(i,j) << " ";
        }
        out << "\n"; 
    }
    for(int i = 0; i < G.nb_noeuds(); ++i)
    {
        out << G.m_Z(i) << " "; 
    }
    return out; 
}

Graph SBM::generate_graph(int n, std::mt19937_64& G)
{
    // Tirage des variables latentes : 
    std::discrete_distribution<int> Loi(m_pi.begin(), m_pi.end()); 
    VecInt Z = VecInt::Zero(n); 
    for(int i = 0; i < n; ++i)
    {
        int value = Loi(G); 
        Z(i) = value; 
    }

    // Tirage de la matrice d'adjacence : 
    MatInt A = MatInt::Zero(n,n); 
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            int k = Z(i), l = Z(j); 
            std::bernoulli_distribution B(std::pow(m_alpha,k*l)); 
            A(i,j) = B(G); 
        }
    }
    return Graph(A, m_directed, Z); 
}