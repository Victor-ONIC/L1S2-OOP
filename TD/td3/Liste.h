#ifndef _LISTE_H
#define _LISTE_H

#include <iostream>
#include "Maillon.h"

class Maillon;

class Liste {

    Maillon *head;

public:
    Liste();
    Liste(int *T, int N);
    Liste(const Liste &L);
    ~Liste();

    Maillon* get_head();

    void afficher(bool flag = false);
    void afficher_inverse(Maillon *m);
    void ajouter_fin(int valeur);
    int cardinal();
    bool chercher(int valeur);
    bool chercher2(int valeur);
    int nb_occurences(int valeur);
    void supprimer(int valeur);
    void supprimer_tout(int valeur);

};

#endif
