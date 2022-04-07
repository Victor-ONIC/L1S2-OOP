#include "Carte.h"

Carte::Carte() : valeur(0), couleur(-1), next(nullptr) {}

Carte::Carte(int v, int c) : valeur(v), couleur(c), next(nullptr) {}

Carte::Carte(int v, int c, Carte *p) : valeur(v), couleur(c), next(p) {}

int Carte::get_valeur() { return valeur; }

int Carte::get_couleur() { return couleur; }

Carte *Carte::get_next() { return next; }



