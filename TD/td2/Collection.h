#ifndef _COLLECTION_H
#define _COLLECTION_H

#include <iostream>
#include "Point.h"

class Collection {

    /// Tableau de Points.
    Point *T;
    /// Nombre de Points dans le tableau.
    int nb_pts;
    /// Taille du tableau alloué (vide ou pas).
    int cap;

public:

    // Collection();
    Collection();
    Collection(const Collection &C);
    Collection(Collection &A, Collection &B);
    ~Collection();
    void afficher();

    bool present(Point &p);
    bool ajout(Point &p);
    bool supprimer(Point &p);
    void ajouter_bis(Point &p);
    void ajouter_tab(Point *P, int N);
    void intersection(const Collection &A, Collection &B);
    void pts_remarquables(Point &g_x, Point &g_y, Point &l_x, Point &l_y, Point &m);

};

#endif
