#ifndef ___MATCOMP_H___
#define ___MATCOMP_H___

#include <iostream>

#include "complexe.h"  

using namespace std;

class matcomp
{
	int nl, nc;
	complexe ** mat;
	
	public:
	matcomp(int, int);
	~matcomp();
	void remplir(void);
	void afficher(void);
	int rechercher(complexe);
	void multiplier(complexe);
    // et bien d'autres
};

#endif
