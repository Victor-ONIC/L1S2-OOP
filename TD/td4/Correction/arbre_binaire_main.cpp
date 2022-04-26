#include <iostream>
#include "arbre_binaire.h"

using namespace std;



int main()
{
	arbre a1, a2, a3;
	int val;
	
	cout << "Entrer des valeurs entières, 0 pour terminer" << endl;
	cin >> val;
	while (val != 0)
	{
		a1.ajoute_feuille1(val);
		a2.ajoute_feuille2(val);
		a3.ajoute_feuille3(val);
		cin >> val;
	}
	a1.afficher();
	a2.afficher();
	a3.afficher();
	
	cout << endl << "Profondeur : " << endl;
	a1.profondeur();
	cout << endl;
	
	cout << endl << "Hauteur : " << endl;
	cout << a1.hauteur();
	cout << endl;


	arbre B(new noeud(7,
				new noeud(3,
					new noeud(4),
					new noeud(9,new noeud(12),NULL)
					),
				new noeud(5,
					new noeud(23,NULL,new noeud(17)),
					NULL)
				)
			);
	int m;
	
	cout << endl << "Maximum : " << endl;
	B.afficher();
	B.max(m);
	cout << m;
	cout << endl;

	arbre C(new noeud(4,new noeud(2,new noeud(1),new noeud(3)),new noeud(6,new noeud(5),new noeud(7))));
	
	cout << endl << "Maximum dans un arbre ordonne : " << endl;
	C.afficher();
	C.max_ordonne(m);
	cout << m;
	cout << endl;
	
	arbre D(new noeud(4,new noeud(2,new noeud(1),new noeud(3)),NULL));
	
	cout << endl << "Maximum dans un arbre ordonne : " << endl;
	D.afficher();
	D.max_ordonne(m);
	cout << m;
	cout << endl;
	
	C.afficher();
	D.afficher();
	if (C.egalite(D))
		cout << "egaux";
	else
		cout << "différents";
	cout << endl << endl;
		
	arbre E1(new noeud(7,new noeud(3,new noeud(4),new noeud(9,new noeud(12),NULL)),
				 new noeud(5,new noeud(23,NULL,new noeud(17)),NULL)));
	arbre E2(new noeud(7,new noeud(3,new noeud(4),new noeud(9,new noeud(12),NULL)),
				 new noeud(5,new noeud(23,NULL,new noeud(17)),NULL)));
	
	E1.afficher();
	E2.afficher();
	if (E1.egalite(E2))
		cout << "egaux";
	else
		cout << "différents";
	cout << endl << endl;

	arbre F(E1);
	F.afficher();
	E1.afficher();
	if (E1.egalite(F))
		cout << "egaux";
	else
		cout << "différents";
	cout << endl << endl;
	
	arbre G;
	G.arbre_miroir(F);

	F.afficher();
	G.afficher();
	if (G.miroir(F))
		cout << "miroirs";
	else
		cout << "pas miroirs";
	cout << endl << endl;
	
	G.afficher();
	G.afficher();
	if (G.miroir(G))
		cout << "miroirs";
	else
		cout << "pas miroirs";
	cout << endl << endl;
	
	arbre H(new noeud(3,new noeud(4),new noeud(9,new noeud(12),NULL)));
	
	H.afficher();
	F.afficher();
	if (H.sous_arbre(F))
		cout << "sous-arbre";
	else
		cout << "pas sous-arbre";
	cout << endl << endl;

	H.afficher();
	G.afficher();
	if (H.sous_arbre(G))
		cout << "sous-arbre";
	else
		cout << "pas sous-arbre";
	cout << endl << endl;
}

