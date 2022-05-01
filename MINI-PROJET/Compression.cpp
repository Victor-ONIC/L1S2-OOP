#include "Compression.hpp"

/**
 * Classe Noeud
 */

/// Constructeur par défaut.
Noeud::Noeud()
{
    m_char = '\0';
    m_effectif = 0;
    m_suiv = NULL;
    m_fg = NULL;
    m_fd = NULL;
}

/// Constructeur avec un caractère
Noeud::Noeud(char c)
{
    m_char = c;
    m_effectif = 0;
    m_suiv = NULL;
    m_fg = NULL;
    m_fd = NULL;
}

/// Constructeur avec valeurs.
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

void Noeud::afficher()                                                          //
{
    char c;
    if (m_char == '\0') c = '#';
    else c = m_char;
    std::cout << "char: " << c << " nb: " << m_effectif << std::endl;
}

/// Remplir l'attribut 'm_codes' de la classe Arbre en parcourant chaque noeud.
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

/// Ajoute le caractère du noeud dans le fichier de sauvegarde de l'arbre.
void Noeud::ecrire_noeud(std::ofstream& of)
{
    char c;
    if (m_char == '\0')
    {
        c = '|';
    }
    else
    {
        c = m_char;
    }
    of << c;

    if (m_fg != NULL)
    {
        m_fg->ecrire_noeud(of);
    }

    if (m_fd != NULL)
    {
        m_fd->ecrire_noeud(of);
    }
}

/// Crée un noeud avec le string sauvegardé lors de la compression.
void Noeud::inserer(const std::string& s, size_t& ind)
{
    if (ind == s.length())
    {
        return;
    }

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


/**
 * Classe Liste
 */

/// Constructeur par défaut.
Liste::Liste()
{
    m_tete = NULL;
}

void Liste::afficher()                                              //
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

// q.0
/// Lire le contenu d'un fichier et le mettre dans un tableau de char.
const char* Liste::readfile(const std::string& filename, int& taille)
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

    return s;
}

// q.1
/// Ajoute un noeud en début de liste.
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

// q.1
/// Ajoute un noeud en début de liste.
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

// q.1
/// Ajoute un noeud à la liste pour chaque caractère présent dans 's'.
void Liste::inserer_les_caracteres(const char* s, int N)
{
    int T[256] = {0};

    for (int i = 0; i < N; i++)
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

// q.2
/// Retire (différent de supprime) le noeud avec le plus petit effectif.
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

/// Constructeur par défaut.
Arbre::Arbre()
{
    m_racine = NULL;
}

// q.4
/// Constructeur avec nom de fichier.
Arbre::Arbre(const std::string& filename)
{
    m_racine = NULL;

    Liste L;
    int N = 0;
    const char* contenu = L.readfile(filename, N);

    if (contenu != NULL)
    {
        L.inserer_les_caracteres(contenu, N);
        m_racine = construire_arbre(L);
    }
}

void Arbre::afficher(const std::string& type)                               //
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

void Arbre::afficher_noeuds(Noeud* n, int profondeur)                   //
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

/// Obtenir la racine de l'arbre.
Noeud* Arbre::racine()
{
    return m_racine;
}

/// Définir la racine de l'arbre.
void Arbre::set_racine(Noeud* n)
{
    m_racine = n;
}

// q.3
/// Génère l'arbre de Huffman avec les noeuds de la liste 'L'.
Noeud* Arbre::construire_arbre(Liste& L)
{
    while (L.m_tete->m_suiv != NULL)
    {
        Noeud* min_1 = L.supprimer_plus_petit();
        Noeud* min_2 = L.supprimer_plus_petit();
        int eff = min_1->m_effectif + min_2->m_effectif;

        Noeud* nouveau = new Noeud(eff, min_2, min_1);

        L.inserer_tete(nouveau);
    }
    Noeud* n = L.m_tete;
    return n;
}

// q.5
/// Remplis l'attribut 'm_codes' en parcourant l'arbre de Huffman.
void Arbre::codage()
{
    char code[20] = {0};
    int size = 0;
    if (m_racine != NULL)
    {
        m_racine->visiter(code, size, m_codes);
    }
}

//q.6
/// Crée un string contenant le texte codé.
const std::string* Arbre::codage(const char* s, int N, double& taux_compression)
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

// q. Question 6 ou q.7
/// Crée un tableau de char contenant les 1 et 0 du string 'texte'.
const char* Arbre::compresser(const std::string* texte)  // TODO finir
{
    char* T = new char[texte->length() / 8 + 1];

    char c = 0;
    int j = 0;
    size_t i = 0;
    for (; i < texte->length(); i++)
    {
        if (i != 0 && i % 8 == 0)  // Il faut créer un nouveau char.
        {
            T[j] = c;
            j++;
            c = 0;
        }

        if ((*texte)[i] == '1')
        {
            c |= 1 << (7 - (i % 8));
        }
    }

    if (i % 8 != 0)
    {
        size_t max = 0;
        int plus_grand_code = -1;
        for (int i = 0; i < 256; i++)
        {
            if (m_codes[i].length() > max)
            {
                max = m_codes[i].length();
                plus_grand_code = i;
            }
        }

        std::string val = m_codes[plus_grand_code];
        int compteur = 0;
        while (i % 8 != 0)
        {
            if (val[compteur] == '1')
            {
                c |= 1 << (7 - (i % 8));
            }
            compteur++;
            i++;
        }

        T[j] = c;
    }

    return T;
}

/// Sauvegarde l'arbre en une chaine de caractères dans un fichier.
void Arbre::ecrire_arbre(const std::string& filename)
{
    std::ofstream of(filename);
    if (m_racine != NULL)
    {
        m_racine->ecrire_noeud(of);
    }
}

/// Crée un arbre à partir de la chaîne de caractère sauvegardée lors de la compression.
void Arbre::lire(const std::string& s)
{
    m_racine = new Noeud(s[0]);

    size_t ind = 0;
    m_racine->inserer(s, ind);
}

/// Transforme le binaire en un texte de '0' et '1'.
const std::string* Arbre::decompresser(const char* texte, int N)
{
    std::string* s = new std::string;

    char c = 0;
    for (int i = 0; i < N; i++)
    {
        c = texte[i];
        for (int j = 0; j < 8; j++)
        {
            int val = (c >> (7 - j)) & 1;
            if (val == 1)
            {
                s->push_back('1');
            }
            else
            {
                s->push_back('0');
            }
        }
    }

    return s;
}

// Transforme le string de '0' et de '1' en texte selon l'arbre de Huffmann.
const std::string* Arbre::decodage(const std::string* code)
{
    std::string* s = new std::string;

    Noeud* parcours = m_racine;
    
    size_t indice = 0;
    size_t size = code->length();
    while (indice != size)  // Tant qu'on est pas arrivé à la fin du texte codé.....
    {
        while (parcours->m_fg != NULL && parcours->m_fd != NULL && indice != size)  // Tant qu'on est pas arrivé à une feuille de l'arbre de Huffmann...
        {
            if ((*code)[indice] == '0')
            {
                parcours = parcours->m_fg;
                indice++;
            }
            else
            {
                parcours = parcours->m_fd;
                indice++;
            }
        }

        if (parcours->m_fg == NULL)
        {
            s->push_back(parcours->m_char);
            parcours = m_racine;
        }
    }

    return s;
}
