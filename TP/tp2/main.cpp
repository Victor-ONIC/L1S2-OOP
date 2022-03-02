#include "Point.h"
#include "Collection.h"

int main() {

    Point p1(1.0, 2.0);
    Point p2(5.0, 6.5);
    Point p3(9.2, 7.0);
    Point p4(2.25, 3.1);
    Point p5(0.2, 5.0);
    Point p6(2.225, 9.99);
    Point p7(1.111, 2.9);
    Point p8(51.23, 45.25);
    Point p9(8.3, 5.5);
    Point p10(1.125, 5.0);
    Point p11(0.00123, 0.0987);
    Point p12(10.0, 10.0);
    Point tableau[] = {p7, p8, p9, p10, p11, p12};
    Point p13(1.618, 3.1415);
    Point p14(88.8, 6.66);
    Point p15(2.11, 2.2);
    Point r[5];

    // Test de la fonction 'identique' (q.0).
    std::cout << "\n--- Fonction 'identique' ---\n";
    if (p1.identiques(p1)) {
        std::cout << "Les points sont egaux.\n";
    }
    else {
        std::cout << "Les points ne sont pas egaux.\n";
    }

    // Test du constructeur (q.2).
    std::cout << "\n--- Constructeur ---\n";
    Collection C;
    C.afficher();

    // Test de la fonction 'ajout' (q.5).
    std::cout << "\n--- Fonction 'ajout' ---\n";
    C.ajout(p1);
    C.afficher();

    // Test de la fonction 'present' (q.4).
    std::cout << "\n--- Fonction 'present' ---\n";
    if (C.present(p1)) {
        std::cout << "Le point est present dans la collection.\n";
    }
    else {
        std::cout << "Le point n'est pas present dans la collection.\n";
    }

    // Test de la fonction 'supprimer' (q.6).
    std::cout << "\n--- Fonction 'supprimer' ---\n";
    C.ajout(p2);
    C.ajout(p3);
    std::cout << "Avant suppression:\n";
    C.afficher();
    C.supprimer(p2);
    std::cout << "Apres suppression:\n";
    C.afficher();
    
    // Test de la fonction 'ajouter_bis' (q.7).
    std::cout << "\n--- Fonction 'ajouter_bis' ---\n";
    C.ajout(p2);
    C.ajout(p4);
    C.ajouter_bis(p5);
    std::cout << "Le tableau est plein.\n";
    C.afficher();
    std::cout << "\nJ'ajoute un autre point.\n";
    C.ajouter_bis(p6);
    C.afficher();

    // Test de la fonction 'ajouter_tab' (q.8).
    std::cout << "\n--- Fonction 'ajouter_tab' ---\n";
    C.ajouter_tab(tableau, 6);
    C.afficher();

    // Test du constructeur par recopie (q.9).
    std::cout << "\n--- Constructeur par recopie ---\n";
    std::cout << "La collection C:\n";
    C.afficher();
    std::cout << "\nLa collection D:\n";
    Collection D(C);
    D.afficher();

    // Test de la fonction 'intersection' (q.10).
    std::cout << "\n--- Fonction 'intersection' ---\n";
    Collection E;
    for (int i = 0; i < 6; i++) {
        D.supprimer(tableau[i]);
    }
    std::cout << "La collection C:\n";
    C.afficher();
    std::cout << "\nLa collectiion D:\n";
    D.afficher();
    std::cout << "\nL'intersection:\n";
    C.intersection(D, E);
    E.afficher();

    // Test du constructeur qui fait l'union de deux collections (q.11).
    std::cout << "\n--- Constructeur union de deux colections ---\n";
    Collection F;
    F.ajouter_bis(p13);
    F.ajouter_bis(p14);
    F.ajouter_bis(p15);
    std::cout << "La collection E:\n";
    E.afficher();
    std::cout << "\nLa collection F:\n";
    F.afficher();
    std::cout << "\nL'union:\n";
    Collection G(E, F);
    G.afficher();

    // Test de la fonction 'pts_remarquables' (q.12).
    std::cout << "\n--- Fonction 'pts_remarquables' ---\n";
    G.pts_remarquables(r[0], r[1], r[2], r[3], r[4]);
    std::cout << "Les points remarquables de la collection G:\n";
    std::cout << "La plus grande abscisse: ";
    r[0].afficher();
    std::cout << "\nLa plus grande ordonnee: ";
    r[1].afficher();
    std::cout << "\nLa plus petite abscisse: ";
    r[2].afficher();
    std::cout << "\nLa plus petite ordonnee: ";
    r[3].afficher();
    std::cout << "\nLe centre de tous les points de la collection: ";
    r[4].afficher();
    std::cout << '\n';

    return 0;
}
