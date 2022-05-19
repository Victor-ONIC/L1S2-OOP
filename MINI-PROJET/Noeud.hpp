/**
 * @file    Noeud.hpp
 * @author  ONIC Victor (victor.onic@outlook.fr)
 * @date    19-05-2022
 * 
 * Fichier d'entête de la classe Noeud.
 */

#ifndef NOEUD_H
#define NOEUD_H

#include <cstddef>
#include <fstream>
#include <string>

///  Classe Noeud
class Noeud
{
private:
    char m_char;
    int m_effectif;
    Noeud* m_suiv;
    Noeud* m_fg;
    Noeud* m_fd;

public:
    Noeud();
    Noeud(char c);
    Noeud(char c, int effectif);
    Noeud(char c, int effectif, Noeud* suivant);
    Noeud(int effectif, Noeud* fg, Noeud* fd);
    ~Noeud();

    void visiter(const char* T, int taille, std::string* codes);
    void ecrire_noeud(std::ofstream& of);
    void inserer(const std::string& s, size_t& ind);

    friend class Liste;
    friend class Arbre;
};

#endif // NOEUD_H
