#include <vector>      //std::vector
#include <random>

class RandomWalk
{
    protected : 
    unsigned n; 
    int s; 
    int s_init; 
    std::bernoulli_distribution U; 

    public : 
    RandomWalk(int s0, double p) : n(0), s(s0), s_init(s0), U(p) {}
    int val() const {return s;}
    int time() const {return n;}
    virtual void reset() {s = s_init; n = 0;} 
    virtual void update(std::mt19937_64& G); 
};

void RandomWalk::update(std::mt19937_64& G)
{
    n++;
    if(U(G) == 1) s++;
    else s--;
}

class RandomWalk_with_Min : public RandomWalk
{
    protected : 
    int m; 

    public : 
    RandomWalk_with_Min(int s0, double p)  : RandomWalk(s0,p), m(s_init) {}
    int minimum() const {return m;}
    void reset() {}
    void update(std::mt19937_64& G); 
};

void RandomWalk_with_Min::update(std::mt19937_64& G)
{
    RandomWalk::update(G); 
    if(s < m) m = s; 
}
