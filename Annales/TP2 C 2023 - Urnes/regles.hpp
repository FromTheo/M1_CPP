#include <array>

template<typename Entier, int n>
void updatePolyaN(int j, std::array<Entier, n>& v)
{
    v[j]++;
}

class Friedman2 
{
    private:
        int q;
        int r;
    public:
        Friedman2(int q0, int r0): q(q0), r(r0) {}
        void operator()(int j, std::array<int,2>& v); 
};
