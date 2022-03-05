#include "Collection.h"

Collection::Collection() : nb_pts(0), cap(5 /*100*/) {
    T = new Point[cap];
}

Collection::Collection(Point *Tab, int N) {
    nb_pts = N;
    cap = N * 2;
    // T = Tab; non!
    T = new Point[cap];
    // on ourrait utiliser memcpy().
    // on pourrait utiliser memcpy(T, Tab, sizeof(Point) * N);
    for (int i = 0; i < N; i++) {
        T[i] = Tab[i];
    }
}

Collection::Collection(const Collection &C) : nb_pts(C.nb_pts), cap(C.cap) {
    T = new Point[cap];
    for (int i = 0; i < C.nb_pts; i++) {
        T[i] = C.T[i];
    }
}

Collection::Collection(Collection &A, Collection &B) {
    if (A.cap > B.cap) {
        cap = A.cap;
    }
    else {
        cap = B.cap;
    }

    int j = 0;
    Point *nouveau = new Point[cap];
    for (int i = 0; i < A.nb_pts; i++) {
        nouveau[j] = A.T[i];
        j++;
    }
    for (int i = 0; i < B.nb_pts; i++) {
        if (!(A.present(B.T[i]))) {
            nouveau[j] = B.T[i];
            j++;
        }
    }
    nb_pts = j;
    T = nouveau;
}

Collection::~Collection() {
    delete[] T;

    // Test du destructeur (q.3).
    std::cout << "\n--- Test du destructeur ---";
}

// DEBUG
void Collection::afficher() {
    std::cout << "Collection - taille: " << nb_pts << " cap: " << cap << '\n';
    for (int i = 0; i < nb_pts; i++) {
        T[i].afficher();
        std::cout << '\n';
    }
}
/////////////////////////////////////////

bool Collection::present(Point &p) {
    for (int i = 0; i < nb_pts; i++) {
        if (p.identiques(T[i])) {
            return true;
        }
    }
    return false;
}

bool Collection::ajout(Point &p) {
    if (!(present(p))) {
        T[nb_pts] = p;
        nb_pts++;
        return true;
    }
    return false;
}

bool Collection::supprimer(Point &p) {
    if (present(p)) {
        Point *temp = new Point[cap];
        int j = 0;
        for (int i = 0; i < nb_pts; i++) {
            if (T[i].identiques(p)) {
                continue;
            }
            temp[j] = T[i];
            j++;
        }
        delete[] T;
        T = temp;
        nb_pts--;
        return true;
    }
    return false;
}

void Collection::ajouter_bis(Point &p) {
    if (nb_pts != cap) {
        ajout(p);
    }
    else {
        if (!(present(p))) {
            Point *nouveau = new Point[cap * 2];
            for (int i = 0; i < nb_pts; i++) {
                nouveau[i] = T[i];
            }
            nouveau[nb_pts] = p;
            delete[] T;
            T = nouveau;
            cap = cap * 2;
            nb_pts++;
        }
    }
}

void Collection::ajouter_tab(Point *P, int N) {
    for (int i = 0; i < N; i++) {
        ajouter_bis(P[i]);
    }
}

// Met les points qui sont à la fois dans *this et A dans B.
void Collection::intersection(const Collection &A, Collection &B) {
    for (int i = 0; i < A.nb_pts; i++) {
        if (present(A.T[i])) {
            B.ajouter_bis(A.T[i]);
        }
    }
}

void Collection::pts_remarquables(Point &grand_x, Point &grand_y, Point &petit_x, Point &petit_y, Point &m) {
    Point temp = T[0];
    grand_x = temp, grand_y = temp, petit_x = temp, petit_y = temp;
    for (int i = 1; i < nb_pts; i++) {
        if (T[i].get_x() > grand_x.get_x()) {
            grand_x = T[i];
        }
        else if (T[i].get_y() > grand_y.get_y()) {
            grand_y = T[i];
        }
        else if (T[i].get_x() < petit_x.get_x()) {
            petit_x = T[i];
        }
        else if (T[i].get_y() < petit_y.get_y()) {
            petit_y = T[i];
        }
    }

    double m_x = 0, m_y = 0;
    for (int i = 0; i < nb_pts; i++) {
        m_x += T[i].get_x();
        m_y += T[i].get_y();
    }
    Point milieu(m_x / nb_pts, m_y / nb_pts);
    m = milieu;
}
