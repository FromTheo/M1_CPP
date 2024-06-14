#include <random>
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <fstream> 

//Forward declarations : 
template<class RV>
class Melange; 

template<class RV> 
std::ostream& operator<<(std::ostream& out, const Melange<RV>& M); 

template<class RV>
Melange<RV> operator+(const Melange<RV>& M1, const Melange<RV>& M2); 


template<class RV>
class Melange 
{
	private:
		std::vector<RV> modes;
		std::discrete_distribution<int> choose_mode; 
		
	public:

		Melange() : modes() {} 
		Melange(std::vector<typename RV::param_type> p, std::vector<double> alpha); 
		
		int nb_of_modes() const {return modes.size();}
		std::vector<double> weights() const {return choose_mode.probabilities();}
		RV operator[](int i) const {return modes[i];}
		void print_type() const {std::cout << typeid(RV()).name() << "\n";}
		void add_mode(double alpha, RV to_add); 
		template<typename RNG> 
		typename RV::result_type operator()(RNG& G); 
		

		friend std::ostream& operator<< <>(std::ostream& out, const Melange<RV>& M); 
		friend Melange<RV> operator+ <>(const Melange<RV>& M1, const Melange<RV>& M2);

};

template <class RV>
Melange<RV>::Melange(std::vector<typename RV::param_type> p, std::vector<double> alpha) : modes(p.size())
{
	for(int i = 0; i < modes.size(); ++i)
	{
		modes[i] = RV(p[i]); 
	}
	std::discrete_distribution<int> X(alpha.begin(), alpha.end()); 
	choose_mode = X; 
}

template<class RV>
void Melange<RV>::add_mode(double alpha, RV to_add)
{
	if(nb_of_modes() == 0)
	{
		modes.push_back(to_add);
		return; 
	}
	std::vector<double> values = weights();
	std::transform(values.begin(), values.end(), values.begin(), [&alpha](double &d)
	{
		return d*(1-alpha); 
	}); 
	values.push_back(alpha); 
	modes.push_back(to_add); 
	std::discrete_distribution<int> X(values.begin(), values.end()); 
	choose_mode = X; 
}

template<typename RV>
template<typename RNG> 
typename RV::result_type Melange<RV>::operator()(RNG& G)
{
	int i = choose_mode(G); 
	return modes[i](G); 
}

template<class RV> 
std::ostream& operator<<(std::ostream& out, const Melange<RV>& M)
{
	out << M.nb_of_modes() << "\n"; 
	for(const RV& rv : M.modes)
	{
		out << rv << "\n"; 
	}
	return out; 	
}

template<class RV>
Melange<RV> operator+(const Melange<RV>& M1, const Melange<RV>& M2)
{
	//On concatène les vecteurs de poids des deux mélanges : 
	std::vector<double> weights_M1 = M1.weights(); 
	std::vector<double> weights_M2 = M2.weights(); 
	std::vector<double> weights(weights_M1.size() + weights_M2.size()); 
	std::copy(weights_M1.begin(), weights_M1.end(), weights.begin()); 
	std::copy(weights_M2.begin(), weights_M2.end(), weights.begin() + weights_M1.size());

	//Normalisation de weights : 
	std::transform(weights.begin(), weights.end(), weights.begin(), [](double &d)
	{
		return d*0.5; 
	});

	//On concatène les paramètres des deux mélanges : 
	std::vector<typename RV::param_type> params_M1(weights_M1.size()); 
	std::vector<typename RV::param_type> params_M2(weights_M2.size()); 
	for(int i = 0; i < weights_M1.size(); ++i)
	{
		params_M1[i] = M1.modes[i].param(); 
	}
	for(int i = 0; i < weights_M2.size(); ++i)
	{
		params_M2[i] = M2.modes[i].param(); 
	}
	std::vector<typename RV::param_type> params(params_M1.size() + params_M2.size()); 
	std::copy(params_M1.begin(), params_M1.end(), params.begin()); 
	std::copy(params_M2.begin(), params_M2.end(), params.begin() + params_M1.size()); 

	return Melange<RV>(params, weights); 
}