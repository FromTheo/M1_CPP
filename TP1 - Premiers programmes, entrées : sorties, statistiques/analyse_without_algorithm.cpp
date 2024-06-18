#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath> 
#include <set> 

using namespace std; 

struct Fiche
{
    string prenom; 
    string ville; 
    int age; 
    double temps; 
}; 

int main()
{
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
    int compteur_lyon = 0; 
    for(const Fiche & f : vdata)
    {
        if(f.ville == "Lyon") compteur_lyon++; 
    }
    cout << "a) Il y a " << compteur_lyon << " lyonnais. Soit " << compteur_lyon*100/(double)N << "% des personnes du fichier." << endl; 
    //Output : a) Il y a 424 lyonnais. Soit 16.96% des personnes du fichier.

    //Q.3.b
    int compteur_lyon_jeune = 0; 
    for(const Fiche& f : vdata)
    {
        if(f.ville == "Lyon" && f.age < 30) compteur_lyon_jeune++; 
    }
    cout << "b) Il y a " << compteur_lyon_jeune << " lyonnais de moins de 30 ans." << endl; 
    //Output : b) Il y a 148 lyonnais de moins de 30 ans.

    //Q.3.c
    bool toulousain_A = false; 
    for(const Fiche & f : vdata)
    {
        if(f.ville == "Toulouse" && f.prenom.front() == 'A') toulousain_A = true; 
    }
    if(toulousain_A) cout << "c) Il y a un toulousain dont le prénom commence par A." << endl; 
    else cout << "c) Il n'y a pas de toulousains dont le prénom commence par A." << endl; 
    //Output : c) Il y a un toulousain dont le prénom commence par A.

    //Q.3.d 
    int age_minimum = INT_MAX; 
    string prenom_age_minimum; 
    for(const Fiche &f : vdata)
    {
        if(f.age < age_minimum)
        {
            age_minimum = f.age; 
            prenom_age_minimum = f.prenom; 
        }
    }
    int age_maximum = 0; 
    string prenom_age_maximum; 
    for(const Fiche& f : vdata)
    {
        if(f.age > age_maximum)
        {
            age_maximum = f.age; 
            prenom_age_maximum = f.prenom; 
        }
    }
    cout << "d) C'est " << prenom_age_minimum << " le plus jeune avec " << age_minimum << " ans. Et c'est " << prenom_age_maximum << " le plus âgé avec " << age_maximum << " ans. " << endl; 
    //Output : d) C'est Bruno le plus jeune avec 20 ans. Et c'est Jabba le plus âgé avec 113 ans. 

    //Q.3.e 
    double moyenne = 0.0; 
    for(const Fiche &f : vdata)
    {
        moyenne += f.age; 
    }
    moyenne /=(double)N; 
    double variance = 0.0; 
    for(const Fiche &f : vdata)
    {
        variance += (f.age-moyenne)*(f.age-moyenne);
    }
    variance /=(double)N; 
    double ecart_type = sqrt(variance); 
    cout << "e) L'âge moyen des personnes du fichier est  : " << moyenne << ", tandis que l'écart type est : " << ecart_type << endl;
    //Output : e) L'âge moyen des personnes du fichier est  : 34.4452, tandis que l'écart type est : 8.78702. 

    //Q.3.f 
    double moyenne_temps_paris = 0.0; 
    double moyenne_temps_marseille = 0.0; 
    int nb_habitants_paris = 0;
    int nb_habitants_marseille = 0; 
    for(const Fiche& f : vdata)
    {   
        if(f.ville == "Paris")
        {
            moyenne_temps_paris += f.temps; 
            nb_habitants_paris++; 
        }
        if(f.ville == "Marseille")
        {
            moyenne_temps_marseille += f.temps; 
            nb_habitants_marseille++; 
        }
    }
    moyenne_temps_paris /= (double)nb_habitants_paris;
    moyenne_temps_marseille /= (double)nb_habitants_marseille; 
    cout << "f) Les parisiens ont une moyenne de " << moyenne_temps_paris << "s, tandis que les marseillais " << moyenne_temps_marseille << "s. "; 
    if(moyenne_temps_paris < moyenne_temps_marseille) cout << "Les parisiens sont donc plus rapides." << endl; 
    else cout << "Les marseillais sont donc plus rapides." << endl; 
    //Output : f) Les parisiens ont une moyenne de 14.3985s, tandis que les marseillais 14.4155s. Les parisiens sont donc plus rapides.

    //Q.3.g
    ofstream fichier_toulousains("toulousains.txt"); 
    for(const Fiche& f : vdata)
    {
        if(f.ville == "Toulouse")
        {
            fichier_toulousains << f.prenom << "\t" << f.ville << "\t" << 2018-f.age << "\t" << f.temps << endl; 
        }
    }
    fichier_toulousains.close();
    
    //Q.3.h
    int nb_habitants_toulouse = 0; 
    double moyenne_age_toulouse = 0.0; 
    double moyenne_temps_toulouse = 0.0; 
    double covariance = 0.0; 
    for(const Fiche& f : vdata)
    {
        if(f.ville == "Toulouse")
        {
            nb_habitants_toulouse++;
            moyenne_age_toulouse += f.age; 
            moyenne_temps_toulouse += f.temps; 
        }
    }
    moyenne_age_toulouse /= (double)nb_habitants_toulouse;
    moyenne_temps_toulouse /= (double)nb_habitants_toulouse; 
    for(const Fiche &f : vdata)
    {
        if(f.ville == "Toulouse")
        {
            covariance += (f.age-moyenne_age_toulouse)*(f.temps-moyenne_temps_toulouse); 
        }
    }
    covariance /= (double)(nb_habitants_toulouse-1);  
    cout << "h) L'âge moyen est : " << moyenne_age_toulouse << ", le temps moyen au 100m est : " << moyenne_temps_toulouse << endl; 
    cout << "La covariance entre age des temps des toulousains est de : " << covariance << endl;  
    /*Output : h) L'âge moyen est : 33.8036, le temps moyen au 100m est : 14.3344
    La covariance entre age des temps des toulousains est de : 10.5591 */ 

    //Q.3.i
    set<string> villes; 
    for(const Fiche &f : vdata)
    {
        villes.insert(f.ville); 
    }
    cout << "i) Il y a un total de " << villes.size() << " villes représentées. On retrouve : " << endl;
    for(const string& city : villes)
    {
        cout << "- " << city << endl; 
    }
    /* Output : 
    i) Il y a un total de 11 villes représentées. On retrouve : 
    - Bordeaux
    - Brest
    - Clermont-Ferrand
    - Kingston
    - Lille
    - Lyon
    - Marseille
    - Montcuq
    - Paris
    - Tatouine
    - Toulouse */

    //Q.4 
    ifstream fichier2("smalldata.txt"); 
    vector<Fiche> vdata2; 
    string prenom; 
    string ville; 
    int age; 
    double temps; 
    while(fichier2 >> prenom >> ville >> age >> temps)
    {
        vdata2.push_back(Fiche{prenom, ville, age, temps}); 
    }
    fichier2.close(); 

    return 0; 
}