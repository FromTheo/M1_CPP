#include <iostream> 
#include <cmath>        //std::sqrt, std::log 
#include <utility>      //std::make_pair 

#include "monte_carlo.hpp"
#include "pi.hpp"
#include "chi_deux.hpp"
#include "markov_2_states.hpp"
#include "ising1D.hpp"

using namespace std;

int main()
{
    cout << "*** Question 4 ***" << endl;
    mt19937_64 G(time(nullptr)); 
    SquareInDisk A; 
    double pi_approx; 
    auto fois4 = [](double x)
    {
        return 4*x; 
    };
    std::vector<int> n_values{1000,10000,100000};
    for(const int& n : n_values)
    {
        MonteCarlo(pi_approx, A, fois4, G, n); 
        cout << "Approximation de pi : " << pi_approx << " (pour n = " << n << ")" << endl; 
    } 
    /* Output : 
    Approximation de pi: 3.2 (pour n = 1000)
    Approximation de pi: 3.12952 (pour n = 10000)
    Approximation de pi: 3.14483 (pour n = 100000) */

    cout << "\n*** Question 8 ***" << endl; 
    DoubleMeanVar MV; 
    for(const int& n : n_values)
    {
        MonteCarlo(MV, A, fois4, G, n); 
        double lbound = MV.moyenne() - 1.96 * sqrt(MV.variance() / (double)n);
        double ubound = MV.moyenne() + 1.96 * sqrt(MV.variance() / (double)n);
        cout << "Pour n = " << n << ", [ " << lbound << " ; " << ubound << " ]" << endl; 
    }
    /* Output : 
    Pour n = 1000, [ 3.07155 ; 3.27245 ]
    Pour n = 10000, [ 3.11298 ; 3.17726 ]
    Pour n = 100000, [ 3.13852 ; 3.15882 ] */

    cout << "\n*** Question 9 ***" << endl; 
    const int N = 10000; 
    auto f1 = [](double x)
    {
        return log(1+x*x); 
    }; 
    uniform_real_distribution<double> U(0.0,1.0); 
    double res1;
    MonteCarlo(res1, U, f1, G, N); 
    cout << "1ère intégrale : " << res1 << endl; 
    //Output : 1ère intégrale : 0.263462 

    exponential_distribution<double> X(1.0); 
    uniform_real_distribution<double> Y(0.0,1.0); 
    auto f2 = [](pair<double,double> p)
    {
        return log(1 + p.first * p.second); 
    };
    auto CoupleXY = [&X, &Y](mt19937_64& G)
    {
        return std::make_pair(X(G), Y(G)); 
    }; 
    double res2; 
    MonteCarlo(res2, CoupleXY, f2, G, N); 
    cout << "2eme intégrale : " << res2 << endl; 
    //Output : 2eme intégrale : 0.341814 
    
    cout << "\n*** Question 13 ***" << endl; 
    auto id = [](double x)
    {
        return x;
    }; 
    const int nb_simulations = 100000;
    normal_distribution<double> gauss(0.0,1.0); 
    Histogramme H(-3., 3., 50); 
    MonteCarlo(H, gauss, id, G, nb_simulations); 
    cout << H << endl; 
    /* Output : 
    -3	0.00073
    -2.88	0.00092
    -2.76	0.00121
    -2.64	0.00167
    -2.52	0.00245

    ... 
    ...

    2.52	0.00197
    2.64	0.0011
    2.76	0.0009
    2.88	0.00086
    3	    0  */

    cout << "\n*** Question 15 ***" << endl;
    Chi2_distribution<double,3> X_3;
    Histogramme H2(0., 5., 50); 
    MonteCarlo(H2, X_3, id, G, nb_simulations); 
    cout << H2 << endl; 
    /* Output : 
    0	0.00833
    0.1	    0.01398
    0.2	    0.01729
    0.3	    0.01952
    0.4	    0.02091

    ...
    ...

    4.6 	0.00887
    4.7	    0.00815
    4.8	    0.00767
    4.9	    0.00713
    5	    0   */

    Chi2_distribution<double,6> X_6;
    Histogramme H3(0., 5., 50); 
    MonteCarlo(H3, X_6, id, G, nb_simulations); 
    cout << H3 << endl;
    /* Output : 
    0	    2e-05
    0.1	    0.00018
    0.2	    0.00038
    0.3	    0.00059
    0.4	    0.00109

    ...
    ...

    4.6	    0.01387
    4.7	    0.0129
    4.8	    0.01314
    4.9	    0.01285
    5	    0   */

    cout << "\n*** Question 18 ***" << endl;
    Markov2States Markov; 
    Stat2states S(0,0);
    MonteCarlo(S,Markov,id,G,100000);
    cout << S << endl;  
    //Output : 0.66638 0.66724


    unsigned N0 = 1000;
	auto x500 = [](const std::vector<int> & v){return v[499];};
	std::cout << "Modele d'Ising: quelques valeurs selon beta et h:\n";
	for (double beta = 0.; beta < 2.; beta+=0.4)
	{
		for (double h = 0.; h < 1.; h += 0.2)
		{
			Ising1D Ising(N0,beta,h);
			double m=0.;
			MonteCarlo(m,Ising,x500,G,nb_simulations);
			std::cout << "\tbeta= " << beta << "\th= " << h << "\tmoyenne de x_500= "<< m << "\n";
		}
	}
    /* Output : 
        beta = 0	h= 0	moyenne de x_500 = -0.01944
	    beta = 0	h= 0.2	moyenne de x_500 = 0.15568
	    beta = 0	h= 0.4	moyenne de x_500 = 0.21996
	    beta = 0	h= 0.6	moyenne de x_500 = 0.38016
	    beta = 0	h= 0.8	moyenne de x_500 = 0.66886
	    beta = 0.4	h= 0	moyenne de x_500 = 0.16162
	    beta = 0.4	h= 0.2	moyenne de x_500 = 0.59236
	    beta = 0.4	h= 0.4	moyenne de x_500 = 0.67572
	    beta = 0.4	h= 0.6	moyenne de x_500 = 0.75938
	    beta = 0.4	h= 0.8	moyenne de x_500 = 0.94086
	    beta = 0.8	h= 0	moyenne de x_500 = 0.3008
	    beta = 0.8	h= 0.2	moyenne de x_500 = 0.58728
	    beta = 0.8	h= 0.4	moyenne de x_500 = 0.9638
	    beta = 0.8	h= 0.6	moyenne de x_500 = 1
	    beta = 0.8	h= 0.8	moyenne de x_500 = 0.99882
	    beta = 1.2	h= 0	moyenne de x_500 = 0.59954
	    beta = 1.2	h= 0.2	moyenne de x_500 = 0.9716
	    beta = 1.2	h= 0.4	moyenne de x_500 = 0.98654
	    beta = 1.2	h= 0.6	moyenne de x_500 = 1
	    beta = 1.2	h= 0.8	moyenne de x_500 = 1
	    beta = 1.6	h= 0	moyenne de x_500 = 1
	    beta = 1.6	h= 0.2	moyenne de x_500 = 0.9486
	    beta = 1.6	h= 0.4	moyenne de x_500 = 1
	    beta = 1.6	h= 0.6	moyenne de x_500 = 0.99862
	    beta = 1.6	h= 0.8	moyenne de x_500 = 1 */

    return 0; 
}