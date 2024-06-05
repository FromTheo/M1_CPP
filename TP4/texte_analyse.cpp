#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <array>
#include <algorithm>
#include <numeric> 
#include <set>

using namespace std; 

bool compare_E(const std::pair<string, unsigned>& p , const std::pair<string, unsigned>& q)
{
    int compteur_p = 0; 
    int compteur_q = 0; 
    for(const char x : p.first)
    {
        if(x == 'e')compteur_p++;
    }
    for(const char x: q.first)
    {
        if(x == 'e') compteur_q++; 
    }
    if(compteur_p < compteur_q)
    {
        return p<q; 
    }
    return q<p; 
}

bool bcp_conditions(const std::pair<string, unsigned>& p)
{
    bool pasE=true;
    for(const char& x: p.first)
    {
        if(x =='e')
        {
            pasE=false; 
        }
    }
    if(p.first.size()>=12 and p.second >=13 and pasE==true and p.first.back()!='s')
    {
        return true;
    }
    return false; 
}

set<string> filter(const map<string,unsigned>& M, char first_letter, unsigned k)
{
    set<string> res; 
    for(const pair<string,unsigned>& p : M)
    {
        if(p.first.front() == first_letter && p.second >= k) res.insert(p.first);
    }
    return res; 
}

int main()
{
    cout << "\n\n*** Question 11 ***" << endl; 
    map<string, unsigned> S; 
    ifstream file ("declaration.txt"); 
    string mot;
    while(file >> mot)
    {
        S[mot]++; 
    }
    //Alternative possible : voir la méthode eof(). 


    cout << "\n\n*** Question 12 ***" << endl; 
    vector<pair<string, unsigned>> copy(S.begin(), S.end()); 
    sort(copy.begin(), copy.end(), [](const std::pair<string, unsigned> &p, const std::pair<string, unsigned> &q)
    {
        return p.first < q.first; 
    }); //Tri dans l'ordre lexicographique. 
    ofstream file_out("stats.txt");
    for_each(copy.begin(), copy.end(), [&file_out](const std::pair<string, int> &p)
    {
        file_out << p.first << "\t" << p.second << endl;
    });
    file_out.close(); 


    cout << "\n\n*** Question 13 ***" << endl; 
    vector<pair<string,unsigned>> copy2(S.begin(), S.end()); 
    sort(copy2.begin(), copy2.end(), [](const std::pair<string, unsigned> &p, const std::pair<string, unsigned> &q)
    {
        return p.second > q.second; 
    }); //Tri par ordre décroissant de fréquence. 
    ofstream file_out2("stats2.txt"); 
    for_each(copy2.begin(), copy2.end(), [&file_out2](const std::pair<string, int> &p)
    {
        file_out2 << p.first << "\t" << p.second << endl;
    });
    file_out2.close();


    cout << "\n\n*** Question 14 ***" << endl; 

    cout << "1) Il y a " << S.size() << " mots différents." << endl; //Output : 1502. 
    
    int sept_lettres = count_if(S.begin(), S.end(), [](const pair<string, unsigned>&p )
    {
        return p.first.size() >= 7; 
    });
    cout << "2) Il y a " << sept_lettres << " mots différents de plus de 7 lettres." << endl;  //Output : 1020. 
    
    map<string,unsigned> S_bis = S; 
    array<pair<string,unsigned>,10> freq; 
    for(int i = 0; i < 10; ++i)
    {
        auto it = max_element(S_bis.begin(), S_bis.end(), [](const pair<string, unsigned>& p, const pair<string, unsigned>& q)
        {
            return p.second < q.second; 
        }); 
        pair<string, unsigned> p = *it; 
        S_bis.erase(it); 
        freq[i] = p; 
    }
    cout << "3) Les 10 mots les plus fréquents sont : " << endl; 
    for(const pair<string, unsigned> &p : freq)
    {
        cout << p.first << " " << p.second << endl; 
    }
    /* Output : 
    de 701
    la 463
    le 364
    l 355
    les 349
    des 279
    et 242
    a 239
    par 207
    du 205 */

    unsigned nombre_lettres = accumulate(S.begin(), S.end(), 0, [](unsigned acc, const pair<string, unsigned>& p)
    {
        return acc + p.second * p.first.size(); 
    });
    cout << "4) Le nombre total de lettres dans la déclaration est : " << nombre_lettres << endl; //Output : 59238.

    auto voyelle=[](const pair<string,unsigned> &p)
    {
        unsigned int compteur= 0; 
        for(const char& c : p.first)
        {
            if(c=='a' or c=='e' or c=='i' or c=='o' or c=='u' or c=='y')
            {
                compteur++;
            }
        }
        return compteur==2;
    };
    unsigned int nbmotvoyelles=accumulate(S.begin(), S.end(), 0.0, [voyelle](unsigned int acc, const pair<string, unsigned>& p)
    {
        if(voyelle(p))
        {
            return acc+p.second;
        }
        else
        {
            return acc;
        }
    });
    cout << "5) Il y a " << nbmotvoyelles << " mots avec exactement deux voyelles. " << endl; //Output : 2357. 

    array<pair<string,unsigned>,10> freq2; 
    vector<pair<string, unsigned>> vect(S.begin(), S.end());  
    for(int i = 0; i < 10; ++i)
    {
        auto it = max_element(vect.begin(), vect.end(), compare_E); 
        pair<string, unsigned> p = *it; 
        vect.erase(it); 
        freq2[i] = p; 
    }
    cout << "6) Les 10 mots contenant le plus de fois la lettre 'e' sont : " << endl; 
    for(const pair<string,unsigned>& p : freq2)
    {
        cout << p.first << " " << p.second << endl; 
    }
    /* Output :
    eventuellement 1
    exceptionnellement 1
    intergouvernementale 1
    acceleree 3
    anterieurement 1
    decentralisee 1
    deferees 1
    determinees 5
    developpement 1
    echelonnement 1 */

    double long_moy = accumulate(S.begin(), S.end(), 0., [](double acc, const pair<string, unsigned>& p)
    {
        return acc + p.first.size(); 
    })/(double)S.size(); 
    cout << "7) La longueur moyenne d'un mot est : " << long_moy << endl; //Output : 7.9281.
    double freq_moy = std::accumulate(S.begin(), S.end(), 0., [](double acc, const std::pair<string, unsigned>&p)
    {
        return acc+p.second; 
    })/(double)S.size(); 
    cout << "La fréquence moyenne d'un mot est : " << freq_moy << endl; //Output : 7.76764.
    double cov = accumulate(S.begin(), S.end(), 0., [&freq_moy, &long_moy](double acc, const pair<string, unsigned>&p)
    {
        return acc+(p.first.size() - long_moy)*(p.second - freq_moy); 
    })/(double)(S.size()-1);
    cout << "La covariance empirique est de : " << cov << endl; //Output :  -22.158. Les résultats ne sont pas corrélés. 

    cout << "\n*** Question 15 ***" << endl; 
    for_each(S.begin(), S.end(), [](const pair<string,unsigned>& p)
    {
        if(bcp_conditions(p)) cout << p.first << " " << p.second << endl; 
    }); 
    /* Output : 
    constitution 13
    organisation 17 */

    cout << "\n*** Question 16 ***" << endl; 
    ofstream file_out3("h2.txt"); 
    set<string> set = filter(S, 'h', 2); 
    for(const string& s: set)
    {
        file_out3 << s << endl; 
    }
    file_out3.close(); 

    return 0; 
}
