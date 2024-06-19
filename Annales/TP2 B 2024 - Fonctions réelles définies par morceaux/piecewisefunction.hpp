#include <vector>
#include <fstream>
#include <utility>

template <class Domain, class Value> 
    bool test_if_contains(const Domain & D, const Value & v);

template <class Domain, class Function> 
    class PiecewiseFn;
    
template <class Domain, class Function> 
    PiecewiseFn<Domain, Function> operator+(const PiecewiseFn<Domain, Function>& f, const PiecewiseFn<Domain, Function>& g);

template <class Value> 
    class Affine_Fn;

struct Segment 
{
    double left;
    double right;
    Segment(double a=0.,double b=1.): left(a), right(b) {};
    bool contains(double x) const { return (left<x) && (x<right); } 
};

std::istream& operator >>(std::istream & is, Segment & S) 
{
    return is >> S.left >> S.right;
}

template <class Domain, class Value>
bool test_if_contains(const Domain & D, const Value & v) 
{
    if(D.contains(v)) return true; 
    return false; 
}

template <class Domain, class Function> 
class PiecewiseFn 
{
    private:
        std::vector<std::pair<Domain, Function>> pieces;
        double default_v;
    public:
        // Constructeurs : 
        PiecewiseFn(const double & v=0) : pieces(), default_v(v) {} 

        // Accessuers, Mutateurs : 
        int nb_subsets() const {return pieces.size();}

        // Méthodes :
        void add_piece(const Domain & t, const Function & f) {pieces.push_back(std::make_pair(t,f));}
        template <class Argument> 
        double operator() (const Argument & y) const;
        template <class Argument>
        bool test_overlap(const Argument& a) const; 

        // Fonctions amies : 
        friend PiecewiseFn<Domain, Function> operator+ <>(const PiecewiseFn<Domain, Function>& f, const PiecewiseFn<Domain, Function>& g);
};

template<class Domain, class Function>
template <class Argument> 
double PiecewiseFn<Domain, Function>::operator() (const Argument & y) const
{
    for(int i = 0; i < nb_subsets(); ++i)
    {
        if(test_if_contains(pieces[i].first, y)) return pieces[i].second(y); 
    }
    return default_v; 
}

template<class Domain, class Function>
template <class Argument>
bool PiecewiseFn<Domain, Function>::test_overlap(const Argument& a) const
{
    int compteur = 0; 
    for(const Domain& D : pieces.first)
    {
        if(D.contains(a)) compteur++; 
    }
    if(compteur <= 1) return false;
    return true; 
}

template <class Value> 
class Affine_Fn 
{
    private:
        Value a;
        Value b;
    public:
        Affine_Fn(const Value & a0, const Value & b0) : a(a0), b(b0) {}
        Value operator () (const Value & x ) const {return a * x + b;}
};
