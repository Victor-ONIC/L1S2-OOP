#include "Carte.h"
#include "Liste.h"

#include <cassert>

void aff_tableau(Liste *T, int N) {
    for (int i = 0; i < N; i++) {
        std::cout << '\n';
        T[i].afficher();
        std::cout << '\n';
    }
}

int main() {

    Liste Jeu(true);  // Créer un jeu de cartes plein.

    Jeu.melanger();

    // Créer un tableau de jeux de cartes.
    // Chaque jeu correspond à un joueur dans la partie.
    constexpr int nb_joueurs = 2;
    Liste *Joueurs = Jeu.distribuer(nb_joueurs);

    aff_tableau(Joueurs, nb_joueurs);  // afficher les jeux après distribution.

    int winner = -1;
    int tour = 0;
    while(winner == -1) {
        std::cout << "Tour " << tour << '\n';
        
        Liste tas;
        int plus_grande_valeur = 0;
        int levee = -1;

        // Retourner
        for (int i = 0; i < nb_joueurs; i++) {
            if (Joueurs[i].get_head() == nullptr) continue;

            int valeur = Joueurs[i].get_head()->get_valeur();
            int couleur = Joueurs[i].get_head()->get_couleur();

            if (valeur > plus_grande_valeur) {
                plus_grande_valeur = valeur;
                levee = i;
            }

            tas.ajouter_fin(valeur, couleur);
        }

        // Bataille ?
        bool is_bataille = false;
        bool bataille[nb_joueurs] = {};
        int check = 0;
        for (int i = 0; i < nb_joueurs; i++) {
            int valeur = Joueurs[i].get_head()->get_valeur();
            if (valeur == plus_grande_valeur) {
                check++;
            }
        }
        if (check > 1) {
            is_bataille = true;
        }

        // Bataille
        int nb_batailles = 0;
        while (is_bataille) {
            nb_batailles++;
            is_bataille = false;

            // Bataille entre qui ?
            for (int i = 0; i < nb_joueurs; i++) {
                int valeur = Joueurs[i].get_head()->get_valeur();
                if (valeur == plus_grande_valeur) {
                    bataille[i] = true;
                }
            }

            for (int i = 0; i < nb_joueurs; i++) {
                Joueurs[i].remove();
            }

            // Piocher deux cartes face cachée.
            for (int i = 0; i < nb_joueurs; i++) {
                if (bataille[i]) {
                    int valeur = Joueurs[i].get_head()->get_valeur();
                    int couleur = Joueurs[i].get_head()->get_couleur();
                    tas.ajouter_fin(valeur, couleur);
                    Joueurs[i].remove();
                }
            }

            // Qui des participants de la bataille gagnera ?
            plus_grande_valeur = 0;
            for (int i = 0; i < nb_joueurs; i++) {
                if (bataille[i]) {
                    if (Joueurs[i].get_head() == nullptr) continue;

                    int valeur = Joueurs[i].get_head()->get_valeur();
                    int couleur = Joueurs[i].get_head()->get_couleur();

                    if (valeur > plus_grande_valeur) {
                        plus_grande_valeur = valeur;
                        levee = i;
                    }

                    tas.ajouter_fin(valeur, couleur);
                }
            }

            // Une deuxième bataille ?
            int check = 0;
            for (int i = 0; i < nb_joueurs; i++) {
                if (bataille[i]) {
                    int valeur = Joueurs[i].get_head()->get_valeur();
                    if (valeur == plus_grande_valeur) {
                        check++;
                    }
                }
            }
            if (check > 1) {
                is_bataille = true;

                for (int i = 0; i < nb_joueurs; i++) {
                    bataille[i] = false;
                }
            }

        }

        // Levée
        // Transfert toutes les cartes de 'tas' au joueurs marqué avec 'levee'.
        Carte *p = tas.get_head();
        while (p != nullptr) {
            int valeur = p->get_valeur();
            int couleur = p->get_couleur();
            Joueurs[levee].ajouter_fin(valeur, couleur);
            p = p->get_next();
        }

        // Supprimer
        if (nb_batailles == 0) {
            for (int i = 0; i < nb_joueurs; i++) {
                Joueurs[i].remove();
            }
        }
        else {
            for (int i = 0; i < nb_joueurs; i++) {
                if (bataille[i]) {
                    Joueurs[i].remove();
                }
            }
        }
        
        // Win condition
        for (int i = 0; i < nb_joueurs; i++) {
            int taille = 0;
            Carte *p = Joueurs[i].get_head();
            while (p != nullptr) {
                p = p->get_next();
                taille++;
            }
            if (taille == 52) {
                winner = i;
            }
        }

        tour++;
    }

    aff_tableau(Joueurs, nb_joueurs);

    delete[] Joueurs;
    return 0;
}
