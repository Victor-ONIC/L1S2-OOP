#ifndef _MAILLON_H
#define _MAILLON_H

#include "Liste.h"

class Maillon {
    friend class Liste;

    int info;
    Maillon *next;

public:
    Maillon();
    Maillon(int valeur);
    Maillon(int valeur, Maillon *m);
    ~Maillon();

    int get_info();
    Maillon* get_next();

};

#endif
