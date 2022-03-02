#include "td1.h"

// OPTIMISER TOUT LE PROGRAMME POUR PRENDRE EN CONSIDÉRATION L'UTILISATEUR STUPIDE

void print_tab(Point *P, int N) {
    for (int i = 0; i < N; i++) {
        P[i].afficher();
    }
}

void saisir_tab(Point *P, int N) {
    for (int i = 0; i < N; i++) {
        P[i].saisir();
    }
}

Point *saisir_points(int &N) {
    std::cin >> N;
    Point *P = new Point[N];
    saisir_tab(P, N);
    return P;
}

int main() {

    // Classe Point.
    std::cout << "\n--- Afficher un point ---\n";
    Point p1;
    p1.afficher();

    std::cout << "\n--- Saisir et afficher un point ---\n";
    Point p2;
    p2.saisir();
    p2.afficher();

    std::cout << "\n--- Distance entre deux points (0,0) et (1,1) ---\n";
    Point p3;
    Point p4(1.0, 1.0);
    double d = p3.distance(p4);
    std::cout << d << '\n';

    std::cout << "\n--- Afficher un tableau de points ---\n";
    Point T[4];
    T[0] = p1;
    T[1] = p2;
    T[2] = p3;
    T[3] = p4;
    print_tab(T, 4);

    std::cout << "\n--- Saisir un tableau de points ---\n";
    saisir_tab(T, 4);

    std::cout << "\n--- Allouer un tableau de points ---\n";
    int N;
    Point *K = saisir_points(N);
    print_tab(K, N);
    delete[] K;

    // Classe Cercle.
    std::cout << "\n--- Afficher un cercle ---\n";
    Cercle c1;
    c1.affichage();

    std::cout << "\n--- Afficher, saisir et afficher un cercle ---\n";
    Cercle c2(p2, 11);
    c2.affichage();
    c2.saisir();
    c2.affichage();

    return 0;

}
