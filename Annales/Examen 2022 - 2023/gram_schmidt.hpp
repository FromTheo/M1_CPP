#include <vector> 
#include <cmath> 

class  DefaultScal
{
    public : 
    template<class Vect> 
    auto operator()(const Vect& v1, const Vect& v2) const {return v1.scal(v2);}
};

template <class Vect, class ScalProd = DefaultScal>
void gram_schmidt_in_place(std::vector<Vect>& v, const ScalProd& s = DefaultScal())
{
    int m = v.size(); 
    std::vector<Vect> v_hat(m); 
    for(int k = 0; k < m; ++k)
    {
        if(k == 0)
        {
            v_hat[0] = v[0];    
            continue; 
        }
        v_hat[k] = v_hat[k] + v[k]; 
        for(int l = 0; l < k-1; ++l)
        {
            double lambda = -s(v_hat[l], v[k])/s(v_hat[l], v_hat[l]); 
            v_hat[k] = v_hat[k] + v_hat[l]*lambda; 
        }
    }
    v = v_hat; 
}

template <class Iterator, class ScalProd = DefaultScal>
void normalize(Iterator b, Iterator e, const ScalProd& s = DefaultScal())
{
    std::transform(b,e,b, [&s](auto d)
    {
        return d/std::sqrt(s(d,d)); 
    }); 
}
