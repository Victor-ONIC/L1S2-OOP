#include "matcomp.h"
#include "complexe.h"

	matcomp::matcomp(int l, int c)
	{
		int i; 
		
		nl = l;
		nc = c;
		mat = new complexe *[nl];
		for (i = 0 ; i < nl ; i++)
		  mat[i] = new complexe[nc];
	}
	
	matcomp::~matcomp(){/*...*/}
	
	void matcomp::remplir(void){/*...*/}

	void matcomp::afficher(void)
	{
		// Cette fonction fera certainement appel a la fonction d'affichage 
		// d'un complexe, ou a la surdefinition de l'operateur >> pour les
		// complexes.
		// ...
	}
	
	int matcomp::rechercher(complexe c){/*...*/ return 0;}
	
	void matcomp::multiplier(complexe c)
	{
		int i, j;
		
		for (i = 0 ; i < nl ; i ++)
		  for (j = 0 ; j < nc ; j++)
		    mat [i][j] = mat [i][j] * c;
	}
    
	// et bien d'autres
