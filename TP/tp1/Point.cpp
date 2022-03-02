#include "Point.h"

Point::Point(double a, double b) : x(a), y(b) {}

double Point::get_x() { return x; }

double Point::get_y() { return y; }

double Point::distance(Point &p) {
    double d = sqrt( pow(p.get_x() - x,2) + pow(p.get_y() - y,2) );
    return d;
}

void Point::afficher() {
    std::cout << '(' << x << " , " << y << ')';
}

void affichage_tab(Point *T, int N) {
    for (int i = 0; i < N; i++) {
        T[i].afficher();
        std::cout << '\n';
    }
}
