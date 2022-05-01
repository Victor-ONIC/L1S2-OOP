#include <iostream>

#include "Compression.hpp"

int main(int argc, char** argv)
{
    // Vérification du bon nombre d'arguments.
    if (argc != 4)
    {
        std::cerr << "Compression - Erreur: nombre de paramètres incorrect.\n";
        return 1;
    }

    // Vérification des bons flags.
    std::string flag = argv[1];
    if (flag != "-c" && flag != "-d")
    {
        std::cerr << "Compression - Erreur: \"" << argv[1] << "\" paramètre inconnu.\n";
        return 1;
    }

    std::string input_file(argv[2]);
    std::string output_file(argv[3]);


    // Compression.
    if (flag == "-c")
    {
        Liste L;
        int N = 0;
        const char* contenu = L.readfile(input_file, N);  // Lire depuis le fichier source.

        if (contenu == NULL)
        {
            std::cerr << "Compression - Erreur: impossible d'ouvrir le fichier " << input_file << ".\n";
            return 1;
        }

        L.inserer_les_caracteres(contenu, N);  // La liste est prête.

        Arbre A;
        Noeud* r = A.construire_arbre(L);
        A.set_racine(r);  // L'arbre est prêt.

        A.codage();  // Initialisation des codes de chaque caractères.
        
        double a = 0;
        const std::string* code = A.codage(contenu, N, a);  // Texte codé "1011010110" par exemple.

        const char* binary = A.compresser(code);  // Texte binaire.

        // Ecrire dans le fichier destination.
        std::ofstream sortie(output_file);
        if (sortie.fail())
        {
            std::cerr << "Compression - Erreur: fichier destination introuvable.\n";
            return 1;
        }

        sortie.write(binary, code->length() / 8 + 1);

        if (!sortie.good())
        {
            std::cerr << "Compression - Une erreur s'est produite.\n";
            return 1;
        }

        // Ecrire l'arbre dans un fichier afin de s'en servir plus tard pour décompresser.
        std::string fn = output_file.append(".arbre");
        A.ecrire_arbre(fn);  

        std::cout << "Compression - Terminé. Taux: " << a << std::endl; 
        return 0;
    }


    // Décompression.
    if (flag == "-d")
    {
        // Lire le fichier contenant l'arbre de Huffmann.
        std::string fn = input_file;
        fn.append(".arbre");
        std::ifstream fichier_arbre(fn);
        if (fichier_arbre.fail())
        {
            std::cerr << "Compression - Erreur: impossible d'ouvrir le fichier " << fn << ".\n";
            return 1;
        }

        fichier_arbre.seekg(0, std::ios::end);
        int taille1 = (int)fichier_arbre.tellg();

        char* s = new char[taille1];
        fichier_arbre.seekg(0, std::ios::beg);
        fichier_arbre.read(s, taille1);
        fichier_arbre.close();
        std::string arbre(s, taille1);
        
        Arbre A;
        A.lire(arbre);
        A.codage();  // L'arbre de Huffmann prêt.

        // Lire le fichier source compressé.
        std::ifstream fichier(input_file);
        if (fichier.fail())
        {
            std::cerr << "Compression - Erreur: impossible d'ouvrir le fichier " << input_file << ".\n";
            return 1;
        }

        fichier.seekg(0, std::ios::end);
        int taille2 = (int)fichier.tellg();

        char* binary = new char[taille2];
        fichier.seekg(0, std::ios::beg);
        fichier.read(binary, taille2);
        fichier.close();

        const std::string* code = A.decompresser(binary, taille2);  // Texte codé "00101011" par exemple.

        const std::string* original = A.decodage(code);  // Texte original.

        // Ecrire le texte dans le fichier destination.
        std::ofstream sortie(output_file);
        if (sortie.fail())
        {
            std::cerr << "Compression - Erreur: fichier destination introuvable.\n";
            return 1;
        }

        sortie.write(original->c_str(), original->length());

        if (!sortie.good())
        {
            std::cerr << "Compression - Une erreur s'est produite.\n";
            return 1;
        }

        std::cout << "Compression - Terminé.\n";
        return 0;
    }


    std::cerr << "Compression - Erreur inconnue.\n";
    return 2;
}

// TODO préciser partout quand est-ce que j'ai dû respecter le sujet.

