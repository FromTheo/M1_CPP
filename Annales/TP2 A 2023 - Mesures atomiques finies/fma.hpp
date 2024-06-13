#include <map> 
#include <numeric>      //std::accumulate 
#include <utility>      //std::pair
#include <type_traits>  //std::invoke_result_t 
#include <fstream> 

//Forward declarations : 
template <class E> 
    class Finite_atomic_measure;

template <class E> 
std::ostream& operator<<(std::ostream& out, const Finite_atomic_measure<E>& F); 

template <class E>
std::istream& operator>>(std::istream& in, Finite_atomic_measure<E>& F); 

template <class E1, class Function>  
    Finite_atomic_measure< std::invoke_result_t< Function, E1> > image(const Finite_atomic_measure<E1> & mu, const Function & f);

template<class E>
Finite_atomic_measure<E> operator+(Finite_atomic_measure<E>& F1, Finite_atomic_measure<E>& F2);



template <class E>
class Finite_atomic_measure 
{
	private:
        std::map<E,double> mass; 
    public:
        Finite_atomic_measure() = default; 
        template<typename Iterator> 
        Finite_atomic_measure(Iterator deb, Iterator fin);
        
        std::map<E,double> atomic_masses() const {return mass;} 
        int nb_of_atoms() const {return mass.size();}
        double total_mass() const; 
		void add_mass(const E & point, double mass_value) {mass[point]+=mass_value;}
        
        template <class Domain> 
        double measure(const Domain &) const; 
		template <class RealFunction_on_E> 
        double integral(const RealFunction_on_E & f) const;

        friend std::ostream& operator<< <>(std::ostream& out, const Finite_atomic_measure<E>& F);   
        friend std::istream& operator>> <>(std::istream& in, Finite_atomic_measure<E>& F); 
        friend Finite_atomic_measure<E> operator+ <>(Finite_atomic_measure<E>& F1, Finite_atomic_measure<E>& F2); 
};

template<typename E> 
template<typename Iterator> 
Finite_atomic_measure<E>::Finite_atomic_measure(Iterator deb, Iterator fin)
{
    for(Iterator it = deb; it != fin; ++it)
    {
        mass[*it]++; 
    }
}

template <class E>
double Finite_atomic_measure<E>::total_mass() const
{
    double resultat = std::accumulate(mass.begin(), mass.end(), 0.0, [](double acc, const std::pair<E,double>&p)
    {
        return acc+p.second; 
    }); 
    return resultat; 
}

template <class E> 
std::ostream& operator<<(std::ostream& out, const Finite_atomic_measure<E>& F)
{
    out << F.nb_of_atoms() << "\n"; 
    for(const std::pair<E,double>& p : F.mass)
    {
        out << p.first << " "  << p.second << "\n"; 
    }
    return out; 
}

template<class E>
std::istream& operator>> (std::istream& in, Finite_atomic_measure<E>& F)
{
    int taille; 
    in >> taille; 
    for(int i = 0; i < taille; ++i)
    {
        E x; 
        double a; 
        in >> x >> a; 
        F.add_mass(x,a); 
    }
    //Si la taille n'était pas accessible on aurait pu avoir recourt à in.eof() ou une boucle while.
    return in; 
}

template <class E>
template <class Domain> 
double Finite_atomic_measure<E>::measure(const Domain & D) const
{
    double resultat = 0.0; 
    for(const std::pair<E,double>& p : mass)
    {
        if(D.contains(p.first)) resultat += p.second; 
    }
    return resultat; 
}

template <class E> 
template <class RealFunction_on_E> 
double Finite_atomic_measure<E>::integral(const RealFunction_on_E & f) const
{
    double resultat = 0.0; 
    for(const std::pair<E,double>& p : mass)
    {
        resultat += p.second * f(p.first); 
    }
    return resultat; 
}

template <class E, class Function>  
Finite_atomic_measure< std::invoke_result_t< Function, E> > image(const Finite_atomic_measure<E> & mu, const Function & f)
{
    Finite_atomic_measure< std::invoke_result_t< Function, E> > resultat; 
    for(const std::pair<E,double>& p : mu.atomic_masses())
    {
        resultat.add_mass(f(p.first), p.second); 
    }
    return resultat; 
}

template<class E>
Finite_atomic_measure<E> operator+(Finite_atomic_measure<E>& F1, Finite_atomic_measure<E>& F2)
{
    Finite_atomic_measure<E> resultat; 
    for(const std::pair<E,double>& p : F1.atomic_masses())
    {
        resultat.mass[p.first] += p.second; 
    }
    for(const std::pair<E,double>& p : F2.atomic_masses())
    {
        resultat.mass[p.first] += p.second;   
    }
    return resultat; 
}