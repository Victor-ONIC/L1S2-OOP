#ifndef _COL_POINTS_H
#define _COL_POINTS_H

#include <iostream>
#include <random>
#include "Point.h"

class col_Points {

    /// Tableau de Points.
    Point *T;
    /// Nombre de Points dans le tableau.
    int nbp;
    /// Taille du tableau alloué.
    int cap;

public:
    col_Points();
    col_Points(const col_Points &C);
    ~col_Points();
    void afficher(int flag = 0);

    bool present(Point &p);
    void ajouter(Point &P, bool flag = true);
    void union_col(const col_Points &C);
    void valeurs(Point &centre, Point &loin);

    void remplir(int n);

};

#endif
