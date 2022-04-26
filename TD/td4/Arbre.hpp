#ifndef ARBRE_H
#define ARBRE_H

#include <iostream>
#include "Noeud.hpp"

class Arbre
{
private:
    Noeud* racine;

    int hauteur(Noeud* n);
    void maximum(Noeud* n, int& max);

public:
    Arbre();
    Arbre(Noeud* p);
    ~Arbre();

    void detruit(Noeud* n);
    void profondeur(Noeud* n, int p);
    int hauteur();
    bool maximum(int& max);
    bool maximum_ordonne(int& max);
};

#endif
