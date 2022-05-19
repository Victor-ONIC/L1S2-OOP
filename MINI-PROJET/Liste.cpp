/**
 * @file    Liste.cpp
 * @author  ONIC Victor (victor.onic@outlook.fr)
 * @date    19-05-2022
 * 
 * Fichier d'implémentation de la classe Liste.
 */

#include "Liste.hpp"

///  Constructeur par défaut.
Liste::Liste()
{
    m_tete = NULL;
}

//  q.0
///  Lire le contenu d'un fichier et le mettre dans un tableau de char.
const char* Liste::readfile(const std::string& filename, int& taille)
{
    //  Création d'un objet de type ifstream (input file stream).
    std::ifstream fichier(filename);
    if (fichier.fail())
    {
        //  Si la construction du flux n'a pas marché, on retourne NULL.
        return NULL;
    }
    fichier.seekg(0, std::ios::end);
    taille = static_cast<int>(fichier.tellg());

    char* s = new char[taille];
    fichier.seekg(0, std::ios::beg);
    fichier.read(s, taille);

    return s;
}

//  q.1
///  Ajoute un noeud en début de liste.
void Liste::inserer_tete(Noeud* n)
{
    if (m_tete == NULL) m_tete = n;
    else
    {
        n->m_suiv = m_tete;
        m_tete = n;
    }
}

//  q.1
///  Ajoute un noeud en début de liste.
void Liste::inserer_tete(char c, int effectif)
{
    if (m_tete == NULL) m_tete = new Noeud(c, effectif);
    else
    {
        Noeud* n = new Noeud(c, effectif, m_tete);
        m_tete = n;
    }
}

//  q.1
///  Ajoute un noeud à la liste pour chaque caractère présent dans 's'.
void Liste::inserer_les_caracteres(const char* s, int N)
{
    int T[256] = {0};

    //  Compter le nombre d'occurences de chaque caractères.
    //  Ne fonctionne que pour les caractères ASCII.
    for (int i = 0; i < N; i++)
    {
        int char_index = static_cast<int>(s[i]);
        T[char_index]++;
    }

    //  Si le caractère est présent au moins une fois, l'ajouter à la liste.
    for (int i = 0; i < 256; i++)
    {
        if (T[i] > 0)
        {
            char caractere = static_cast<char>(i);
            inserer_tete(caractere, T[i]);
        }
    }
}

//  q.2
///  Retire le noeud avec le plus petit effectif et le renvoie.
Noeud* Liste::supprimer_plus_petit()
{
    if (m_tete == NULL) return NULL;

    //  Trouver le noeud avec l'effectif le plus petit.
    int effectif_min = m_tete->m_effectif;
    Noeud* min = m_tete;

    Noeud *p = m_tete;
    while (p != NULL)
    {
        if (p->m_effectif < effectif_min)
        {
            min = p;
            effectif_min = p->m_effectif;
        }
        p = p->m_suiv;
    }

    //  Retirer le noeud de la liste.
    p = m_tete;
    Noeud* prev = NULL;
    while (p != min)
    {
        prev = p;
        p = p->m_suiv;
    }

    if (prev == NULL)
    {
        m_tete = p->m_suiv;
        p->m_suiv = NULL;
    }
    else
    {
        prev->m_suiv = p->m_suiv;
        p->m_suiv = NULL;
    }

    return p;
}
