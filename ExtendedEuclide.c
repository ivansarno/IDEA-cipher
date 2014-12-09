#include <assert.h>

typedef struct
{
	long long x;
	long long y;
	long long z;
} triple;




triple ExtendedEuclide(long long a, long long b)
{
    triple result;
    triple temp;

    if (b == 0)
    {
        result.x = a;
        result.y = 1;
        result.z = 0;

        return result;
    }
    else temp = ExtendedEuclide(b, a % b);

    result.x = temp.x;
    result.y = temp.z;
    result.z = temp.y - ((a / b) * temp.z);

    return result;
}

long long inverso(long long n,long long Modulo)
{
	triple ris = ExtendedEuclide(n,Modulo);
    if (ris.y<0)
    	ris.y=Modulo+ris.y;
    assert((ris.y*n)%Modulo==1);
	return  ris.y;
}
