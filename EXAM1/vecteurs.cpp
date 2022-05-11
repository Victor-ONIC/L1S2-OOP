#include "vecteurs.h"

vecteur::vecteur(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

void vecteur::afficher()
{
	cout << '(' << x << ',' << y << ',' << z << ')';
}

vecteur vecteur::add(vecteur& a)
{
	vecteur e(x + a.x, y + a.y, z + a.z);
	return e;
}

vecteur vecteur::minus(vecteur& a)
{
	vecteur e(x - a.x, y - a.y, z - a.z);
	return e;
}

double vecteur::produit_scalaire(vecteur& a)
{
	double ps = x * a.x + y * a.y + z * a.z;
	return ps;
}

double vecteur::norme()
{
	double N = produit_scalaire(*this);
	N = sqrt(N);
	return N;
}

bool vecteur::identique(vecteur& C)
{
	vecteur v = minus(C);

	if (v.norme() < 0.01)
	{
		return true;
	}

	return false;
}



collection_vecteurs::collection_vecteurs(int n)
{
	T = new vecteur[n];
	capacite = n;
	nbv = 0;
}

collection_vecteurs::~collection_vecteurs()
{
	delete[] T;
}

bool collection_vecteurs::ajouter(vecteur& c)
{
	if (nbv == capacite)
	{
		return false;
	}

	T[nbv] = c;
	nbv++;
	return true;
}

void collection_vecteurs::afficher()
{
	for (int i = 0; i < nbv; i++)
	{
		T[i].afficher();
		cout << endl;
	}
}

bool collection_vecteurs::chercher(vecteur& c)
{
	for (int i = 0; i < nbv; i++)
	{
		if (T[i].identique(c))
		{
			return true;
		}
	}

	return false;
}



maillon::maillon(vecteur& v)
{
	this->v = v;
	suiv = NULL;
}

liste_vecteurs::liste_vecteurs()
{
	tete = NULL;
	queue = NULL;
}

liste_vecteurs::~liste_vecteurs()
{
	maillon* p = tete;
	maillon* tmp = NULL;
	while (p != NULL)
	{
		tmp = p;
		p = p->suiv;
		delete tmp;
	}
}

void liste_vecteurs::afficher()
{
	maillon* p = tete;

	while (p != NULL)
	{
		p->v.afficher();
		cout << endl;
		p = p->suiv;
	}
}

void liste_vecteurs::ajouter(vecteur& C)
{
	maillon* m = new maillon(C);

	if (tete == NULL)
	{
		queue = tete = m;
		return;
	}

	queue->suiv = m;
	queue = m;
}

liste_vecteurs* liste_vecteurs::Inter(liste_vecteurs& C)
{
	liste_vecteurs* liste = new liste_vecteurs;

	maillon* p = C.tete;
	while (p != NULL)
	{
		if (chercher(p->v) != NULL)
		{
			liste->ajouter(p->v);
		}

		p = p->suiv;
	}

	return liste;
}

liste_vecteurs* liste_vecteurs::Union(liste_vecteurs& C)
{
	liste_vecteurs* liste = new liste_vecteurs;

	maillon* p = tete;
	while (p != NULL)
	{
		liste->ajouter(p->v);
		p = p->suiv;
	}

	p = C.tete;
	while (p != NULL)
	{
		liste->ajouter(p->v);
		p = p->suiv;
	}

	return liste;
}

maillon* liste_vecteurs::chercher(vecteur& C)
{
	maillon* p = tete;
	while (p != NULL)
	{
		if (p->v.identique(C))
		{
			return p;
		}

		p = p->suiv;
	}

	return NULL;
}

void liste_vecteurs::supprimer_tete()
{
	if (tete == NULL)
	{
		return;
	}

	maillon* m = tete;
	tete = tete->suiv;
	delete m;
}

void liste_vecteurs::supprimer(vecteur& c)
{
	maillon* m = chercher(c);
	if (m == NULL)
	{
		return;
	}

	vecteur tmp = tete->v;
	tete->v = m->v;
	m->v = tmp;

	supprimer_tete();
}

void liste_vecteurs::supprimer_toutes(vecteur& c)
{
	maillon* m = chercher(c);
	while (m != NULL)
	{
		supprimer(c);
		m = chercher(c);
	}
}
