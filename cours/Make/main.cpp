#include <iostream>

#include "matcomp.h"
#include "complexe.h"
 
using namespace std;

int main() 
{
	complexe c1, c2;
	
	cin >> c1;
	cin >> c2;
	
	matcomp MC(12,15);
	
	MC.remplir();
	MC.afficher();
	
	if (MC.rechercher(c1))
		cout << c1 << " est dans la matrice" ;
	else
		cout << c1 << " n'est pas dans la matrice" ;
	cout << endl;
	
	MC.multiplier(c2);
	MC.afficher();
}
