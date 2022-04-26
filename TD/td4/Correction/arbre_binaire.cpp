#include "arbre_binaire.h"


// Question 1 ----------------------------------------------------------
// On peut faire un seul constructeur pour arbre 
// avec une initialisation par defaut

arbre::arbre()
{
  racine = NULL;
}

arbre::arbre(noeud * N)
{
  racine = N;
}

noeud::noeud(int I, noeud * G, noeud * D)
{
	info = I;
	fg = G;
	fd = D;
}

// Question 1 ----------------------------------------------------------

// Question 2 ----------------------------------------------------------
    
noeud::~noeud()
{
	if (fg != NULL)
	  delete fg;
	if (fd != NULL)
	  delete fd;
}

arbre::~arbre()
{
	if (racine != NULL)
	  delete racine;
}

// Question 2 ----------------------------------------------------------

// Question 3 ----------------------------------------------------------
// Pour bien voir la récursivité dans la destruction

void arbre::detruit(noeud * p)
{
  if (p != NULL)
  {
    detruit(p -> fg);
    detruit(p -> fd);
    delete(p);
  }
}

// Question 3 ----------------------------------------------------------

// Question 4 ----------------------------------------------------------
void arbre::profondeur()
{
	profondeur(racine, 1);
}

void arbre::profondeur(noeud * p, int prof)
{
  if (p == NULL)
    cout << '#';
  else
  {
    cout << '(';
    profondeur(p -> fg, prof + 1);
    cout << ",<";
    cout << p -> info;
    cout << ',';
    cout << prof;
    cout << ">,";
    profondeur(p -> fd, prof + 1);
    cout << ')';
  }
}

// Question 4 ----------------------------------------------------------

// Question 5 ----------------------------------------------------------

int arbre::hauteur()
{
	return hauteur(racine,0);
}

int arbre::hauteur(noeud * p, int h)
{
	int h1, h2;
	
	if (p == NULL)
		return h;
	h1 = hauteur(p -> fg, h);
	h2 = hauteur(p -> fd, h);
	if (h1 > h2)
		return h1 + 1;
	else
		return h2 + 1;
}

// Question 5 ----------------------------------------------------------

// Question 6 ----------------------------------------------------------

bool arbre::max(int & m)
{ 	// N'a de sens que sur un arbre non vide
	// On peut ajouter un booleen pour dire que la recherche
	// etait possible
	
	if (racine == NULL)
		return false;
	else
	{
		m = racine -> info;
		max(racine, m);
		return true;
	}
}

void arbre::max(noeud * p, int & m)
{

	if (p == NULL)
		return;
	if (p -> info > m)
		m = p -> info;
	max(p -> fg, m);
	max(p -> fd, m);
}

// Question 6 ----------------------------------------------------------

// Question 7 ----------------------------------------------------------

bool arbre::max_ordonne(int & m)
{
	noeud * p;
	
	if (racine == NULL)
		return false;
	p = racine;
	while (p -> fd != NULL)
		p = p -> fd;
	m = p -> info;
	return true;
}

// Question 7 ----------------------------------------------------------

// Question 8 ----------------------------------------------------------
// 3 versions
// passage du noeud par valeur
int arbre::afn1(noeud * p,int v)
{
  if (v == p -> info)
    return 0;
  if (v < p -> info)
    if (p -> fg == NULL)
    {
      p -> fg = new noeud(v);
//      p -> fg -> info = v;
//      p -> fg -> fg = p -> fg -> fd = NULL;
      return 1;
    }
    else
      return afn1(p -> fg, v);
  else
    if (p -> fd == NULL)
    {
      p -> fd = new noeud(v);
//      p -> fd -> info = v;
//      p -> fd -> fg = p -> fd -> fd = NULL;
      return 1;
    }
    else
      return afn1(p -> fd, v);
}

int arbre::ajoute_feuille1(int i)
{
  if (racine == NULL)
  {
    racine = new noeud(i);
//    racine -> info = i;
//    racine -> fg = racine -> fd = NULL;
    return 1;
  }
  else
    return afn1(racine,i);
}

// passage du noeud par reference
int arbre::afn2(noeud * & p,int v)
{
  if (p == NULL)
  {
    p = new noeud(v);
//    p -> info = v;
//    p -> fg = p -> fd = NULL;
    return 1;
  }
  if (v == p -> info)
    return 0;
  if (v < p -> info)
    return afn2(p -> fg, v);
  else
    return afn2(p -> fd, v);
}

int arbre::ajoute_feuille2(int i)
{
  return afn2(racine,i);
}

// passage du noeud par adresse
int arbre::afn3(noeud * * p,int v)
{
  if ((*p) == NULL)
  {
    (*p) = new noeud(v);
//    (*p) -> info = v;
//    (*p) -> fg = (*p) -> fd = NULL;
    return 1;
  }
  if (v == (*p) -> info)
    return 0;
  if (v < (*p) -> info)
    return afn3(&((*p) -> fg), v);
  else
    return afn3(&((*p) -> fd), v);
}

int arbre::ajoute_feuille3(int i)
{
  return afn3(&racine,i);
}
// Question 8 ----------------------------------------------------------

// Affichage ----------------------------------------------------------
// 2 versions
// Preordre
void arbre::afficherPre(noeud * p)
{
  if (p == NULL)
    cout << '#';
  else
  {
    cout << '(';
    cout << p -> info;
    cout << ',';
    afficherPre(p -> fg);
    cout << ',';
    afficherPre(p -> fd);
    cout << ')';
  }
}

void arbre::afficherPre()
{
  if (!racine) return;
  cout << endl;
  afficherPre(racine);
  cout << endl;
}

// Inordre
void arbre::afficherIn(noeud * p)
{
  if (p == NULL)
    cout << '#';
  else
  {
    cout << '(';
    afficherIn(p -> fg);
    cout << ',';
    cout << p -> info;
    cout << ',';
    afficherIn(p -> fd);
    cout << ')';
  }
}

void arbre::afficher()
{
  if (!racine) return;
  cout << endl;
  afficherIn(racine);
  cout << endl;
}

// Question 9 ----------------------------------------------------------

bool arbre::egalite(arbre a)
{
	return egalite(racine, a.racine);
}

bool arbre::egalite(noeud * n1, noeud * n2)
{
	if (n1 == NULL && n2 == NULL)
		return true;
	if (n1 == NULL || n2 == NULL)
		return false;
	return n1 -> info == n2 -> info
		&& egalite(n1 -> fg, n2 -> fg)
		&& egalite(n1 -> fd, n2 -> fd);
}

// Question 9 ----------------------------------------------------------

// Question 10 ---------------------------------------------------------

noeud * arbre::copie(noeud * n)
{
	if (n == NULL)
		return NULL;
	return new noeud(n -> info, copie(n -> fg), copie(n -> fd));
}

arbre::arbre(arbre & A)
{
	racine = copie(A.racine);
}

// Question 10 ---------------------------------------------------------

// Question 11 ---------------------------------------------------------
void arbre::arbre_miroir(arbre & A)
{
	if (racine != NULL)
		detruit(racine);
	racine = arbre_miroir(A.racine);
}

noeud * arbre::arbre_miroir(noeud * n)
{
	if (n == NULL)
		return NULL;
	return new noeud(n -> info, arbre_miroir(n -> fd), arbre_miroir(n -> fg));
}
// Question 11 ---------------------------------------------------------

// Question 12 ---------------------------------------------------------
bool arbre::miroir(arbre & A)
{
	return miroir(racine, A.racine);
}

bool arbre::miroir(noeud * n1, noeud * n2)
{
	if (n1 == NULL && n2 == NULL)
		return true;
	if (n1 == NULL || n2 == NULL)
		return false;
	return n1 -> info == n2 -> info
		&& miroir(n1 -> fg, n2 -> fd)
		&& miroir(n1 -> fd, n2 -> fg);
}
// Question 12 ---------------------------------------------------------

// Question 13 ---------------------------------------------------------
bool arbre::sous_arbre(arbre & A)
{	// le premier est un sous-arbre du second
	return sous_arbre(racine, A.racine);
}

bool arbre::sous_arbre(noeud * n1, noeud * n2)
{							// n1 est sous-arbre de n2 si
	if (egalite(n1, n2))
		return true;		// il est egal à n2
	if (n2 != NULL)
		return sous_arbre(n1, n2 -> fg)	// il est sous_arbre du fg de n2
			|| sous_arbre(n1, n2 -> fd);// il est sous_arbre du fd de n2
	return false;
}
// Question 13 ---------------------------------------------------------





