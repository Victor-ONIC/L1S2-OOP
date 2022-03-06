#ifndef ___COMPLEXE_H___
#define ___COMPLEXE_H___
 
#include <iostream> 
 
using namespace std;

class complexe
{
	    double re, im;
    public:
        complexe(double = 0., double = 0.);
        
        friend complexe operator*(complexe &, complexe &);
        
        friend ostream & operator<<(ostream & o, complexe & z);
        friend istream & operator>>(istream & i, complexe & z);
        // et bien d'autres...

};

#endif
