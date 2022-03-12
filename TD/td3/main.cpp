#include "Maillon.h"
#include "Liste.h"

class Maillon;

void afficher_rec(Maillon *P) {
    if (P == nullptr) return;
    std::cout << P->get_info() << ' ';
    afficher_rec(P->get_next());
}

int main() {

    int T[] = {5,5,5,1,2,3,4,5,6,7,8,9,10};

    // Test du constructeur
    Liste L(T, 12);

    // Test de la fonction 'afficher'
    L.afficher();

    // Test de la fonction 'afficher_rec'
    std::cout << "\nListe: ";
    afficher_rec(L.get_head());
    std::cout << '\n';

    // Test de la fonction 'afficher_inverse'
    std::cout << "\nListe: ";
    L.afficher_inverse(L.get_head());
    std::cout << '\n';
    
    // Test de la fonction 'cardinal'
    std::cout << "\nListe: " << L.cardinal() << " elements.\n";

    // Test de la fonction 'chercher'
    int valeur = 5;
    if (L.chercher(valeur)) {
        std::cout << '\n' << valeur << " appartient a la liste.\n";
    }
    else {
        std::cout << '\n' << valeur << " n'appartient pas a la liste.\n";
    }

    // Test de la fonction 'chercher2'
    if (L.chercher2(valeur)) {
        std::cout << '\n' << valeur << " appartient a la liste.\n";
    }
    else {
        std::cout << '\n' << valeur << " n'appartient pas a la liste.\n";
    }

    // Test de la fonction 'nb_occurences'
    int nb_valeur = L.nb_occurences(valeur);
    std::cout << "\nIl y a " << nb_valeur << " fois le nombre " << valeur << " dans la liste\n";

    // Test de la fonction 'supprimer'
    L.supprimer(10);
    L.afficher();

    // Test de la fonction 'supprimer_tout'
    L.supprimer_tout(5);
    L.afficher();

    // Test du constructeur par recopie
    Liste M(L);
    L.afficher(true);
    M.afficher(true);

    return 0;
}
