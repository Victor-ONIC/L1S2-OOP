#include "complexe.h"
 
	complexe::complexe(double r, double i)
	{
		re = r; 
		im = i;
	}

	ostream & operator<<(ostream & o, complexe & z)
	{
        if (z.re != 0)
        {
                o << z.re;
                if (z.im > 0)
                        o << '+';
        }
        if (z.im != 0)
                o << z.im << 'i'; 
        return o;
	}

	istream & operator>>(istream & i, complexe & z)
	{
        i >> z.re;
        i >> z.im;
        return i;
	}

	complexe operator*(complexe & z1, complexe & z2)
	{
		complexe z;
		z.re = z1.re * z2.re;
		z.im = z1.im * z2.im;
		return z;
	}
	

                
                
