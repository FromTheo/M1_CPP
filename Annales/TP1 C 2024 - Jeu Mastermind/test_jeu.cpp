#include "mastermind.hpp"

using namespace std; 

int main()
{
    // I. Premières méthodes et premiers tests. 
    CodeSecret c0;
    cout << "C0 : " << c0 <<  endl; //Output : C0 : 

    vector<int> v1{1,2,0,8,6,7};
    CodeSecret c1(v1,10);
    cout << "C1 : " << c1 << endl;
    cout << "Le code secret C1 possède " << c1.size() << " éléments. Son maximum est " << c1.value_max() << ". La cinquième valeur de ce code est " << c1[4] << "." << endl;
    /* Output : C1 : 1 2 0 8 6 7 
    Le code secret C1 possède 6 éléments. Son maximum est 10. La cinquième valeur de ce code est 6. */ 

    
    vector<int> v2{0,5,2,1};
    CodeSecret c2(v2);
    cout << "C2 : " << c2 << std::endl;
    cout << "Le code secret C2 possède "<< c2.size() << " éléments. Son maximum est " << c2.value_max() << ". La troisième valeur de ce code est " << c2[2] << "." << endl;
    /* Output : C2 : 0 5 2 1 
    Le code secret C2 possède 4 éléments. Son maximum est 5. La troisième valeur de ce code est 2. */


    // II. Comparaison des codes. 
    cout << "Le code secret est " << c2 <<endl;
    //Output : Le code secret est 0 5 2 1 
    std::vector<int> w{1,3,2,5};
    CodeSecret c3(w);

    cout << "La proposition du décodeur est " << c3 << endl;
    //Output : La proposition du décodeur est 1 3 2 5 

    int BVBE = c2.BonneValeurBonEndroit(c3);
    int BVME = c2.BonneValeurMauvaisEndroit(c3);
    cout << "Dans la proposition du décodeur, il y a " << BVBE << " bonne valeur bien placée et " << BVME << " bonnes valeurs mal placées." << endl;
    //Output : Dans la proposition du décodeur, il y a 1 bonne valeur bien placée et 2 bonnes valeurs mal placées.


    // III. Décodeur. 
    string nom = "Tom";
    Decodeur D(nom);
    nom = "Arthur";

    CodeSecret proposition = D.ProposerCode(4, 5);
    cout << "Votre proposition est " << proposition << endl;

    // IV. Mastermind. 
    Decodeur Joueur(nom);
    Mastermind M(10, c2);
    bool reponse = M.jouer(Joueur);

    mt19937_64 G(time(nullptr)); 
    CodeSecret c4(4,5,G); 
    Mastermind M2(10,c4); 
    bool reponse2 = M2.jouer(Joueur);

    return 0; 
}
