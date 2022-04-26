#ifndef NOEUD_H
#define NOEUD_H

class Noeud
{
private:
    int info;
    Noeud *fg, *fd;  // fils gauche, fils droit

public:
    Noeud(int valeur, Noeud* g, Noeud* d);
    ~Noeud();

    friend class Arbre;
};

#endif
