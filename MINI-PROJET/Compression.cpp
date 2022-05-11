/**
 * @file    Compression.cpp
 * @author  ONIC Victor (victor.onic@outlook.fr)
 * @date    01-05-2022
 * 
 * Ce fichier contient l'entièreté de l'implémentation des classes
 * Noeud, Liste et Arbre nécessaire au fonctionnement du programme
 * Compression.
 */

#include "Compression.hpp"



/**
 *  Classe Noeud
 */

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
    m_char = '\0';
    m_effectif = effectif;
    m_suiv = NULL;
    m_fg = fg;
    m_fd = fd;
}

///  Destructeur.
Noeud::~Noeud()
{
    if (m_fg != NULL)
    {
        delete m_fg;
    }

    if (m_fd != NULL)
    {
        delete m_fd;
    }
}

///  Remplir l'attribut 'm_codes' de la classe Arbre en parcourant chaque noeud.
void Noeud::visiter(const char* T, int taille, std::string* codes)
{
    //  Tableau à passer au noeud fils de gauche.
    char codeg[20] = {0};
    for (int i = 0; i < taille; i++)
    {
        codeg[i] = T[i];
    }

    //  Tableau à passer au noeud fils de droite.
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

    //  Le caractère '0' est ajouté en descendant l'arbre à gauche.
    codeg[taille] = '0';
    m_fg->visiter(codeg, taille + 1, codes);

    //  Et le caractère '1' en passant à droite.
    coded[taille] = '1';
    m_fd->visiter(coded, taille + 1, codes);

    //  Par exemple: racine->gauche->gauche->droite donne "001".
}

///  Ajoute le caractère du noeud dans le fichier de sauvegarde de l'arbre.
void Noeud::ecrire_noeud(std::ofstream& of)
{
    char c;
    //  Les noeuds qui ne sont pas des feuilles ont '\0' comme caractère.
    //  Ils seront codés avec '|' dans le fichier de sauvegarde.
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

///  Crée un noeud avec le string sauvegardé lors de la compression.
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
 *  Classe Liste
 */

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
    taille = (int)fichier.tellg();

    char* s = new char[taille];
    fichier.seekg(0, std::ios::beg);
    fichier.read(s, taille);

    return s;
}

//  q.1
///  Ajoute un noeud en début de liste.
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

//  q.1
///  Ajoute un noeud en début de liste.
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

//  q.1
///  Ajoute un noeud à la liste pour chaque caractère présent dans 's'.
void Liste::inserer_les_caracteres(const char* s, int N)
{
    int T[256] = {0};

    //  Compter le nombre d'occurences de chaque caractères.
    //  Ne fonctionne que pour les caractères ASCII.
    for (int i = 0; i < N; i++)
    {
        T[(int)s[i]]++;
    }

    //  Si le caractère est présent au moins une fois, l'ajouter à la liste.
    for (int i = 0; i < 256; i++)
    {
        if (T[i] > 0)
        {
            inserer_tete((char)i, T[i]);
        }
    }
}

//  q.2
///  Retire le noeud avec le plus petit effectif et le renvoie.
Noeud* Liste::supprimer_plus_petit()
{
    if (m_tete == NULL)
    {
        return NULL;
    }

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



/**
 *  Classe Arbre
 */

///  Constructeur par défaut.
Arbre::Arbre()
{
    m_racine = NULL;
}

///  Destructeur.
Arbre::~Arbre()
{
    if (m_racine != NULL)
    {
        delete m_racine;
    }
}

//  q.4
///  Constructeur avec un nom de fichier.
///  Inutilisée
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

    delete[] contenu;
}

///  Obtenir la racine de l'arbre.
Noeud* Arbre::racine()
{
    return m_racine;
}

///  Définir la racine de l'arbre.
void Arbre::set_racine(Noeud* n)
{
    m_racine = n;
}

//  q.3
///  Génère l'arbre de Huffman avec les noeuds de la liste 'L'.
Noeud* Arbre::construire_arbre(Liste& L)
{
    while (L.m_tete->m_suiv != NULL)
    {
        //  Tant qu'il reste plus d'un seul noeud dans la liste....
        Noeud* min_1 = L.supprimer_plus_petit();
        Noeud* min_2 = L.supprimer_plus_petit();
        int eff = min_1->m_effectif + min_2->m_effectif;

        //  Création d'un noeud avec comme fils les deux noeuds avec les
        //  effectifs les plus petits de la liste.
        //  Son effectif à lui est la somme des effectifs de ses fils.
        //  Son caractère est '\0'.
        Noeud* nouveau = new Noeud(eff, min_2, min_1);

        //  On ajoute ce nouveau noeud en tête de la liste.
        L.inserer_tete(nouveau);
    }
    Noeud* n = L.m_tete;
    return n;
}

//  q.5
///  Remplis l'attribut 'm_codes' en parcourant l'arbre de Huffman.
void Arbre::codage()
{
    char code[20] = {0};
    int size = 0;
    if (m_racine != NULL)
    {
        m_racine->visiter(code, size, m_codes);
    }
}

//  q.6
///  Crée un string contenant le texte codé.
const std::string* Arbre::codage(const char* s, int N, double& taux_compression)
{
    //  'code' contiendra tout le texte de 's' codé.
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

//  q. Question 6 ou q.7
///  Crée un tableau de char contenant les 1 et 0 du string 'texte'.
const char* Arbre::compresser(const std::string* texte)
{
    //  Tous les caractères de 'texte' (des '0' et des '1') iront par paquets
    //  de 8 dans T. Il faut un emplacement supplémentaire au cas-où le
    //  nombre de caractères n'est pas divisible par 8.
    char* T = new char[texte->length() / 8 + 1];

    //  Les bits de 'c' vont copier la chaine de caractères 'texte'.
    //  exemple: les 8 premiers caractères de 'texte' sont 00101101.
    //  alors, c = 0b00101101, soit 45.
    //  Cela jusqu'à être arrivé à la fin de 'texte'.
    char c = 0b00000000;

    int j = 0;
    size_t i = 0;
    for (; i < texte->length(); i++)
    {
        //  Tous les 8 caractères, il faut ajouter 'c' dans 'T' et "vider" 'c'
        //  pour continuer à lire 'texte'.
        if (i != 0 && i % 8 == 0)
        {
            T[j] = c;
            j++;
            c = 0;
        }

        if ((*texte)[i] == '1')
        {
            //  S'il y a un '1' dans 'texte', on le rajoute dans 'c' à la
            //  bonne place.
            //  i=0: mettre le 7e bit de 'c' à 1,
            //  i=1: mettre le 6e bit de 'c' à 1,
            //  ...
            //  i=8: mettre le 7e bit de 'c' à 1 (ce n'est plus le même 'c'!)
            //  ...
            //  
            //  On utilise l'opération OU sur les bits de 'c' un à un.
            //  exemple:
            //      11000000 => c
            //   OU 00001000 => valeur, ici 1 (00000001) avec ses bits décalés vers la gauche 3 fois (1 << 3).
            //      --------
            //    = 11001000 => résultat
            c |= 1 << (7 - (i % 8));
        }
    }

    //  Si le nombre de caractères dans 'texte' n'est pas divisible par 8,
    //  alors remplir les derniers bits avec une partie du plus long codage.
    //
    //  BUG
    //  À savoir que si le texte à compresser est de petite taille, cette méthode
    //  pourra quand même rajouter un caractère non désiré lors de la décompression.
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
        size_t compteur = 0;
        while (i % 8 != 0)
        {
            //  Si jamais il y a encore des bits à remplir alors que tout le
            //  code le plus long ait été ajouté, on réitère.
            //  Cela signifie qu'il y aura un caractère non désiré à la décompression.
            if (compteur == val.size())
            {
                compteur = 0;
            }

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

///  Sauvegarde l'arbre en une chaine de caractères dans un fichier.
void Arbre::ecrire_arbre(const std::string& filename)
{
    std::ofstream of(filename);
    if (m_racine != NULL)
    {
        m_racine->ecrire_noeud(of);
    }
}

///  Crée un arbre à partir de la chaîne de caractère sauvegardée lors de la compression.
void Arbre::lire(const std::string& s)
{
    m_racine = new Noeud(s[0]);

    size_t ind = 0;
    m_racine->inserer(s, ind);
}

///  Transforme le binaire en un string de '0' et '1'.
const std::string* Arbre::decompresser(const char* texte, int N)
{
    std::string* s = new std::string;

    //  Lire 'texte' char par char et lire chaque bits de chaque char.
    //  Ajouter '0' à 's' si le bit est 0 et '1' si le bit est 1.
    char c = 0;
    for (int i = 0; i < N; i++)
    {
        c = texte[i];
        for (int j = 0; j < 8; j++)
        {
            //  Pour chaque char de 'texte', répéter 8 fois...

            //  Pour lire le nième bit de 'c', on va déplacer le bit tout
            //  à droite (bit de poids faible).
            //  Puis on utilise l'opération ET sur les bits avec le chiffre 1.
            //  exemple:
            //      00110110 => c (lire le 1er bit)       00011011 => c >> 1 (lire le 2e bit)
            //   ET 00000001 => 1                         ET 00000001 => 1
            //      --------                              --------
            //      00000000 => résultat                  00000001 => résultat
            //  Si le résultat est 1 (00000001), alors le nième bit était 1.
            //  Si le résultat est 0 (00000000), alors c'était 0.
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

//  Transforme le string de '0' et de '1' en texte selon l'arbre de Huffmann.
const std::string* Arbre::decodage(const std::string* code)
{
    std::string* s = new std::string;

    Noeud* parcours = m_racine;
    
    size_t indice = 0;
    size_t size = code->length();
    while (indice != size)
    {
        //  Tant qu'on est pas arrivé à la fin du texte codé.....
        while (parcours->m_fg != NULL && parcours->m_fd != NULL && indice != size)
        {
            //  Tant qu'on est pas arrivé à une feuille de l'arbre de Huffmann...
            if ((*code)[indice] == '0')
            {
                //  S'il y a un '0' dans le code du caractère, on descend à
                //  gauche dans l'arbre.
                parcours = parcours->m_fg;
                indice++;
            }
            else
            {
                //  Et à droite s'il y a un '1'.
                parcours = parcours->m_fd;
                indice++;
            }
        }

        //  Vérifier que 'parcours' est bien une feuille de l'arbre, au cas-où
        //  ce serait la châine incomplète de fin de compression.
        if (parcours->m_fg == NULL)
        {
            s->push_back(parcours->m_char);
            parcours = m_racine;
        }

        // Si on parcours l'arbre sans arriver à aucune racine, on ne fait rien.
    }

    return s;
}
