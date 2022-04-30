#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <iostream>  // TODO supprimer (1)
#include <cstddef>  // Pour NULL
#include <fstream>
#include <string>
#include <bitset>

/**
 * Classe Noeud
 */
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
    Noeud(char c, int effectif);
    Noeud(char c, int effectif, Noeud* suivant);
    Noeud(int effectif, Noeud* fg, Noeud* fd);

    void afficher();  // TODO supprimer (2)

    void visiter(const char* T, int taille, std::string* codes);

    friend class Liste;
    friend class Arbre;
};


/**
 * Classe Liste
 */
class Liste
{
private:
    Noeud* m_tete;

public:
    Liste();

    void afficher();  // TODO supprimer (3)

    Noeud* tete();

    char* readfile(const std::string& filename, int& taille);
    void inserer_tete(Noeud* n);
    void inserer_tete(char c, int effectif);
    void inserer_les_caracteres(const char* s, int taille);
    Noeud* supprimer_plus_petit();
};


/**
 * Classe Arbre
 */
class Arbre
{
private:
    Noeud* m_racine;
    std::string m_codes[256];

public:
    Arbre();
    Arbre(const std::string& filename);

    void afficher(const std::string& type = "");  // TODO supprimer (4)
    void afficher_noeuds(Noeud* n, int profondeur);  // (5)

    Noeud* racine();

    Noeud* construire_arbre(Liste& L);
    void codage();
    std::string* codage(const char* s, int N, double& taux_compression);  // TODO string& ??
    char* compresse(const std::string& texte);  // TODO char* ?? taille du tableau ??
};

#endif
