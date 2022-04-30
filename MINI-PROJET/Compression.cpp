#include "Compression.hpp"

/**
 * Classe Noeud
 */
Noeud::Noeud()
{
    m_char = '\0';
    m_effectif = 0;
    m_suiv = NULL;
    m_fg = NULL;
    m_fd = NULL;
}

Noeud::Noeud(char c, int effectif)
{
    m_char = c;
    m_effectif = effectif;
    m_suiv = NULL;
    m_fg = NULL;
    m_fd = NULL;
}

/// Constructeur d'un noeud de liste.
Noeud::Noeud(char c, int effectif, Noeud* suivant)
{
    m_char = c;
    m_effectif = effectif;
    m_suiv = suivant;
    m_fg = NULL;
    m_fd = NULL;
}

/// Constructeur d'un noeud d'arbre.
Noeud::Noeud(int effectif, Noeud* fg, Noeud* fd)
{
    m_char = '\0';
    m_effectif = effectif;
    m_suiv = NULL;
    m_fg = fg;
    m_fd = fd;
}

void Noeud::afficher()
{
    char c;
    if (m_char == '\0') c = '#';
    else c = m_char;
    std::cout << "char: " << c << " nb: " << m_effectif << std::endl;
}

void Noeud::visiter(const char* T, int taille, std::string* codes)
{
    char codeg[20] = {0};
    for (int i = 0; i < taille; i++)
    {
        codeg[i] = T[i];
    }

    char coded[20] = {0};
    for (int i = 0; i < taille; i++)
    {
        coded[i] = T[i];
    }

    if (m_fg == NULL && m_fd == NULL)
    {
        codes[(int)m_char] = codeg;
        return;
    }

    codeg[taille] = '0';
    m_fg->visiter(codeg, taille + 1, codes);

    coded[taille] = '1';
    m_fd->visiter(coded, taille + 1, codes);
}


/**
 * Classe Liste
 */
Liste::Liste()
{
    m_tete = NULL;
}

void Liste::afficher()
{
    if (m_tete == NULL) std::cout << "Liste vide.\n";

    Noeud* p = m_tete;
    while (p != NULL)
    {
        p->afficher();
        std::cout << '\n';
        p = p->m_suiv;
    }
    std::cout << std::endl;
}

Noeud* Liste::tete()
{
    return m_tete;
}

char* Liste::readfile(const std::string& filename, int& taille)
{
    std::ifstream fichier(filename);
    if (fichier.fail())
    {
        return NULL;
    }
    fichier.seekg(0, std::ios::end);
    taille = (int)fichier.tellg();
    char* s = new char[taille];
    fichier.seekg(0, std::ios::beg);
    fichier.read(s, taille);
    fichier.close();
    return s;
}

void Liste::inserer_tete(Noeud* n)
{
    if (m_tete == NULL)
    {
        m_tete = n;
    }
    else
    {
        n->m_suiv = m_tete;
        m_tete = n;
    }
}

void Liste::inserer_tete(char c, int effectif)
{
    if (m_tete == NULL)
    {
        m_tete = new Noeud(c, effectif);
    }
    else
    {
        Noeud* n = new Noeud(c, effectif, m_tete);
        m_tete = n;
    }
}

void Liste::inserer_les_caracteres(const char* s, int taille)
{
    int T[256] = {0};

    for (int i = 0; i < taille; i++)
    {
        T[(int)s[i]]++;
    }

    for (int i = 0; i < 256; i++)
    {
        if (T[i] > 0)
        {
            inserer_tete((char)i, T[i]);
        }
    }
}

Noeud* Liste::supprimer_plus_petit()
{
    if (m_tete == NULL)
    {
        return NULL;
    }

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


/**
 * Classe Arbre
 */
Arbre::Arbre()
{
    m_racine = NULL;
}

Arbre::Arbre(const std::string& filename)
{
    m_racine = NULL;

    Liste L;
    int N = 0;
    char* contenu = L.readfile(filename, N);

    if (contenu != NULL)
    {
        L.inserer_les_caracteres(contenu, N);

        L.afficher();

        m_racine = construire_arbre(L);
    }
}

void Arbre::afficher(const std::string& type)
{
    if (m_racine == NULL) 
    {
        std::cout << "Arbre vide.\n";
        return;
    }

    if (type == "racine")
    {
        std::cout << "Racine: " << m_racine->m_effectif << std::endl;
    }
    
    if (type == "codes")
    {
        for (int i = 0; i < 256; i++)
        {
            if (m_codes[i] != "")
            {
                std::cout << "\nCode de " << (char)i << '(' << i << ')' << ": " << m_codes[i] << std::endl;
            }
            else
            {
                std::cout << i << 'X';
            }
        }
        std::cout << std::endl;
    }

    if (type == "tout")
    {
        afficher_noeuds(m_racine, 0);
    }
}

void Arbre::afficher_noeuds(Noeud* n, int profondeur)
{
    std::cout << "Noeud: profondeur " << profondeur << " ";
    if (n == NULL) 
    {
        std::cout << "NULL.\n";
        return;
    }
    else n->afficher();

    afficher_noeuds(n->m_fg, profondeur + 1);
    afficher_noeuds(n->m_fd, profondeur + 1);
}

Noeud* Arbre::racine()
{
    return m_racine;
}

Noeud* Arbre::construire_arbre(Liste& L)
{
    while (L.tete()->m_suiv != NULL)
    {
        Noeud* min_1 = L.supprimer_plus_petit();
        Noeud* min_2 = L.supprimer_plus_petit();
        int eff = min_1->m_effectif + min_2->m_effectif;

        Noeud* nouveau = new Noeud(eff, min_2, min_1);

        L.inserer_tete(nouveau);
        std::cout << "Etape suivante:\n";
        L.afficher();
    }
    Noeud* n = L.tete();
    return n;
}

void Arbre::codage()
{
    char code[20] = {0};
    int size = 0;
    if (m_racine != NULL)
    {
        m_racine->visiter(code, size, m_codes);
    }
}

std::string* Arbre::codage(const char* s, int N, double& taux_compression)
{
    std::string* code = new std::string;
    for (int i = 0; i < N; i++)
    {
        code->append(m_codes[(int)s[i]]);
    }

    double taille_s = N * 8;
    double taille_code = code->length();

    taux_compression = ((taille_s - taille_code) / taille_s) * 100;

    return code;
}

char* Arbre::compresse(const std::string& texte)
{
    char* T = new char[texte.length()]{0};

    std::bitset<8> ensemble(0);
    
    size_t i = 0;
    int j = 0;
    for (; i < texte.length(); i++)
    {
        if (i != 0 && i % 8 == 0)
        {
            char c = ensemble.to_ulong();
            T[j] = c;
            j++;

            std::cout << ensemble;
            ensemble.reset();
        }
        bool valeur = texte[i] == '1' ? 1 : 0;
        ensemble[7 - i % 8] = valeur;
    }

    if (i % 8 != 0)
    {
        while (i % 8 != 0)
        {
            ensemble[7 - i % 8] = 0;
            i++;
        }
        char c = ensemble.to_ulong();
        T[++j] = c;

        std::cout << ensemble;
    }

    std::cout << std::endl;
    return T;
}
