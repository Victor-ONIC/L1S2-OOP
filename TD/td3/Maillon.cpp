#include "Maillon.h"

Maillon::Maillon() : info(0), next(nullptr) {}

Maillon::Maillon(int valeur) : info(valeur), next(nullptr) {}

Maillon::Maillon(int valeur, Maillon *m) : info(valeur), next(m) {}

int Maillon::get_info() { return info; }

Maillon* Maillon::get_next() { return next; }
