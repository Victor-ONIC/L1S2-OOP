#include <iostream>
#include <cmath>
using namespace std;

class vecteur
{
private:
    double x;
    double y;
    double z;

public:
    vecteur(double a = 0, double b = 0, double c = 0);
    void afficher();
    vecteur add(vecteur& a);
    vecteur minus(vecteur& a);
    double produit_scalaire(vecteur& a);
    double norme();
    bool identique(vecteur& C);
};



class collection_vecteurs
{
private:
    vecteur* T;
    int nbv;
    int capacite;

public:
    collection_vecteurs(int cap);
    ~collection_vecteurs();
    bool ajouter(vecteur& c);
    void afficher();
    bool chercher(vecteur& c);
};



class maillon
{
private:
    vecteur v;
    maillon* suiv;

public:
    maillon(vecteur& v);

	friend class liste_vecteurs;
};



class liste_vecteurs
{
private:
    maillon* tete;
    maillon* queue;

public:
    liste_vecteurs();
    ~liste_vecteurs();
    void afficher();
    void ajouter(vecteur& C);
    liste_vecteurs* Inter(liste_vecteurs& C);
    liste_vecteurs* Union(liste_vecteurs& C);
    maillon* chercher(vecteur& C);
    void supprimer_tete();
    void supprimer(vecteur& c);
    void supprimer_toutes(vecteur& c);
};
