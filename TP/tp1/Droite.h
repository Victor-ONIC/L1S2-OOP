#ifndef _DROITE_H
#define _DROITE_H

#include "Point.h"

class Droite {

    double a, b;

public:
    Droite(double x, double y);
    Droite(Point &A, Point &B);
    double get_a();
    double get_b();

    bool appartient(Point &p);
    bool parallele(Droite &d);
    Point *appartient_tab(Point *T, int N, int &newN);

};

#endif
