#include "Liste.h"

Liste::Liste(bool plein) : head(nullptr), tail(nullptr) {
    if (plein) {
        for (int couleur = 0; couleur < 4; couleur++) {
            for (int valeur = 2; valeur < 15; valeur++ ) {
                ajouter_fin(valeur, couleur);
            }
        }
    }
}

Liste::~Liste() {
    Carte *tmp = nullptr;
    while (head != nullptr) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

Carte *Liste::get_head() { return head; }

Carte *Liste::get_tail() { return tail; }

void Liste::ajouter_fin(int valeur, int couleur) {
    if (tail == nullptr) {
        head = tail = new Carte(valeur, couleur);
    }
    else {
        tail = tail->next = new Carte(valeur, couleur);
    }
}

void Liste::ajouter_debut(int valeur, int couleur) {
    if (head == nullptr) {
        tail = head = new Carte(valeur, couleur);
    }
    else {
        Carte *p = new Carte(valeur, couleur, head);
        head = p;
    }
}

void Liste::remove() {
    Carte *p = head;
    head = head->next;
    delete p;
}

void Liste::vider() {
    Carte *tmp = nullptr;
    while (head != nullptr) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
}

void Liste::afficher() {
    if (head == nullptr) {
        std::cout << "\nListe vide.\n";
        return;
    }

    const char Valeurs[4][6] = {"As", "Roi", "Dame", "Valet"};
    const char Couleurs[4][8] = {"Trèfle", "Carreau", "Coeur", "Pique"};

    Carte *p = head;
    while (p != nullptr) {

        if (p->valeur > 1 && p->valeur < 11) std::cout << p->valeur;
        else std::cout << Valeurs[14 - p->valeur];

        std::cout << " de ";

        std::cout << Couleurs[p->couleur];
        std::cout << '\n';

        p = p->next;
    }
}

void Liste::tri_croissant_valeur_couleur() {

    Carte *avant = nullptr;
    Carte *p = head;
    if (p == nullptr || p->next == nullptr) return;

    bool tri = false;
    while (!tri) {
        tri = true;
        avant = nullptr;
        p = head;

        while (p != nullptr) {
            Carte *a = p;
            Carte *b = p->next;

            if (b != nullptr && (a->valeur > b->valeur || (a->valeur == b->valeur && a->couleur > b->couleur))) {
                if (avant == nullptr) {
                    a->next = b->next;
                    b->next = a;
                    head = b;
                }
                else {
                    avant->next = b;
                    a->next = b->next;
                    b->next = a;
                }
                tri = false;
            }

            avant = p;
            p = p->next;
        }
    }
}

void Liste::tri_decroissant_couleur_valeur() {

    Carte *avant = nullptr;
    Carte *p = head;
    if (p == nullptr || p->next == nullptr) return;

    bool tri = false;
    while (!tri) {
        tri = true;
        avant = nullptr;
        p = head;

        while (p != nullptr) {
            Carte *a = p;
            Carte *b = p->next;

            if (b != nullptr && (a->couleur < b->couleur || (a->couleur == b->couleur && a->valeur < b->valeur))) {
                if (avant == nullptr) {
                    a->next = b->next;
                    b->next = a;
                    head = b;
                }
                else {
                    avant->next = b;
                    a->next = b->next;
                    b->next = a;
                }
                tri = false;
            }

            avant = p;
            p = p->next;
        }
    }
    
}

void Liste::melanger() {
    Liste J;
    
    Carte *p = nullptr;
    int n = 0;

    for (int i = 0; i < 12; i++) {
        p = head;
        n = 1;
        while (p != nullptr) {
            if (n % 2 == 0) J.ajouter_debut(p->valeur, p->couleur);
            else J.ajouter_fin(p->valeur, p->couleur);
            n++;
            p = p->next;
        }
        vider();
        p = J.head;
        while (p != nullptr) {
            ajouter_fin(p->valeur, p->couleur);
            p = p->next;
        }
        J.vider();
    }

}

Liste *Liste::distribuer(int nb_joueurs) {
    Liste *T = new Liste[nb_joueurs];

    Carte *p = head;
    int n = 0;
    while (p != nullptr) {
        T[n].ajouter_fin(p->valeur, p->couleur);
        p = p->next;
        if (n == (nb_joueurs - 1)) {
            n = 0;
        }
        else {
            n++;
        }
    }

    return T;
}






