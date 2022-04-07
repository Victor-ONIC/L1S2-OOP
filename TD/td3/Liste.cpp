#include "Liste.h"

Liste::Liste() : head(nullptr) {}

// Liste::Liste(int *T, int N) : head(nullptr) {
//     if (N == 0) return;
//     for (int i = 0; i < N; i++) {
//         ajouter_fin(T[i]);
//     }
// }

Liste::Liste(int *T, int N) : head(nullptr) {
    if (N == 0) return;
    head = new Maillon(T[0]);
    Maillon *tmp = head;
    for (int i = 1; i < N; i++) {
        tmp->next = new Maillon(T[i]);
        tmp = tmp->next;
    } 
}

// Liste::Liste(const Liste &L) : head(nullptr) {
//     Maillon *p = L.head;
//     while (p != nullptr) {
//         ajouter_fin(p->info);
//         p = p->next;
//     }
// }

Liste::Liste(const Liste &L) {
    if (L.head == nullptr) {
        head = nullptr;
        return;
    }
    head = new Maillon(L.head->info, nullptr);
    Maillon *m1 = head, *m2 = L.head->next;
    while (m2 != nullptr) {
        m1->next = new Maillon(m2->info, nullptr);
        m1 = m1->next;
        m2 = m2->next;
    }
}

// Liste::~Liste() {
//     Maillon *actuel = head;
//     while (actuel != nullptr) {
//         Maillon *prochain = actuel->next;
//         delete actuel;
//         actuel = prochain;
//     }
// }

Liste::~Liste() {
    Maillon *tmp = nullptr;
    while (head != nullptr) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

Maillon* Liste::get_head() { return head; }

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

void Liste::afficher_rec() { afficher_rec(head); }
void Liste::afficher_rec(Maillon *m) {
    if (m == nullptr) return;
    std::cout << m->info << ' ';
    afficher_rec(m->next);
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
bool Liste::chercher(int valeur) {
    for (Maillon *m = head; m != nullptr; m = m->next) if (m->info == valeur) return true;
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

// void Liste::supprimer(int valeur) {
//     if (head->info == valeur) {
//         Maillon *temp = head;
//         head = head->next;
//         delete temp;
//         return;
//     }

//     Maillon *p = head->next, *pre = head;
//     while (p != nullptr) {
//         if (p->info == valeur) {
//             pre->next = p->next;
//             delete p;
//             return;
//         }
//         pre = p;
//         p = p->next;
//     }
// }

void Liste::supprimer(int valeur) {
    Maillon *tmp = head, *pr = nullptr;
    while(tmp != nullptr && tmp->info != valeur) {
        pr = tmp;
        tmp = tmp->next;
    }
    if (tmp != nullptr) {
        if (pr == nullptr) {
            head = head->next;
        }
        else {
            pr->next = tmp->next;
        }
        delete tmp;
    }
    
} 

// void Liste::supprimer_tout(int valeur) {
//     while (head->info == valeur) {
//         Maillon *temp = head;
//         head = head->next;
//         delete temp;
//     }
    
//     Maillon *p = head->next, *pre = head;
//     while (p != nullptr) {
//         if (p->info == valeur) {
//             pre->next = p->next;
//             delete p;
//             p = pre->next;
//             continue;
//         }
//         pre = p;
//         p = p->next;
//     }
// }

void Liste::supprimer_tout(int valeur) {
    Maillon *tmp = head, *pr = nullptr;
    while (tmp != nullptr) {
        if (tmp->info == valeur) {
            if (pr == nullptr) {
                head = head->next;
                delete tmp;
                tmp = head;
            }
            else {
                pr->next = tmp->next;
                delete tmp;
                tmp = pr->next;
            }
        }
        else {
            pr = tmp;
            tmp = tmp->next;
        }
    }
}
