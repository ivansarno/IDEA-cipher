/*
implementation of Extended Euclide algorithm to find the inverse of a numbere in module
*/
//Version V.1.2

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

long long inverse(long long number,long long modulo)
{
	triple ris = ExtendedEuclide(number, modulo);
    if (ris.y < 0)
    	ris.y = modulo + ris.y;

	return  ris.y;
}
