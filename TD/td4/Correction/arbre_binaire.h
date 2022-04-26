#include <iostream>

using namespace std;


class noeud
{
    int info;
    noeud * fg, * fd;
    friend class arbre;
  public:
    noeud(int, noeud * = NULL, noeud * = NULL);
    ~noeud();
};


class arbre
{
    noeud * racine;
  public:
    arbre();
    arbre(noeud *);
    ~arbre();
	void detruit(noeud * p);


    int ajoute_feuille1(int);
	int afn1(noeud *,int);
    int ajoute_feuille2(int);
	int afn2(noeud * &,int);
    int ajoute_feuille3(int);
	int afn3(noeud * *,int);

    void afficher();
	void afficherIn(noeud *);
	void afficherPre();
	void afficherPre(noeud *);

	void profondeur();
	void profondeur(noeud *, int);
	
	int hauteur();
	int hauteur(noeud *, int);
	
	bool max(int &);
	void max(noeud *, int &);
	
	bool max_ordonne(int &);
	
	bool egalite(arbre);
	bool egalite(noeud *, noeud *);
	
	noeud * copie(noeud *);
	arbre(arbre &);

	void arbre_miroir(arbre &);
	noeud * arbre_miroir(noeud *);

	bool miroir(arbre &);
	bool miroir(noeud *, noeud *);
	
	bool sous_arbre(arbre &);
	bool sous_arbre(noeud *, noeud *);

};
