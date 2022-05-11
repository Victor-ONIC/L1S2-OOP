#include <iostream>

#include "vecteurs.h"

using namespace std;

int main() {
    cout << "\n==============les vecteurs======================" << endl;
    cout << "Test 1-a, 1-b, 2,c, 1-d, 1,e " << endl;
    vecteur A(2, 5, 2), B(3, 3, 3);
    A.afficher();
    cout << endl;
    cout << "----test addition----" << endl;
    vecteur C;
    C = A.add(B);
    cout << "la somme de A et B est:" << endl;
    C.afficher();
    cout << endl;
    cout << "----test produit scalaire----" << endl;
    double ps;
    ps = A.produit_scalaire(B);
    cout << "la produit de A et B est: " << ps << endl;
    cout << "----Test de la norme----" << endl;
    cout << "la norme de A est: ";
    cout << A.norme() << endl;
    cout << "----Test de identique----" << endl;
    A = B;
    if (A.identique(B))
        cout << "A et B sont identiques" << endl;
    else
        cout << "A et B sont différents" << endl;

    cout << "\n================ Collection ======================" << endl;
    cout << "----test constructeur, ajout et affichage -----" << endl;
    vecteur AA(2, 5, 2), BB(2, 3, 3), CC(1, 2, 2);
    collection_vecteurs Col(3);
    if (Col.ajouter(AA) == true)
        cout << "AA a été ajoutée" << endl;
    else
        cout << "AA ne peut être ajoutée" << endl;
    if (Col.ajouter(BB) == true)
        cout << "BB a été ajoutée" << endl;
    else
        cout << "BB ne peut être ajoutée" << endl;
    if (Col.ajouter(CC) == true)
        cout << "CC a été ajoutée" << endl;
    else
        cout << "CC ne peut être ajoutée" << endl;
    if (Col.ajouter(CC) == true)
        cout << "CC a été ajoutée" << endl;
    else
        cout << "CC ne peut être ajoutée" << endl;
    cout << "-----------affichage de la collection ----" << endl;
    Col.afficher();
    cout << "----test de la fonction recherche -----" << endl;
    vecteur H(2, 3);
    if (Col.chercher(H))
        cout << "H est présent" << endl;
    else
        cout << "H n'est pas présent" << endl;
    cout << "--- fin de test da la fonction recherche---" << endl;

    cout << "\n================liste===================" << endl;
    liste_vecteurs L1;

    cout << "test ajout---" << endl;
    vecteur a(2, 3, 3), b(1, 2, 2), c(2, 4, 2);
    L1.ajouter(a);
    L1.ajouter(b);
    L1.ajouter(c);
    L1.afficher();
    cout << "fin test ajout----" << endl;

    cout << "test supprimer---" << endl;
    vecteur d(2.0001, 4, 2);
    L1.supprimer(d);
    L1.afficher();
    cout << "fin test supprimer----" << endl;

    liste_vecteurs L2;
    vecteur aa(3, 3), bb(4, 4), cc(5, 5);
    L2.ajouter(aa);
    L2.ajouter(bb);
    L2.ajouter(cc);
    cout << "affichage de L2" << endl;
    L2.afficher();

    cout << "affichage de L1" << endl;
    L1.afficher();

    cout << "test union-----" << endl;
    liste_vecteurs* L3 = L1.Union(L2);
    cout << "affichage après Union de L1 avec L2---" << endl;
    (*L3).afficher();
    cout << "fin de test Union---" << endl;
    delete L3;

    cout << "test chercher-----" << endl;
    vecteur aaa(3.0001, 3, 3);
    if (L1.chercher(aaa) != NULL)
        cout << "aaa est présent" << endl;
    else
        cout << "aaa n'est pas présent" << endl;

    cout << "test supprimer-----" << endl;
    L1.supprimer(a);
    cout << "affichage après suppression" << endl;
    L1.afficher();
    cout << "fin test supprimer-----" << endl;

    cout << "test supprimer toutes les occurences-----" << endl;
    vecteur x(3.0001, 3, 3), y(3.01, 3.0001, 3);
    L1.ajouter(x);
    L1.ajouter(y);
    cout << "Affichage de L1 avaant suppression de toutes----" << endl;
    L1.afficher();
    L1.supprimer_toutes(x);
    cout << "Affichage de L1 après suppression de toutes----" << endl;
    L1.afficher();
    cout << "fin test supprimer toutes les occurences-----" << endl;
    cout << "==================Test de Inter==============" << endl;
    cout << "==============Créez le test vous même =======" << endl;

    vecteur v1(1, 2, 3), v2(4, 5, 6), v3(7, 8, 9);

    liste_vecteurs liste1;
    liste1.ajouter(v1);
    liste1.ajouter(v2);
    liste1.ajouter(v3);

    liste_vecteurs liste2;
    liste2.ajouter(v3);

    cout << "Liste numéro 1: \n";
    liste1.afficher();

    cout << "Liste numéro 2: \n";
    liste2.afficher();

    cout << "Intersection des deux listes: \n";
    liste_vecteurs* liste3 = liste1.Inter(liste2);
    liste3->afficher();
    delete liste3;
}
