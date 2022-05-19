/**
 * @file    Arbre.hpp
 * @author  ONIC Victor (victor.onic@outlook.fr)
 * @date    19-05-2022
 * 
 * Fichier d'entête de la classe Arbre.
 */

#ifndef ARBRE_H
#define ARBRE_H

#include "Liste.hpp"

///  Classe Arbre
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

#endif // ARBRE_H
