#include "Arbre.hpp"

Arbre::Arbre() : racine(nullptr) 
{ }

Arbre::Arbre(Noeud* p) : racine(p) 
{ }

Arbre::~Arbre()
{
    if (racine != nullptr)
    {
        delete racine;
    }
}

void Arbre::detruit(Noeud* n)
{
    if (n != nullptr)
    {
        detruit(n->fg);
        detruit(n->fd);
        delete n;
    }
}

void Arbre::profondeur(Noeud* n, int p)
{
    if (n != nullptr)
    {
        profondeur(n->fg, p + 1);
        profondeur(n->fd, p + 1);
        std::cout << p << std::endl;
    }
}

int Arbre::hauteur() 
{
    return hauteur(racine);
}

int Arbre::hauteur(Noeud* n)
{
    int h_d = 0, h_g = 0;

    if (n == nullptr)
    {
        return 0;
    }

    h_g = hauteur(n->fg);
    h_d = hauteur(n->fd);

    if (h_d < h_g)
    {
        return h_g + 1;
    }
    else
    {
        return h_d + 1;
    }
}

bool Arbre::maximum(int& max)
{
    if (racine != nullptr)
    {
        max = racine->info;
        maximum(racine, max);
        return true;
    }
    return false;
}

void Arbre::maximum(Noeud* n, int& max)
{
    if (n != nullptr)
    {
        if (max < n->info)
        {
            max = n->info;
        }
        maximum(n->fg, max);
        maximum(n->fd, max);
    }
}

bool Arbre::maximum_ordonne(int& max)
{
    Noeud* p = racine;
    if (p != nullptr)
    {
        while (p != nullptr)
        {
            max = p->info;
            p = p->fd;
        }
        return true;
    }
    return false;
}
