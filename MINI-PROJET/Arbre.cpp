/**
 * @file    Arbre.cpp
 * @author  ONIC Victor (victor.onic@outlook.fr)
 * @date    19-05-2022
 * 
 * Fichier d'implémentation de la classe Arbre.
 */

#include "Arbre.hpp"

///  Constructeur par défaut.
Arbre::Arbre()
{
    m_racine = NULL;
}

///  Destructeur.
Arbre::~Arbre()
{
    if (m_racine != NULL) delete m_racine;
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

        Noeud* nouveau = new Noeud(eff, min_2, min_1);

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
    if (m_racine != NULL) m_racine->visiter(code, size, m_codes);
}

//  q.6
///  Crée un string contenant le texte codé.
const std::string* Arbre::codage(const char* s, int N, double& taux_compression)
{
    //  'code' contiendra tout le texte de 's' codé.
    std::string* code = new std::string;
    for (int i = 0; i < N; i++)
    {
        int char_index = static_cast<int>(s[i]);
        code->append(m_codes[char_index]);
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
    //  Tous les caractères de 'texte' (des '0' et des '1') seront
    //  retranscrit dans T par paquets de 8. 
    //  Il faut un emplacement supplémentaire au cas-où le
    //  nombre de caractères n'est pas divisible par 8.
    char* T = new char[texte->length() / 8 + 1];

    //  Les bits de 'c' vont copier la chaine de caractères 'texte'.
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
            //  S'il y a un '1' dans 'texte', on le retranscrit dans 'c' à la
            //  bonne place.
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
            //  Cela signifie qu'il y aura forcément un caractère non désiré à la décompression !
            if (compteur == val.size()) compteur = 0;

            if (val[compteur] == '1') c |= 1 << (7 - (i % 8));
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
    if (m_racine != NULL) m_racine->ecrire_noeud(of);
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
            //  Pour lire le nième bit de 'c', on va déplacer le bit tout
            //  à droite (bit de poids faible).
            //  Puis on utilise l'opération ET sur les bits avec le chiffre 1.
            int val = (c >> (7 - j)) & 1;

            if (val == 1)   s->push_back('1');
            else            s->push_back('0');
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
            
            if ((*code)[indice] == '0')  //  Si 0, on descend à gauche.
            {
                parcours = parcours->m_fg;
                indice++;
            }
            else  //  Si 1, on descend à droite.
            {
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
