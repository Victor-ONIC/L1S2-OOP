#ifndef _CARTE_H
#define _CARTE_H

class Carte {

    // 2, 3, 4, 5, 6, 7, 8, 9, 10, Valet, Dame, Roi, As = 14
    // Trèfle: 0, Carreau: 1, Coeur: 2, Pique: 3
    int valeur;
    int couleur;
    Carte *next;

public:

    Carte();
    Carte(int v, int c);
    Carte(int v, int c, Carte *p);

    int get_valeur();
    int get_couleur();
    Carte *get_next();

    friend class Liste;
};

#endif
