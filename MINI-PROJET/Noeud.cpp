/**
 * @file    Noeud.cpp
 * @author  ONIC Victor (victor.onic@outlook.fr)
 * @date    19-05-2022
 * 
 * Fichier d'implémentation de la classe Noeud.
 */

#include "Noeud.hpp"

///  Constructeur par défaut.
Noeud::Noeud()
{
    m_char = '\0';
    m_effectif = 0;
    m_suiv = NULL;
    m_fg = NULL;
    m_fd = NULL;
}

///  Constructeur avec un caractère.
Noeud::Noeud(char c)
{
    m_char = c;

    m_effectif = 0;
    m_suiv = NULL;
    m_fg = NULL;
    m_fd = NULL;
}

///  Constructeur avec valeurs.
Noeud::Noeud(char c, int effectif)
{
    m_char = c;
    m_effectif = effectif;

    m_suiv = NULL;
    m_fg = NULL;
    m_fd = NULL;
}

///  Constructeur d'un noeud de liste.
Noeud::Noeud(char c, int effectif, Noeud* suivant)
{
    m_char = c;
    m_effectif = effectif;
    m_suiv = suivant;

    m_fg = NULL;
    m_fd = NULL;
}

///  Constructeur d'un noeud d'arbre.
Noeud::Noeud(int effectif, Noeud* fg, Noeud* fd)
{
    m_effectif = effectif;
    m_fg = fg;
    m_fd = fd;

    m_char = '\0';
    m_suiv = NULL;
}

///  Destructeur.
Noeud::~Noeud()
{
    if (m_fg != NULL) delete m_fg;
    if (m_fd != NULL) delete m_fd;
}

///  Remplir l'attribut 'm_codes' de la classe Arbre en parcourant chaque noeud.
void Noeud::visiter(const char* T, int taille, std::string* codes)
{
    //  Tableau à passer au noeud fils de gauche.
    char codeG[20] = {0};
    for (int i = 0; i < taille; i++) 
    {
        codeG[i] = T[i];
    }

    //  Tableau à passer au noeud fils de droite.
    char codeD[20] = {0};
    for (int i = 0; i < taille; i++) 
    {
        codeD[i] = T[i];
    }

    //  Une fois arrivé à une feuille, on a un codage valide.
    if (m_fg == NULL && m_fd == NULL)
    {
        codes[static_cast<int>(m_char)] = codeG;
        return;
    }

    //  Le caractère '0' est ajouté en descendant l'arbre à gauche.
    codeG[taille] = '0';
    m_fg->visiter(codeG, taille + 1, codes);

    //  Et le caractère '1' en passant à droite.
    codeD[taille] = '1';
    m_fd->visiter(codeD, taille + 1, codes);

    //  Par exemple: racine->gauche->gauche->droite donne "001".
}

///  Ajoute le caractère du noeud dans le fichier de sauvegarde de l'arbre.
void Noeud::ecrire_noeud(std::ofstream& of)
{
    char c;
    //  Les noeuds qui ne sont pas des feuilles ont '\0' comme caractère.
    //  Ils seront codés avec '|' dans le fichier de sauvegarde.
    if (m_char == '\0')  c = '|';
    else                 c = m_char;

    of << c;

    if (m_fg != NULL) m_fg->ecrire_noeud(of);
    if (m_fd != NULL) m_fd->ecrire_noeud(of);
}

///  Crée un noeud avec le string sauvegardé lors de la compression.
void Noeud::inserer(const std::string& s, size_t& ind)
{
    if (ind == s.length()) return;

    m_char = s[ind];

    if (s[ind] == '|')
    {
        m_fg = new Noeud(s[ind + 1]);
        ind = ind + 1;
        m_fg->inserer(s, ind);

        m_fd = new Noeud(s[ind + 1]);
        ind = ind + 1;
        m_fd->inserer(s, ind);
    }
}
