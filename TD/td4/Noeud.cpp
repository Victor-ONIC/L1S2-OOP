#include "Noeud.hpp"

Noeud::Noeud(int valeur, Noeud* g, Noeud* d)
    : info(valeur), fg(g), fd(d)
{ }

Noeud::~Noeud()
{
    if (fg != nullptr)
    {
        delete fg;
    }
    
    if (fd != nullptr)
    {
        delete fd;
    }
}
