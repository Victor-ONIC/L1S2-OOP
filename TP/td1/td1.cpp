#include "td1.h"

// Méthodes de la classe Point.
Point::Point() : x(0.0), y(0.0) {}

Point::Point(double posX, double posY) : x(posX), y(posY) {}

double Point::get_x() {
    return x;
}

double Point::get_y() {
    return y;
}

void Point::afficher() {
    std::cout << '(' << x << " , " << y << ')' << '\n';
}

void Point::saisir() {
    double posX, posY;
    std::cin >> posX >> posY;
    x = posX, y = posY;
}

double Point::distance(Point &p) {
    double d = sqrt( pow(p.get_x() - x,2) + pow(p.get_y() - y,2) );
    return d;
}

// Méthodes de la classe Cercle.
Cercle::Cercle() : radius(0), center() {}

Cercle::Cercle(Point &origine, double r) : radius(r), center(origine) {}

void Cercle::affichage() {
    std::cout << "Centre: ";
    center.afficher();
    std::cout << "Radius: " << radius << '\n';
}

void Cercle::saisir() {
    Point p;
    double r;
    p.saisir();
    std::cin >> r;
    center = p;
    radius = r;
}
