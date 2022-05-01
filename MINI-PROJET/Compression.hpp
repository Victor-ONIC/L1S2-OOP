/**
 * @file    Compression.hpp
 * @author  ONIC Victor (victor.onic@outlook.fr)
 * @date    01-05-2022
 * 
 * Fichier header de Compression.cpp.
 */

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <cstddef>
#include <fstream>
#include <string>

/**
 *  Classe Noeud
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



/**
 *  Classe Liste
 */
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



/**
 *  Classe Arbre
 */
class Arbre
{
private:
    Noeud* m_racine;
    std::string m_codes[256];

public:
    Arbre();
    Arbre(const std::string& filename);                                        //  q.4
    ~Arbre();

    Noeud* racine();
    void set_racine(Noeud* n);

    Noeud* construire_arbre(Liste& L);                                         //  q.3
    void codage();                                                             //  q.5
    const std::string* codage(const char* s, int N, double& taux_compression); //  q.6
    const char* compresser(const std::string* texte);                          //  q. Question 6 ou q.7
    void ecrire_arbre(const std::string& filename);
    void lire(const std::string& s);
    const std::string* decompresser(const char* texte, int N);
    const std::string* decodage(const std::string* code);
};

#endif
