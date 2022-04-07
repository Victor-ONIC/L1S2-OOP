#ifndef _LISTE_H
#define _LISTE_H

#include <iostream>

#include "Carte.h"

class Liste {

    Carte *head;
    Carte *tail;

public:

    Liste(bool plein = false);
    ~Liste();

    Carte *get_head();
    Carte *get_tail();

    void ajouter_fin(int valeur, int couleur);
    void ajouter_debut(int valeur, int couleur);
    void remove();
    void vider();
    void afficher();
    void tri_croissant_valeur_couleur();
    void tri_decroissant_couleur_valeur();
    void melanger();
    Liste *distribuer(int nb_joueurs);
};

#endif
