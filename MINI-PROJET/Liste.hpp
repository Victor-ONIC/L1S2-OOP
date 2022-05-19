/**
 * @file    Liste.hpp
 * @author  ONIC Victor (victor.onic@outlook.fr)
 * @date    19-05-2022
 * 
 * Fichier d'entête de la classe Liste.
 */

#ifndef LISTE_H
#define LISTE_H

#include "Noeud.hpp"

///  Classe Liste
class Liste
{
private:
    Noeud* m_tete;

public:
    Liste();

    const char* readfile(const std::string& filename, int& taille);            //  q.0
    void inserer_tete(Noeud* n);                                               //  q.1
    void inserer_tete(char c, int effectif);                                   //  q.1
    void inserer_les_caracteres(const char* s, int N);                         //  q.1
    Noeud* supprimer_plus_petit();                                             //  q.2

    friend class Arbre;
};

#endif // LISTE_H
