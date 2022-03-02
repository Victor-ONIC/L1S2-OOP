#include "Point.h"
#include "Droite.h"

int main() {

    Point p1(0.0, 0.0);
    Point p2(1.0, 1.0);

    Point pA(1.2, 3.4);
    Point pB(5.01, 9.0);
    Point pC(3.0, 3.0);
    Point pD(9.2, 1.618);
    Point pE(18.0, 18.0);
    Point pts[] = {pA, pB, pC, pD, pE};
    int taille = 5;

    Droite d(1.0, 0.0);
    Droite d2(2.0, 0.0);

    // Test de la fonction 'affichage'.
    std::cout << "\n---Afficher un point:\n";
    p2.afficher();

    // Test de la fonction 'affichage_tab'.
    std::cout << "\n---Afficher un tableau de points:\n";
    affichage_tab(pts, taille);

    // Test de la fonction 'distance'.
    double distance = p1.distance(p2);
    std::cout << "---Distance entre les points (0,0) et (1,1):\n";
    std::cout << distance;

    // Test de la fonction 'appartient'.
    std::cout << "\n---Voir si un point appartient a la droite d: ";
    for (int i = 0; i < taille; i++) {
        if (d.appartient(pts[i])) {
            std::cout << "\nLe point ";
            pts[i].afficher();
            std::cout << " appartient à la droite d.";
        }
        else {
            std::cout << "\nLe point ";
            pts[i].afficher();
            std::cout << " n'appartient pas à la droite d.";
        }
    }

    // Test de la fonction 'parallele'
    std::cout << "\n---Voir si les droites d et d2 sont paralelles:\n";
    if (d.parallele(d2)) {
        std::cout << "Les droites sont bien paralleles.";
    }
    else {
        std::cout << "Les droites ne sont pas paralleles.";
    }

    // Test de la fonction 'appartient_tab'.
    std::cout << "\n---Voir quels points d'un tableau de points appartiennent a la droite d\n";
    int n = 0;
    Point *app = d.appartient_tab(pts, taille, n);
    if (n != 0) {
        affichage_tab(app, n);
    }
    else {
        std::cout << "Aucun.\n";
    }
    delete[] app;

    return 0;

}
