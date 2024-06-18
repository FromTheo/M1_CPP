#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath> 
#include <algorithm>
#include <numeric> 
#include <map> 

using namespace std; 

struct Fiche
{
    string prenom; 
    string ville; 
    int age; 
    double temps; 
}; 

bool compare(const Fiche& f, const Fiche& g)
{   
    if(f.prenom != g.prenom) return f.prenom < g.prenom;
    if(f.ville != g.ville) return f.prenom < g.prenom;
    if(f.age != g.age) return f.age > g.age; 
    return f.temps > g.temps; 
}

int main()
{
    // ***** Question 1 *****

    //Q.1
    ifstream fichier ("smalldata.txt"); 

    //Q.2 
    const int N = 2500; 
    vector<Fiche> vdata(N); 
    for(int i = 0; i < N; ++i)
    {
        fichier >> vdata[i].prenom >> vdata[i].ville >> vdata[i].age >> vdata[i].temps; 
    }
    fichier.close(); 

    //Q.3.a
    auto is_from_Lyon = [](Fiche f)
    {
        return f.ville == "Lyon"; 
    }; 
    int nb_habitants_lyon = count_if(vdata.begin(), vdata.end(), is_from_Lyon);
    cout << "a) Il y a " << nb_habitants_lyon << " lyonnais. Soit " << nb_habitants_lyon*100/(double)N << "% des personnes du fichier." << endl; 
    //Output : a) Il y a 424 lyonnais. Soit 16.96% des personnes du fichier.

    //Q.3.b 
    auto is_from_Lyon_young = [](Fiche f)
    {
        return f.ville == "Lyon" && f.age < 30; 
    };
    int nb_habitants_lyon_jeunes = count_if(vdata.begin(), vdata.end(), is_from_Lyon_young); 
    cout << "b) Il y a " << nb_habitants_lyon_jeunes << " lyonnais de moins de 30 ans." << endl; 
    //Output : b) Il y a 148 lyonnais de moins de 30 ans.

    //Q.3.c 
    auto toulousains_A = [](Fiche f)
    {
        return f.ville == "Toulouse" && f.prenom.front() == 'A'; 
    }; 
    if(any_of(vdata.begin(), vdata.end(), toulousains_A)) cout << "c) Il y a un toulousain dont le prénom commence par A." << endl; 
    else cout << "c) Il n'y a pas de toulousains dont le prénom commence par A." << endl; 
    //Output : c) Il y a un toulousain dont le prénom commence par A.

    //Q.3.d 
    auto it_min = min_element(vdata.begin(), vdata.end(), [](const Fiche& f, const Fiche& g)
    {
        return f.age < g.age; 
    }); 
    auto it_max = max_element(vdata.begin(), vdata.end(), [](const Fiche &f, const Fiche &g)
    {
        return f.age < g.age; 
    }); 
    cout << "d) C'est " << (*it_min).prenom << " le plus jeune avec " << (*it_min).age << " ans. Et c'est " << (*it_max).prenom << " le plus âgé avec " << (*it_max).age << " ans. " << endl; 
    //Output : d) C'est Bruno le plus jeune avec 20 ans. Et c'est Jabba le plus âgé avec 113 ans. 

    //Q.3.e 
    double moyenne = accumulate(vdata.begin(), vdata.end(), 0.0, [](double acc, const Fiche& f)
    {
        return acc + f.age; 
    })/(double)N;  

    double variance = accumulate(vdata.begin(), vdata.end(), 0.0, [&moyenne](double acc, const Fiche& f)
    {
        return acc + (f.age-moyenne)*(f.age-moyenne); 
    })/(double)N; 
    double ecart_type = sqrt(variance); 
    cout << "e) L'âge moyen des personnes du fichier est  : " << moyenne << ", tandis que l'écart type est : " << ecart_type << endl;
    //Output : e) L'âge moyen des personnes du fichier est  : 34.4452, tandis que l'écart type est : 8.78702

    //Q.3.f 
    auto is_from_Paris = [](Fiche f)
    {
        return f.ville == "Paris"; 
    }; 
    auto is_from_Marseille = [](Fiche f)
    {
        return f.ville == "Marseille"; 
    };
    double moyenne_temps_paris = accumulate(vdata.begin(), vdata.end(), 0.0, [&is_from_Paris](double acc, const Fiche& f)
    {
        if(is_from_Paris(f)) return acc + f.temps;
        else return acc; 
    })/(double)count_if(vdata.begin(), vdata.end(), is_from_Paris); 
    double moyenne_temps_marseille = accumulate(vdata.begin(), vdata.end(), 0.0, [&is_from_Marseille](double acc, const Fiche& f)
    {
        if(is_from_Marseille(f)) return acc + f.temps;
        else return acc; 
    })/(double)count_if(vdata.begin(), vdata.end(), is_from_Marseille);
    cout << "f) Les parisiens ont une moyenne de " << moyenne_temps_paris << "s, tandis que les marseillais " << moyenne_temps_marseille << "s. "; 
    if(moyenne_temps_paris < moyenne_temps_marseille) cout << "Les parisiens sont donc plus rapides." << endl; 
    else cout << "Les marseillais sont donc plus rapides." << endl; 
    //Output : f) Les parisiens ont une moyenne de 14.3985s, tandis que les marseillais 14.4155s. Les parisiens sont donc plus rapides.

    //Q.3.g 
    ofstream fichier_toulousains("toulousains2.txt"); 
    auto is_from_Toulouse = [](Fiche f)
    {
        return f.ville == "Toulouse"; 
    }; 
    for_each(vdata.begin(), vdata.end(), [&fichier_toulousains, &is_from_Toulouse](const Fiche &f)
    {
        if(is_from_Toulouse(f)) fichier_toulousains << f.prenom << "\t" << f.ville << "\t" << 2018-f.age << "\t" << f.temps << "\n";
    });  
    fichier_toulousains.close(); 

    //Q.3.h
    double moyenne_age_toulouse = accumulate(vdata.begin(), vdata.end(), 0.0, [&is_from_Toulouse](double acc, const Fiche& f)
    {
        if(is_from_Toulouse(f)) return acc + f.age; 
        else return acc; 
    })/(double)count_if(vdata.begin(), vdata.end(), is_from_Toulouse); 
    double moyenne_temps_toulouse = accumulate(vdata.begin(), vdata.end(), 0.0, [&is_from_Toulouse](double acc, const Fiche& f)
    {
        if(is_from_Toulouse(f)) return acc + f.temps; 
        else return acc; 
    })/(double)count_if(vdata.begin(), vdata.end(), is_from_Toulouse); 
    double covariance = accumulate(vdata.begin(), vdata.end(), 0.0, [&is_from_Toulouse, &moyenne_temps_toulouse, &moyenne_age_toulouse](double acc, const Fiche &f)
    {
        if(is_from_Toulouse(f)) return acc + (f.age - moyenne_age_toulouse)*(f.temps - moyenne_temps_toulouse);
        else return acc; 
    })/(double)(count_if(vdata.begin(), vdata.end(), is_from_Toulouse)-1); 
    cout << "h) L'âge moyen est : " << moyenne_age_toulouse << ", le temps moyen au 100m est : " << moyenne_temps_toulouse << endl; 
    cout << "La covariance entre age des temps des toulousains est de : " << covariance << endl;  
    /* Output : h) L'âge moyen est : 33.8036, le temps moyen au 100m est : 14.3344
    La covariance entre age des temps des toulousains est de : 10.5591  */

    //Q.3.i
    map<string, int> M; 
    for_each(vdata.begin(), vdata.end(), [&M](const Fiche &f)
    {   
        M[f.ville]++; 
    }); 
    cout << "i) Il y a un total de " << M.size() << " villes représentées. On retrouve : " << endl;
    for_each(M.begin(), M.end(), [](const pair<string, int>& p)
    {
        cout << "- " << p.first << ", représentée " << p.second << " fois." << endl; 
    }); 
    /* Output : i) Il y a un total de 11 villes représentées. On retrouve : 
    - Bordeaux, représentée 289 fois.
    - Brest, représentée 138 fois.
    - Clermont-Ferrand, représentée 135 fois.
    - Kingston, représentée 1 fois.
    - Lille, représentée 288 fois.
    - Lyon, représentée 424 fois.
    - Marseille, représentée 405 fois.
    - Montcuq, représentée 1 fois.
    - Paris, représentée 543 fois.
    - Tatouine, représentée 1 fois.
    - Toulouse, représentée 275 fois. */

    // ***** Question 2 *****
    vector<Fiche> sorted_vdata = vdata; 
    sort(sorted_vdata.begin(), sorted_vdata.end(), [](const Fiche& f, const Fiche& g) 
    {
        return f.temps > g.temps; //Tri dans l'ordre décroissant. 
    }); 
    for(int i = 0; i< 10; ++i)
    {
        cout << sorted_vdata[i].temps << endl; 
    }
    ofstream fichier3("data_tri.txt"); 
    for(vector<Fiche>::iterator it = sorted_vdata.end()-100; it != sorted_vdata.end(); ++it)
    {
        fichier3 << (*it).prenom << "\t" << (*it).ville << "\t" << (*it).age << "\t" << (*it).temps << endl; 
    }
    fichier3.close(); 

    // ***** Question 3 ***** 
    //Q.1 
    vector<double> temps(N); 
    transform(vdata.begin(), vdata.end(), temps.begin(), [](const Fiche& f)->double
    { 
        return f.temps; 
    }); 
    vector<double> ecarts (temps.size());
    adjacent_difference(temps.begin(), temps.end(), ecarts.begin());
    cout << "Le plus petit écart entre les temps de deux personnes est : " << *min_element(ecarts.begin()+1,ecarts.end()) << endl; 
    //Output : Le plus petit écart entre les temps de deux personnes est : 0

    //Q.2
    vector<Fiche> jeunes; 
    vector<Fiche> moins_jeunes; 
    for_each(vdata.begin(), vdata.end(), [&jeunes, &moins_jeunes](const Fiche& f)
    {
        if(f.age <= 40) jeunes.push_back(f); 
        else moins_jeunes.push_back(f); 
    });

    //Q.3 
    sort(sorted_vdata.begin(), sorted_vdata.end(), compare); 
    ofstream fichier4("ordre.txt"); 
    for_each(sorted_vdata.begin(), sorted_vdata.end(), [&fichier4](const Fiche &f)
    {
        fichier4 << f.prenom << "\t" << f.ville << "\t" << f.age << "\t" << f.temps << "\n"; 
    });
    fichier4.close(); 

    //Q.4
    map<int,int> H; 
    for_each(vdata.begin(), vdata.end(), [&H](const Fiche& f)
    {
        H[f.age]++; 
    }); 
    cout << "~ Histogramme des âges ~" << endl; 
    for_each(H.begin(), H.end(), [](const pair<int,int>& p)
    {
        cout << p.first << "ans, représenté " << p.second << " fois." << endl; 
    });
    /* Output : 
    ~ Histogramme des âges ~
    20ans, représenté 91 fois.
    21ans, représenté 80 fois.
    22ans, représenté 80 fois.
    23ans, représenté 76 fois.
    24ans, représenté 84 fois.
    25ans, représenté 80 fois.
    26ans, représenté 91 fois.
    27ans, représenté 101 fois.
    28ans, représenté 99 fois.
    29ans, représenté 99 fois.
    30ans, représenté 83 fois.
    31ans, représenté 54 fois.
    32ans, représenté 68 fois.
    33ans, représenté 83 fois.
    34ans, représenté 77 fois.
    35ans, représenté 79 fois.
    36ans, représenté 87 fois.
    37ans, représenté 73 fois.
    38ans, représenté 73 fois.
    39ans, représenté 99 fois.
    40ans, représenté 106 fois.
    41ans, représenté 86 fois.
    42ans, représenté 79 fois.
    43ans, représenté 88 fois.
    44ans, représenté 85 fois.
    45ans, représenté 71 fois.
    46ans, représenté 87 fois.
    47ans, représenté 93 fois.
    48ans, représenté 69 fois.
    49ans, représenté 78 fois.
    113ans, représenté 1 fois. */ 
    return 0; 
}