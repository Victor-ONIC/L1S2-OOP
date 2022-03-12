#include "Liste.h"

Liste::Liste() : head(nullptr) {}

Liste::Liste(int *T, int N) : head(nullptr) {
    for (int i = 0; i < N; i++) {
        ajouter_fin(T[i]);
    }
}

Liste::Liste(const Liste &L) : head(nullptr) {
    Maillon *p = L.head;
    while (p != nullptr) {
        ajouter_fin(p->info);
        p = p->next;
    }
}

Liste::~Liste() {
    Maillon *actuel = head;
    while (actuel != nullptr) {
        Maillon *prochain = actuel->next;
        delete actuel;
        actuel = prochain;
    }
    head = nullptr;
}

Maillon *Liste::get_head() { return head; }

void Liste::afficher(bool flag) {
    Maillon *p = head;
    if (head == nullptr) {
        std::cout << "\nListe vide.\n";
    }
    else {
        if (flag) {
            std::cout << "\nListe:\n";
            while (p != nullptr) {
                std::cout << p->info << " - " << p << '\n';
                p = p->next;
            }
        }
        else {
            std::cout << "\nListe: ";
            while (p != nullptr) {
                std::cout << p->info << ' ';
                p = p->next;
            }
            std::cout << '\n';
        }
    }
}

void Liste::afficher_inverse(Maillon *m) {
    if (m == nullptr) return;
    afficher_inverse(m->next);
    std::cout << m->info << ' ';
}

void Liste::ajouter_fin(int valeur) {
    Maillon *p = head, *pre = nullptr;
    while (p != nullptr) {
        pre = p;
        p = p->next;
    }
    if (pre == nullptr) {
        head = new Maillon(valeur);
    }
    else {
        pre->next = new Maillon(valeur);
    }
}

int Liste::cardinal() {
    int n = 0;
    Maillon *p = head;
    while (p != nullptr) {
        p = p->next;
        n++;
    }
    return n;
}

bool Liste::chercher(int valeur) {
    Maillon *p = head;
    while (p != nullptr) {
        if (p->info == valeur) return true;
        p = p->next;
    }
    return false;
}

bool Liste::chercher2(int valeur) {
    Maillon *p = head;
    while (p != nullptr) {
        if (p->info > valeur) return false;
        if (p->info == valeur) return true;
        p = p->next;
    }
    return false;
}

int Liste::nb_occurences(int valeur) {
    int n = 0;
    Maillon *p = head;
    while (p != nullptr) {
        if (p->info == valeur) n++;
        p = p->next;
    }
    return n;
}

void Liste::supprimer(int valeur) {
    if (head->info == valeur) {
        Maillon *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Maillon *p = head->next, *pre = head;
    while (p != nullptr) {
        if (p->info == valeur) {
            pre->next = p->next;
            delete p;
            return;
        }
        pre = p;
        p = p->next;
    }
}

void Liste::supprimer_tout(int valeur) {
    while (head->info == valeur) {
        Maillon *temp = head;
        head = head->next;
        delete temp;
    }
    
    Maillon *p = head->next, *pre = head;
    while (p != nullptr) {
        if (p->info == valeur) {
            pre->next = p->next;
            delete p;
            p = pre->next;
            continue;
        }
        pre = p;
        p = p->next;
    }
}
