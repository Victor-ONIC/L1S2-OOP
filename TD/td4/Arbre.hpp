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
    int inserer(Noeud* n, int info);
    bool equal(Noeud* n1, Noeud* n2);
    Noeud* copie(Noeud* n);
    Noeud* arbre_miroir(Noeud* n);
    bool sous_arbre(Noeud* n, Noeud* n2);

public:
    Arbre();
    Arbre(Noeud* p);
    Arbre(const Arbre& other);
    ~Arbre();

    void detruit(Noeud* n);
    void profondeur(Noeud* n, int p);
    int hauteur();
    bool maximum(int& max);
    bool maximum_ordonne(int& max);
    int inserer(int info);
    bool equal(Arbre& other);
    Noeud* arbre_miroir(const Arbre& other);
    bool sous_arbre(const Arbre& other);
};

#endif
