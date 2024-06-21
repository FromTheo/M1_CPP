#include <iostream>
#include <chrono>
#include <random>
#include <ctime> 
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/Eigenvalues>

#include "histogramme.hpp"

using namespace std;

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixDouble;
typedef Eigen::SparseMatrix<double> SparseMatrixDouble;
using Mat = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;

MatrixDouble puissance_lente(const MatrixDouble& M, int n)
{
    if(n == 0) return MatrixDouble::Identity(M.rows(), M.cols()); 
    else if(n == 1) return M; // Pour éviter la récursivité (allocation de mémoire supplémentaire qui s'avère inutile). 
    else 
    {
        MatrixDouble N(M.rows(), M.cols()); 
        N = puissance_lente(M,n-1); 
        return N * M;
    }
}

MatrixDouble puissance_rapide(const MatrixDouble& M, int n)
{
    if(n == 0) return MatrixDouble::Identity(M.rows(), M.cols());
    else if (n == 1) return M; 
    else if (n % 2 == 0) 
    {
        MatrixDouble N(M.rows(), M.cols()); 
        N = puissance_rapide(M, n/2); 
        return N * N; 
    }
    else 
    {
       MatrixDouble N(M.rows(), M.cols()); 
       N = puissance_rapide(M, (n-1)/2);
       return M * N * N;  
    }
}

SparseMatrixDouble puissance_sparse(const SparseMatrixDouble& M, int n)
{
    if(n == 0)
    {
        SparseMatrixDouble identity(M.cols(), M.rows());
        identity.setIdentity();
        return identity;
    }
    else if(n % 2 == 0)
    {
        SparseMatrixDouble N = puissance_sparse(M,n/2);
        return N * N;
    }
    else
    {
        SparseMatrixDouble N = puissance_sparse(M,(n-1)/2);
        return M * N * N; 
    }
}

auto generate_random_spectrum(mt19937_64& G, int N)
{
    MatrixDouble A(N,N);
    normal_distribution<double> loi_diag(0.0,1.0);
    normal_distribution<double> loi_hors_diag(0.0,2.0);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(j == i)
            {
                A(j,j) = loi_diag(G);
            }
            else
            {
                A(j,i) = loi_hors_diag(G);
                A(i,j) = A(j,i); // Car la matrice est symétrique. 
            }
        }
    }
    Eigen::EigenSolver<MatrixDouble> solver(A);
    return solver.eigenvalues(); 
}

int main()
{
    // Question 2.3 : 
    MatrixDouble A(3,3); 
    A << 0.4, 0.6, 0.0, 0.75, 0.25, 0.0, 0.0, 0.0, 1.0; 
    cout << puissance_lente(A,100) << endl; 
    /* Output : 
    0.555556 0.444444        0
    0.555556 0.444444        0
    0        0        1 */

    // Question 2.7 & Question 2.8 : 
    ifstream file("matrice.txt"); 
    MatrixDouble B(30,30); 
    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            file >> B(i,j);
        }
    }

    SparseMatrixDouble B_sparse(30,30);
    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            double v;
            file  >> v;
            if(abs(v) >= 1e-12)
            {
                B_sparse.coeffRef(i,j) = v;
            }
        }
    }

    file.close(); 

    auto start1 = std::chrono::system_clock::now(); 
    puissance_lente(B,1000); 
    auto stop1 = std::chrono::system_clock::now(); 
    std::chrono::duration<double> diff1 = stop1 - start1; 
    
    auto start2 = std::chrono::system_clock::now(); 
    puissance_rapide(B,1000); 
    auto stop2 = std::chrono::system_clock::now(); 
    std::chrono::duration<double> diff2 = stop2 - start2; 
    cout << "Avec puissance_lente : " << diff1.count() << endl;   //Output : Avec puissance_lente : 0.304467 (0.009338 avec - DNDEBUG et -O2)
    cout << "Avec puissance_rapide : " << diff2.count() << endl;  //Output : Avec puissance_rapide : 0.003995 (0.000125 avec -DNDEBUG et -O2)

    auto start3 = std::chrono::system_clock::now(); 
    puissance_sparse(B_sparse,1000); 
    auto stop3 = std::chrono::system_clock::now(); 
    std::chrono::duration<double> diff3 = stop3 - start3; 
    cout << "Avec puissance_sparse : " << diff3.count() << endl; // Output : Avec puissance_sparse : 0.000334 (3.9e-05 avec -DNDEBUG et -O2)

    // Question 2.10 : 
    int simul = 20; 
    const int N = 150;
    const int nb_boxes = 20;
    double a=-3.;
    double b=3.;
    mt19937_64 G(time(nullptr));
    
    vector<double> hist(nb_boxes); 
    for(int sample = 0; sample < simul; sample++)
    {
        Mat RandomMat(N,N);
        std::normal_distribution<double> Loi_diag(0,1); 
        std::normal_distribution<double> Loi_hors_diag(0,2); 
        for(int j = 0; j <  N; ++j)
        {
            RandomMat(j,j) = Loi_diag(G);
            for(int k = j+1; k < N; ++k)
            {
                RandomMat(j,k) = Loi_hors_diag(G);
                RandomMat(k,j) = RandomMat(j,k);
            }
        }
        Eigen::EigenSolver<Mat> Solver(RandomMat);
        for(int i=0; i<N; i++)
        {
            double lambda_normalized = Solver.eigenvalues()[i].real()/(2.*sqrt(N));
            int indice = std::floor( (lambda_normalized-a)/(b-a)*nb_boxes); 
            if( (indice >= 0) && (indice < nb_boxes) )
            {
                hist[indice]+= 1.;
            }
        }
    }
    for (auto & x: hist)
	{
		x /= double(simul*N);
	}
	ofstream fichier_out_1("eigenvalues_q_10.txt");
	for(size_t i = 0; i< hist.size(); i++)
    {
		fichier_out_1 << a+(2*i+1)*(b-a)/(2.*nb_boxes) << "\t" << hist[i] << endl;
	}
	fichier_out_1.close();

    // Question 2.14 : 
    Histogramme H(a,b,nb_boxes);
    for(int i = 0; i < simul; i++)
    {
        auto spec = generate_random_spectrum(G, N);
        for(auto lambda : spec)
        {
            H += lambda.real()/(2.0*sqrt(N));
        }
    }
    ofstream fichier_out_2("eigenvalues_q_14.txt"); 
    H.print(fichier_out_2); 
    fichier_out_2.close(); 
    
    return 0; 
}
