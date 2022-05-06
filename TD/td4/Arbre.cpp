#include "Arbre.hpp"

Arbre::Arbre() : racine(nullptr) 
{ }

Arbre::Arbre(Noeud* p) : racine(p) 
{ }

Arbre::Arbre(const Arbre& other)
{
    racine = copie(other.racine);
}

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

int Arbre::inserer(int info)
{
    if (racine == nullptr)
    {
        racine = new Noeud(info, nullptr, nullptr);
        return 1;
    }
    else
    {
        return inserer(racine, info);
    }
}

int Arbre::inserer(Noeud* n, int info)
{
    if (info == n->info)
    {
        return 0;
    }

    if (info < n->info)
    {
        if (n->fg != nullptr)
        {
            inserer(n->fg, info);
        }
        else
        {
            n->fg = new Noeud(info, nullptr, nullptr);
            return 1;
        }
    }
    else
    {
        if (n->fd != nullptr)
        {
            inserer(n->fd, info);
        }
        else
        {
            n->fd = new Noeud(info, nullptr, nullptr);
            return 1;
        }
    }
}

bool Arbre::equal(Arbre& other)
{
    return equal(racine, other.racine);
}

bool Arbre::equal(Noeud* n1, Noeud* n2)
{
    if (n1 == nullptr && n2 == nullptr)
    {
        return true;
    }

    if (n1 == nullptr || n2 == nullptr)
    {
        return false;
    }

    return n1->info == n2->info &&
           equal(n1->fg, n2->fg) &&
           equal(n1->fd, n2->fd);
}

Noeud* Arbre::copie(Noeud* n)
{
    if (n == nullptr) return nullptr;
    return new Noeud(n->info, copie(n->fg), copie(n->fd));
}

Noeud* Arbre::arbre_miroir(const Arbre& other)
{
    racine = arbre_miroir(other.racine);
}

Noeud* Arbre::arbre_miroir(Noeud* n)
{
    if (n == nullptr) return nullptr;
    new Noeud(n->info, arbre_miroir(n->fd), arbre_miroir(n->fg));
}

bool Arbre::sous_arbre(const Arbre& other)
{
    return sous_arbre(racine, other.racine);
}

bool Arbre::sous_arbre(Noeud* n1, Noeud* n2)
{
    if (equal(n1, n2)) return true;
    if (n2 != nullptr) return sous_arbre(n1, n2->fg) || sous_arbre(n1, n2->fd);
    return false;
}
