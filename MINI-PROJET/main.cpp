#include <iostream>

#include "Compression.hpp"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Compression - Erreur: nombre de paramètres incorrect.\n";
        return 1;
    }

    std::string flag = argv[1];
    if (flag != "-c" && flag != "-d")
    {
        std::cerr << "Compression - Erreur: \"" << argv[1] << "\" paramètre inconnu.\n";
        return 1;
    }

    if (flag == "-c")
    {
        Arbre A("texte.txt");

        A.afficher("tout");
        std::cout << std::endl;

        A.codage();
        A.afficher("codes");

        double a = 0;
        std::string* code = A.codage("fffeeaefdfecbfffffbdd", 22, a);
        std::cout << *code << std::endl;
        std::cout << "Taux: " << a << '%' << std::endl;

        char* T = A.compresse(*code);

        return 0;
    }
    
    return 0;
}
