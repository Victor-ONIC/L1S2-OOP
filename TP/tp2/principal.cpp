#include <random>
#include <cmath>
#include <chrono>

#include "Point.h"
#include "col_Points.h"

int main() {

    Point p1(1.0, 2.0);
    Point p2(5.0, 6.5);
    Point p3(9.2, 7.0);
    Point p4(2.25, 3.1);
    Point p5(0.2, 5.0);

    // Test de la fonction 'identiques' (q.0).
    std::cout << "\n--- Fonction 'identiques' ---\n";
    if (p1.identiques(p1)) {
        std::cout << "Les points sont egaux.\n";
    }
    else {
        std::cout << "Les points ne sont pas egaux.\n";
    }

    // Test du constructeur (q.1).
    std::cout << "\n--- Constructeur ---\n";
    std::cout << "Creation de l'objet C de type col_Points.\n";
    col_Points C;

    // Test de la fonction 'afficher' (q.5).
    std::cout << "\n--- Fonction 'affichage' ---\n";
    std::cout << "Affichage de la collection C:\n";
    C.afficher();

    // Test de la fonction 'ajout' (q.4).
    std::cout << "\n--- Fonction 'ajout' ---\n";
    std::cout << "Ajout du point p1 dans la collection C:\n";
    C.ajouter(p1);
    C.afficher();

    // Test de la fonction 'present' (q.3).
    std::cout << "\n--- Fonction 'present' ---\n";
    if (C.present(p1)) {
        std::cout << "Le point p1 est present dans la collection.\n";
    }
    else {
        std::cout << "Le point p1 n'est pas present dans la collection.\n";
    }

    // Test du constructeur par recopie (q.6).
    std::cout << "\n--- Constructeur par recopie ---\n";
    std::cout << "Affichage de la collection C:\n";
    C.afficher();
    std::cout << "\nAffichage de la collection D = C:\n";
    col_Points D(C);
    D.afficher();

    // Test de la fonction 'union_col' (q.7).
    std::cout << "\n--- Fonction 'union_col' ---\n";
    D.ajouter(p2);
    D.ajouter(p3);
    std::cout << "Affichage de la collection C:\n";
    C.afficher();
    std::cout << "\nAffichage de la collection D:\n";
    D.afficher();
    std::cout << "\nLa collection C apres l'appel de 'C.union_col(D)':\n";
    C.union_col(D);
    C.afficher();

    // Test de la fonction 'valeurs' (q.8).
    std::cout << "\n--- Fonction 'valeurs' ---\n";
    D.ajouter(p4);
    D.ajouter(p5);
    std::cout << "Affichage de la collection D:\n";
    D.afficher();
    Point centre, loin;
    D.valeurs(centre, loin);
    std::cout << "Le centre des points de la collection D est: ";
    centre.afficher();
    std::cout << "\nLe point de D le plus loin du centre est: ";
    loin.afficher();

    // q.9
    std::cout << "\n\n--- Derniere question ---\n";

    for (int i = 1; i < 9; i++) {
        int n = pow(10, i);
        std::cout << "\nCreation d'une collection vide.\n";
        col_Points E;
        std::cout << "Ajout de " << n << " points dans la collection...\n";
        E.remplir_zeros(n);
        std::cout << "La collection est remplie.\n";
        
        auto debut = std::chrono::system_clock::now();

        std::cout << "Debut de la recherche...\n";
        Point test(1.0, 1.0);
        if (E.present(test)) {
            std::cout << "Le point est bien present dans la collection.\n";
        }
        else {
            std::cout << "Le point n'est pas present dans la collection.\n";
        }

        std::chrono::duration<double, std::milli> temps = std::chrono::system_clock::now() - debut;
        std::cout << "Temps de recherche: " << temps.count() / 1000 << " s" << '\n';
    }

    std::cout << '\n';
    std::cout << "\nAppuyez sur ENTREE pour finir...\n";
    std::cin.get();
    return 0;
}
