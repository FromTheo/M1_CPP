#include "loi_melange.hpp" 

using namespace std; 

int main() 
{
	Melange<std::bernoulli_distribution> M_bernoulli;	
	M_bernoulli.print_type();

	//Question 7 : 
	std::bernoulli_distribution B1(0.5), B2(0.2); 
	M_bernoulli.add_mode(1,B1); 
	M_bernoulli.add_mode(0.3,B2);

	//Question 9 : 
	mt19937_64 G(time(nullptr));  
	cout << M_bernoulli(G) << endl; 

	//Question 10 : 
	double moyenne = 0.7*0.5 + 0.2*0.3; 
	double moyenne_empirique = 0.0; 
	const int N = 100000; 
	for(int i = 0; i < N; ++i)
	{
		moyenne_empirique += M_bernoulli(G); 
	}
	moyenne_empirique /= (double)N; 
	cout << "Moyenne = " << moyenne << endl; 						//Output : Moyenne = 0.41
	cout << "Moyenne empirique = " << moyenne_empirique << endl; 	//Output : Moyenne empirique = 0.4116

	//Question 13 : 
	ifstream fichier1 ("melange_gauss_1.txt"); 
	int taille; 
	fichier1 >> taille; 
	std::vector<typename std::normal_distribution<double>::param_type > p(taille); 
	std::vector<double> alpha(taille);
	for(int i=0; i<taille;i++)
	{
		double esp, var, poids; 
		fichier1 >> poids >> esp >> var; 
		alpha[i] = poids; 
		std::normal_distribution<double> N(esp, var);
		p[i] = N.param(); 
	}
	Melange<normal_distribution<double>> M_gaussian_1(p, alpha); 
	cout << M_gaussian_1[0] << endl; 
	fichier1.close(); 

	//Question 15 : 
	ifstream fichier2 ("melange_gauss_2.txt"); 
	int taille2; 
	fichier2 >> taille2; 
	std::vector<typename std::normal_distribution<double>::param_type > p2(taille2); 
	std::vector<double> alpha2(taille2);
	for(int i=0; i<taille2;i++)
	{
		double esp, var, poids; 
		fichier2 >> poids >> esp >> var; 
		alpha2[i] = poids; 
		std::normal_distribution<double> N(esp, var);
		p2[i] = N.param(); 
	}
	Melange<normal_distribution<double>> M_gaussian_2(p2, alpha2); 
	cout << M_gaussian_2[0] << endl; 
	fichier2.close(); 

	//Question 16 : 
	Melange<normal_distribution<double>> Somme = M_gaussian_1 + M_gaussian_2; 
	cout << Somme(G) << endl; 
	
	return 0;
}

