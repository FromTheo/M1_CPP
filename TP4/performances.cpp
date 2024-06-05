#include <iostream>
#include <fstream> 
#include <algorithm>
#include <numeric>
#include <ctime>
#include <chrono>
#include <list>
#include <vector>
#include <deque>
#include <random>

using namespace std; 


void measure_complexity_on_vector(long int N)
{
    auto start1 = chrono::system_clock::now(); 
    vector<double> c1(N), c2(N); 
    auto stop1 = chrono::system_clock::now(); 
    chrono::duration<double> diff1 = stop1 - start1; 
    cout << "1) Création " << diff1.count() << endl; 

    auto start2 = chrono::system_clock::now(); 
    mt19937_64 G(time(nullptr)); 
    exponential_distribution<double> E(1);
    for_each(c1.begin(), c1.end(), [&E, &G](double & d)
    {
        d = E(G); 
    }); 
    auto stop2 = chrono::system_clock::now(); 
    chrono::duration<double> diff2 = stop2 - start2;
    cout << "2) Remplissage aléatoire : "  << diff2.count() << endl; 

    auto start3 = chrono::system_clock::now(); 
    auto greater_than_10 = [](double & d)
    {
        return d >= 10; 
    };
    int nombre = count_if(c1.begin(), c1.end(), greater_than_10); 
    auto stop3 = chrono::system_clock::now(); 
    chrono::duration<double> diff3 = stop3 - start3;
    cout << "3) Comptage des éléments supérieurs ou égaux à 10 : " << diff3.count() << endl; 

    auto start4 = chrono::system_clock::now(); 
    transform(c1.begin(), c1.begin()+100, c1.begin(), [](double &d)
    {
        return d*d; 
    }); 
    auto stop4 = chrono::system_clock::now(); 
    chrono::duration<double> diff4 = stop4 - start4;
    cout << "4) Élévation au carré des 100 premiers éléments : " << diff4.count() << endl; 

    auto start5 = chrono::system_clock::now(); 
    copy(c1.begin(), c1.end(), c2.begin()); 
    auto stop5 = chrono::system_clock::now(); 
    chrono::duration<double> diff5 = stop5 - start5;
    cout << "5) Copie du premier dans le second : " << diff5.count() << endl; 

    auto start6 = chrono::system_clock::now(); 
    int moitie = floor(N/2); 
    sort(c1.begin(), c1.begin()+moitie); 
    auto stop6 = chrono::system_clock::now(); 
    chrono::duration<double> diff6 = stop6 - start6;
    cout << "6) Tri de la première moitié du premier : " << diff6.count() << endl;

    auto start7 = chrono::system_clock::now(); 
    swap(c1,c2); 
    auto stop7 = chrono::system_clock::now(); 
    chrono::duration<double> diff7 = stop7 - start7;
    cout << "7) Échange du contenu des deux : " << diff7.count() << endl; 

    /*auto start8 = chrono::system_clock::now(); 
    ofstream file("8_with_std::vector.text"); 
    for_each(c2.begin(), c2.end(), [&file](const double &d)
    {
        file << d << endl; 
    }); 
    file.close(); 
    auto stop8 = chrono::system_clock::now(); 
    chrono::duration<double> diff8 = stop8 - start8;
    cout << "8) Écriture du contenu dans un fichier : " << diff8.count() << endl; */
}  

void measure_complexity_on_deque(long int N)
{
    auto start1 = chrono::system_clock::now(); 
    deque<double> c1(N), c2(N); 
    auto stop1 = chrono::system_clock::now(); 
    chrono::duration<double> diff1 = stop1 - start1; 
    cout << "1) Création " << diff1.count() << endl; 

    auto start2 = chrono::system_clock::now(); 
    mt19937_64 G(time(nullptr)); 
    exponential_distribution<double> E(1);
    for_each(c1.begin(), c1.end(), [&E, &G](double & d)
    {
        d = E(G); 
    }); 
    auto stop2 = chrono::system_clock::now(); 
    chrono::duration<double> diff2 = stop2 - start2;
    cout << "2) Remplissage aléatoire : "  << diff2.count() << endl; 

    auto start3 = chrono::system_clock::now(); 
    auto greater_than_10 = [](double & d)
    {
        return d >= 10; 
    };
    int nombre = count_if(c1.begin(), c1.end(), greater_than_10); 
    auto stop3 = chrono::system_clock::now(); 
    chrono::duration<double> diff3 = stop3 - start3;
    cout << "3) Comptage des éléments supérieurs ou égaux à 10 : " << diff3.count() << endl; 

    auto start4 = chrono::system_clock::now(); 
    transform(c1.begin(), c1.begin()+100, c1.begin(), [](double &d)
    {
        return d*d; 
    }); 
    auto stop4 = chrono::system_clock::now(); 
    chrono::duration<double> diff4 = stop4 - start4;
    cout << "4) Élévation au carré des 100 premiers éléments : " << diff4.count() << endl; 

    auto start5 = chrono::system_clock::now(); 
    copy(c1.begin(), c1.end(), c2.begin()); 
    auto stop5 = chrono::system_clock::now(); 
    chrono::duration<double> diff5 = stop5 - start5;
    cout << "5) Copie du premier dans le second : " << diff5.count() << endl; 

    auto start6 = chrono::system_clock::now(); 
    int moitie = floor(N/2); 
    sort(c1.begin(), c1.begin()+moitie); 
    auto stop6 = chrono::system_clock::now(); 
    chrono::duration<double> diff6 = stop6 - start6;
    cout << "6) Tri de la première moitié du premier : " << diff6.count() << endl;

    auto start7 = chrono::system_clock::now(); 
    swap(c1,c2); 
    auto stop7 = chrono::system_clock::now(); 
    chrono::duration<double> diff7 = stop7 - start7;
    cout << "7) Échange du contenu des deux : " << diff7.count() << endl; 

    /*auto start8 = chrono::system_clock::now(); 
    ofstream file("8_with_std::deque.text"); 
    for_each(c2.begin(), c2.end(), [&file](const double &d)
    {
        file << d << endl; 
    }); 
    file.close(); 
    auto stop8 = chrono::system_clock::now(); 
    chrono::duration<double> diff8 = stop8 - start8;
    cout << "8) Écriture du contenu dans un fichier : " << diff8.count() << endl; */
}  

int main()
{   
    long int N = 10000000; 
    vector<long int> N_values{N, 2*N, 4*N, 8*N}; 

    cout << "\n*** Question 7 ***" << endl; 

    for(const long int& i : N_values)
    {
        cout << "\n\n---- Pour i = " << i << " ----" << endl; 
        measure_complexity_on_vector(i); 
    }
    /* Output :
    ---- Pour i = 10000000 ----
    1) Création 0.237059
    2) Remplissage aléatoire : 0.812491
    3) Comptage des éléments supérieurs ou égaux à 10 : 0.114232
    4) Élévation au carré des 100 premiers éléments : 2e-06
    5) Copie du premier dans le second : 0.012401
    6) Tri de la première moitié du premier : 0.374412
    7) Échange du contenu des deux : 0


    ---- Pour i = 20000000 ----
    1) Création 0.501001
    2) Remplissage aléatoire : 1.54332
    3) Comptage des éléments supérieurs ou égaux à 10 : 0.217026
    4) Élévation au carré des 100 premiers éléments : 1e-06
    5) Copie du premier dans le second : 0.021622
    6) Tri de la première moitié du premier : 0.772463
    7) Échange du contenu des deux : 0


    ---- Pour i = 40000000 ----
    1) Création 0.921667
    2) Remplissage aléatoire : 3.02444
    3) Comptage des éléments supérieurs ou égaux à 10 : 0.405401
    4) Élévation au carré des 100 premiers éléments : 1e-06
    5) Copie du premier dans le second : 0.052279
    6) Tri de la première moitié du premier : 1.44596
    7) Échange du contenu des deux : 1e-06


    ---- Pour i = 80000000 ----
    1) Création 1.83354
    2) Remplissage aléatoire : 6.17028
    3) Comptage des éléments supérieurs ou égaux à 10 : 0.849654
    4) Élévation au carré des 100 premiers éléments : 1e-06
    5) Copie du premier dans le second : 0.113114
    6) Tri de la première moitié du premier : 3.22508
    7) Échange du contenu des deux : 1e-06
    */

    cout << "\n*** Question 8 ***" << endl; 

    for(const long int& i : N_values)
    {
        cout << "\n\n---- Pour i = " << i << " ----" << endl; 
        measure_complexity_on_deque(i); 
    }
    /* Output : 
    1) Création 0.182473
    2) Remplissage aléatoire : 0.665428
    3) Comptage des éléments supérieurs ou égaux à 10 : 0.080716
    4) Élévation au carré des 100 premiers éléments : 1e-06
    5) Copie du premier dans le second : 0.012137
    6) Tri de la première moitié du premier : 1.70686
    7) Échange du contenu des deux : 1e-06


    ---- Pour i = 20000000 ----
    1) Création 0.308702
    2) Remplissage aléatoire : 1.36857
    3) Comptage des éléments supérieurs ou égaux à 10 : 0.162086
    4) Élévation au carré des 100 premiers éléments : 2e-06
    5) Copie du premier dans le second : 0.025801
    6) Tri de la première moitié du premier : 3.53703
    7) Échange du contenu des deux : 1e-06


    ---- Pour i = 40000000 ----
    1) Création 0.616032
    2) Remplissage aléatoire : 2.63384
    3) Comptage des éléments supérieurs ou égaux à 10 : 0.319574
    4) Élévation au carré des 100 premiers éléments : 2e-06
    5) Copie du premier dans le second : 0.05715
    6) Tri de la première moitié du premier : 6.9432
    7) Échange du contenu des deux : 1e-06


    ---- Pour i = 80000000 ----
    1) Création 1.17606
    2) Remplissage aléatoire : 4.97778
    3) Comptage des éléments supérieurs ou égaux à 10 : 0.59501
    4) Élévation au carré des 100 premiers éléments : 2e-06
    5) Copie du premier dans le second : 0.116158
    6) Tri de la première moitié du premier : 14.3205
    7) Échange du contenu des deux : 0
    */

    
    return 0; 
}