#ifndef _POINT_H
#define _POINT_H

#include <iostream>
#include <cmath>

class Point {

    double x, y;

public:
    Point(double a = 0.0, double b = 0.0);
    double get_x();
    double get_y();

    double distance(Point &p);
    void afficher();
    bool identiques(Point &p);

};

void affichage_tab(Point *T, int N);

#endif
