#include "Droite.h"

Droite::Droite(double x, double y) : a(x), b(y) {}

Droite::Droite(Point &A, Point &B) {
    a = (B.get_y() - A.get_y()) / (B.get_x() - A.get_x());
    b = A.get_y() - a * A.get_x();
}

double Droite::get_a() { return a; }

double Droite::get_b() { return b; }

bool Droite::appartient(Point &p) {
    if (p.get_y() == a * p.get_x() + b) {
        return true;
    }
    else {
        return false;
    }
}

bool Droite::parallele(Droite &d) {
    if (d.get_a() == a) {
        return true;
    }
    else {
        return false;
    }
}

Point *Droite::appartient_tab(Point *T, int N, int &newN) {

    int index = 0;
    for (int i = 0; i < N; i++) {
        if (appartient(T[i])) {
            index++;
        }
    }

    if (index != 0) {
        newN = index;
        Point *tab = new Point[newN];

        index = 0;
        for (int i = 0; i < N; i++) {
            if (appartient(T[i])) {
                tab[index] = T[i];
                index++;
            }
        }
        return tab;
    }
    else {
        newN = index;
        return nullptr;
    }
}
