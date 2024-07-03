#include <vector>
#include <cmath> 
#include <iostream> 
#include <complex> 
#include <type_traits>
#include <fstream> 
#include <algorithm> 
#include <utility> 
#include <numeric>

template<typename T>
bool is_zero(T a)
{
    return a == 0; 
}
template<> //spécialisation
bool is_zero(double a)
{
    return std::abs(a) < 1e-16; 
}
template<typename T> //surcharge 
bool is_zero(std::complex<T> a)
{
    return is_zero<T>(a.real()) && is_zero<T>(a.imag());
}

template<typename T>
bool is_one(T a)
{
    return a == 1; 
}
template<>
bool is_one(double a)
{
    return std::abs(a-1) < 1e-16; 
}
template<typename T> 
bool is_one(std::complex<T> a)
{
    return is_one<T>(a.real()) && is_one<T>(a.imag());
}

template<typename T> 
bool is_invertible(T x)
{
    if constexpr (std::is_integral<decltype(x)>::value)
    {
        return x == 1 || x == -1; 
    }
    else
    {
        return !is_zero(x);
    }
}

template<typename T>
class Polynome; 

template <class T> 
struct result_euclid_div 
{
	Polynome<T> quotient;
    Polynome<T> remainder;
    result_euclid_div(const Polynome<T> & q, const Polynome<T> & r): quotient(q), remainder(r) {}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Polynome<T>& P); 

template<typename T>
Polynome<T> operator+(const Polynome<T>& P, const Polynome<T>& Q); 

template<typename T>
Polynome<T> operator-(const Polynome<T>& P, const Polynome<T>& Q); 

template<typename T>
Polynome<T> operator*(const Polynome<T>& A, const Polynome<T>& B); 

template<typename T>
result_euclid_div<T> euclid_div(const Polynome<T>& A, const Polynome<T>& B);

template<typename T>
Polynome<T> operator/(const Polynome<T>& A, const Polynome<T>& B); 

template<typename T>
Polynome<T> operator%(const Polynome<T>& A, const Polynome<T>& B); 


template<typename T>
class Polynome
{
    private : 
    std::vector<T> coeff; 
    int n; 
    Polynome<T> extend(int m) const; 
    void adjust(); 

    public : 
    // Constructeurs : 
    Polynome() : n(-1), coeff{0} {}
    Polynome(const T& a, int m) : n(m), coeff(m+1) {coeff.back() = a;}
    Polynome(std::vector<T>& v) : n(v.size()-1), coeff(v) {}

    // Méthodes : 
    int degre() const {return n;}
    T operator[](int i) const;
    T operator()(T x) const;
    T dominant() const {return coeff.back();}

    // Fonctions amies : 
    friend std::ostream& operator<< <>(std::ostream& out, const Polynome<T>& P); 
    friend Polynome<T> operator+ <>(const Polynome<T>& P, const Polynome<T>& Q); 
    friend Polynome<T> operator- <>(const Polynome<T>& P, const Polynome<T>& Q); 
    friend Polynome<T> operator* <>(const Polynome<T>& A, const Polynome<T>& B); 
    friend Polynome<T> operator/ <>(const Polynome<T>& A, const Polynome<T>& B) {return euclid_div(A,B).quotient;}
    friend Polynome<T> operator% <>(const Polynome<T>& A, const Polynome<T>& B) {return euclid_div(A,B).remainder;}
};

template<typename T>
Polynome<T> Polynome<T>::extend(int m) const
{
    if (m <= n) return *this; 
    std::vector<T> vector(m+1); 
    std::copy(coeff.begin(), coeff.end(), vector.begin());
    return Polynome(vector); 
}

template <typename T>
void Polynome<T>::adjust()
{
    auto is_non_zero = [](const T &d)
    {
        return !is_zero(d); 
    };
    auto it = std::find_if(coeff.rbegin(), coeff.rend(), is_non_zero); 
    int dist = std::distance(coeff.rbegin(), it); 
    int new_degree = n - dist;  
    std::vector<T> coefficients = coeff;
    coefficients.resize(new_degree+1); 
    n = new_degree; 
    coeff = coefficients;  
} 

template<typename T>
T Polynome<T>::operator[](int i) const 
{
    if(i < 0 || i > n) return -1;
    return coeff[i]; 
}

template<typename T>
void affiche_monome(std::ostream& out, const T& a, int n)
{
    if(is_zero(a)) return;
    if(is_zero(n))
    {
        out << a; 
        return;
    }
    if(is_one(n))
    {
        if constexpr (std::is_same<T, std::complex<float>>::value || std::is_same<T, std::complex<double>>::value || std::is_same<T, std::complex<long double>>::value)
        {
            out << a << "z";
        }
        else 
        {
            out << a << "x"; 
        }   
        return; 
    }
    if constexpr (std::is_same<T, std::complex<float>>::value || std::is_same<T, std::complex<double>>::value || std::is_same<T, std::complex<long double>>::value)
    {
        out << a << "z^" << n; 
    }
    else 
    {
        out << a << "x^" << n; 
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Polynome<T>& P)
{
    int compteur = 0; 
    for(const T& a : P.coeff)
    {
        affiche_monome(out, a, compteur); 
        out << " + "; 
        compteur++; 
    }
    return out; 
}

template<typename T>
Polynome<T> operator+(const Polynome<T>& P, const Polynome<T>& Q)
{
    int m = std::max(P.degre(), Q.degre()); 
    Polynome<T> P_extend = P.extend(m); 
    Polynome<T> Q_extend = Q.extend(m); 
    std::vector<T> vector(P_extend.degre()+1); 
    for(int i = 0; i < vector.size(); ++i)
    {
        vector[i] = P_extend[i] + Q_extend[i]; 
    }
    Polynome<T> resultat(vector); 
    resultat.adjust(); 
    return resultat; 
}

template<typename T>
Polynome<T> operator-(const Polynome<T>& P, const Polynome<T>& Q)
{
    int m = std::max(P.degre(), Q.degre()); 
    Polynome<T> P_extend = P.extend(m); 
    Polynome<T> Q_extend = Q.extend(m); 
    std::vector<T> vector(P_extend.degre()+1); 
    for(int i = 0; i < vector.size(); ++i)
    {
        vector[i] = P_extend[i] - Q_extend[i]; 
    }
    Polynome<T> resultat(vector); 
    resultat.adjust(); 
    return resultat; 
}

template<typename T>
Polynome<T> operator*(const Polynome<T>& A, const Polynome<T>& B)
{
    int n = A.degre();
    int m = B.degre(); 
    int l = n + m; 
    std::vector<T> coefficients(l+1); 
    for(int i = 0; i <= n; ++i)
    {
        for(int j = 0; j <= m; ++j)
        {
            coefficients[i+j] += A[i]*B[j]; 
        }
    }
    return Polynome<T>(coefficients); 
}

template<typename T>
result_euclid_div<T> euclid_div(const Polynome<T>& A, const Polynome<T>& B)
{
    Polynome<T> R = A; 
    Polynome<T> Q_final; 
    while(R.degre() >= B.degre()) 
    {
        int n = R.degre() - B.degre(); 
        Polynome<T> Q (R.dominant()/B.dominant(), n); 
        R = R - B * Q;
        Q_final = Q_final + Q;  
        /*if(is_invertible(B.dominant()))
        {
            T q = R.dominant()/(T)(B.dominant()); 
            Polynome<T> Q(q,R.degre()); 
            Q_final = Q_final+Q; 
            R = R-B*Q;
        }
        else
        {
            std::cout << "Coeff non inversible." << std::endl; 
            return std::make_pair(Polynome<T>(),A); 
        }*/
    }
    return result_euclid_div<T>(Q_final,R);
    //return std::make_pair(Q_final, R); 
}   

template<typename T>
T Polynome<T>::operator()(T x) const
{   
    return std::accumulate(coeff.rbegin(), coeff.rend(), T(0), [&x](T acc, const T&d)
    {
        return acc*x+d; 
    });

}