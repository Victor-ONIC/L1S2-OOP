#include <iostream>
#include <cmath>

class Point {

    double x, y;

public:
    Point();
    Point(double posX, double posY);
    double get_x();
    double get_y();

    void afficher();
    void saisir();
    double distance(Point &p);

};

class Cercle {

    Point center;
    double radius;

public:
    Cercle();
    Cercle(Point &O, double r);

    void affichage();
    void saisir();

};
