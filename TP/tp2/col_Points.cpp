#include "col_Points.h"

col_Points::col_Points() : nbp(0), cap(100) {
    T = new Point[cap];
}

col_Points::col_Points(const col_Points &C) : nbp(C.nbp), cap(C.cap) {
    T = new Point[cap];
    for (int i = 0; i < C.nbp; i++) {
        T[i] = C.T[i];
    }
}

col_Points::~col_Points() {
    delete[] T;
    // Test du destructeur (q.2).
    std::cout << "--- Test du destructeur ---\n";
}

void col_Points::afficher(int flag) {
    std::cout << "Collection - points: " << nbp << " cap: " << cap << '\n';
    if (nbp == 0) {
        std::cout << "La collection est vide.\n";
    }
    else {
        if (flag == 0) {
            for (int i = 0; i < nbp; i++) {
                T[i].afficher();
                std::cout << '\n';
            }
        }
    }
}

bool col_Points::present(Point &p) {
    for (int i = 0; i < nbp; i++) {
        if (p.identiques(T[i])) {
            return true;
        }
    }
    return false;
}

void col_Points::ajouter(Point &P, bool flag) {
    if (present(P) && flag) {
        return;
    }
    // Si nbp = cap, augmenter la taille.
    if (nbp == cap) {
        Point *nouveau = new Point[cap * 2];
        for (int i = 0; i < nbp; i++) {
            nouveau[i] = T[i];
        }
        delete[] T;
        T = nouveau;
        cap = cap * 2;
    }
    // Ajouter le point, avec ou sans agrandissement.
    T[nbp] = P;
    nbp++;
}

void col_Points::union_col(const col_Points &C) {
    for (int i = 0; i < C.nbp; i++) {
        ajouter(C.T[i]);
    }
}

void col_Points::valeurs(Point &centre, Point &loin) {
    double m_x = 0, m_y = 0;
    for (int i = 0; i < nbp; i++) {
        m_x += T[i].get_x();
        m_y += T[i].get_y();
    }
    Point milieu(m_x / nbp, m_y / nbp);
    centre = milieu;

    double distance = 0;
    for (int j = 0; j < nbp; j++) {
        if (centre.distance(T[j]) > distance) {
            distance = centre.distance(T[j]);
            loin = T[j];
        }
    }
}

void col_Points::remplir_zeros(int n) {
    Point e;
    for (int i = 0; i < n; i++) {
        ajouter(e, false);
    }
}
