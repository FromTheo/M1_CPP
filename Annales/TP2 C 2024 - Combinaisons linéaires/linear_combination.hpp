#include <vector> 
#include <utility> 
#include <fstream> 
#include <algorithm> 
#include <array> 
#include <iostream> 

template<typename V, unsigned long n> 
std::array<V,n> operator*(const V& valeur, const std::array<V,n>& v)
{
    std::array<V,n> res; 
    for(int i=0; i<n; i++)
    {
        res[i] = v[i]*valeur; 
    }
    return res; 
}

template<typename V, unsigned long n> 
std::array<V,n> operator+(const std::array<V,n>& v1, const std::array<V,n>& v2)
{
    std::array<V,n> res; 
    for(int i=0; i<n; i++)
    {
        res[i] = v1[i] + v2[i]; 
    }
    return res; 
}

template<typename V, unsigned long n> 
std::array<V,n> operator-(const std::array<V,n>& v1, const std::array<V,n>& v2)
{
    std::array<V,n> res; 
    for(int i=0; i<n; i++)
    {
        res[i] = v1[i] - v2[i]; 
    }
    return res; 
}


template <typename Value> 
class LinearCombination; 

template <typename Value> 
std::ostream& operator<<(std::ostream& out, const LinearCombination<Value>& L);

template <typename Value> 
LinearCombination<Value> operator*(const Value& V, const LinearCombination<Value>& L); 

template<typename Value> 
LinearCombination<Value> operator+(const LinearCombination<Value>& L1, const LinearCombination<Value>& L2); 

template<typename Value> 
LinearCombination<Value> operator-(const LinearCombination<Value>& L1, const LinearCombination<Value>& L2); 

template<typename V, unsigned long n>
std::pair< bool, std::array<V,n> > ResolutionSysteme( std::vector<LinearCombination<V>> L , std::array<V,n> w); 

template <typename Value> 
class LinearCombination{
    private:
        int n; //correspond à la taille de la combinaison linéaire
        std::vector<Value> coeff; //correspond aux a_i
    public:
        LinearCombination(int n0=0) : n(n0), coeff(n0) {}
        LinearCombination(const std::vector<Value>& v) : n(v.size()), coeff(v) {} 

        int size() const {return n;}
        Value operator[](int i) const {return coeff[i];}
        Value& operator[](int i) {return coeff[i];}
        template <class X> 
        X operator()(const std::vector<X>&) const;

        friend std::ostream& operator<< <>(std::ostream& out, const LinearCombination<Value>& L);
        friend LinearCombination<Value> operator* <>(const Value& V, const LinearCombination<Value>& L); 
        friend LinearCombination<Value> operator+ <> (const LinearCombination<Value>& L1, const LinearCombination<Value>& L2); 
        friend LinearCombination<Value> operator- <> (const LinearCombination<Value>& L1, const LinearCombination<Value>& L2); 
        template<typename V, unsigned long n>
        friend std::pair< bool, std::array<V,n> > ResolutionSysteme( std::vector<LinearCombination<V>> L , std::array<V,n> w);
        
};

template <typename Value> 
std::ostream& operator<<(std::ostream& out, const LinearCombination<Value>& L)
{
    for(int i=0; i<L.n; i++)
    {
        out << L[i] << "x_" << i << " + ";  
    }
    //out << L[L.size()] << "x_" << L.size()-1; 
    return out; 
}

template <typename Value> 
LinearCombination<Value> operator*(const Value& V, const LinearCombination<Value>& L)
{
    std::vector<Value> coefficients(L.coeff); 
    std::transform(coefficients.begin(), coefficients.end(), coefficients.begin(), [&V](const Value& d)
    {
        return d*V; 
    }); 
    return LinearCombination<Value>(coefficients); 
}

template<typename Value> 
LinearCombination<Value> operator+(const LinearCombination<Value>& L1, const LinearCombination<Value>& L2)
{
    std::vector<Value> res(L1.coeff.size()); 
    for(int i=0; i<L1.coeff.size(); i++)
    {   
        res[i] = L1[i]+L2[i];
    }
    return LinearCombination<Value>(res); 
}


template<typename Value> 
LinearCombination<Value> operator-(const LinearCombination<Value>& L1, const LinearCombination<Value>& L2)
{
    std::vector<Value> res(L1.coeff.size()); 
    for(int i=0; i<L1.coeff.size(); i++)
    {   
        res[i] = L1[i]-L2[i];
    }
    return LinearCombination<Value>(res); 
}

template <class Value> 
template <class X> 
X LinearCombination<Value>::operator()(const std::vector<X>& v) const
{
    X value; 
    for(int i=0; i<coeff.size(); i++)
    {
        value = value + coeff[i]* v[i];  
    }
    return value; 
}

std::pair<std::vector<double>,std::vector<double>> ReadData(std::istream& in)
{
    std::vector<double> x_values; 
    std::vector<double> y_values; 
    double x; 
    while(in >> x)
    {
        x_values.push_back(x); 
        double y; 
        in >> y; 
        y_values.push_back(y); 
    }
    return std::make_pair(x_values,y_values); 

}

template <typename Fonction>
std::vector<double> AppFct(const Fonction& f, const std::vector<double>& points)
{
    return std::transform(points.begin(), points.end(), [&f](double &d)
    {
        return f(d);
    }); 
}

template<typename V, unsigned long n>
std::pair< bool, std::array<V,n> > ResolutionSysteme( std::vector<LinearCombination<V>> L , std::array<V,n> w)
{
    std::array<V,n> resultat  = w;
    for(int k=0; k<n; k++)
    {
        if(L[k][k]!=0)
        {
            V pivot = L[k][k];
            L[k] = (1.0/pivot)*L[k]; 
            resultat[k] = (1.0/pivot)*resultat[k];
            for(int i=0; i<n; i++)
            {
                if(i!=k)
                {
                    V coeff = L[i][k];
                    L[i] = L[i]- coeff*L[k]; 
                    resultat[i] = resultat[i] - coeff*resultat[k];
                }
            }
        }
        else 
        {
            std::cout << "Il n'y a pas de solution." << std::endl; 
            return std::make_pair(false, std::array<V,n>()) ; 
        }
    }
    return std::make_pair(true, resultat); 
}
