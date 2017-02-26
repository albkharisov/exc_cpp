#include <iostream>

using namespace std;
unsigned mangcd(unsigned a, unsigned b);

#define MIN(a,b)			((a) < (b) ? (a) : (b))
#define MAX(a,b)			((a) > (b) ? (a) : (b))
unsigned int gcd(unsigned int a, unsigned int b)
{
	int c;

	if (a == 0)
		return b;
	if (b == 0)
		return a;

	c = a % b;

	cout << "gcd... a = " << a << ", b = " << b << ", c = " << c << endl;

	if (c == 0)
		return MIN(a, b);
	else
		return gcd(b, c);
}

int main()
{
    // 8124
    // 1323
    unsigned int a = 0;
    unsigned int b = 0;
    cout << "Enter a" << endl;
    cin >> a;
    cout << "Enter b" << endl;
    cin >> b;

    cout << "GCD by pereborom:" << endl;

    cout << "mang = " << mangcd(a, b);
//    cout << "mang = " << mangcd(b, a);


    cout << "GCD:" << endl;
    unsigned int c = gcd(a, b);
    cout << "GCD:" << endl;
    unsigned int d = gcd(b, a);

    cout << endl;
    cout << "gcd(" << a << ", " << b << ") = " << c << endl;
    if (c != d)
        cout << "gcd(" << b << ", " << a << ") = " << d << endl;
    return 0;
}

unsigned amas[50];
unsigned bmas[50];
unsigned mangcd(unsigned a, unsigned b)
{
    if ((a <= 1) || (b <= 1))
        return 1;

    for (int i = 0; i < 50 ; ++i)
    {
        amas[i] = 0; bmas[i] = 0;
    }

    unsigned i = 0;

    for (unsigned a2 = a; a2 >= 1; --a2)
    {
        if (!(a % a2))
            amas[i++] = a2;
    }

    i = 0;

    for (unsigned b2 = b; b2 >= 1; --b2)
    {
        if (!(b % b2))
            bmas[i++] = b2;
    }

    for (int i = 0; (i < 50) && (amas[i] || bmas[i]); ++i)
    {
        cout << "amas["<<i<<"]="<<amas[i]<<"  |  "
             << "bmas["<<i<<"]="<<bmas[i]<<endl;
    }

    unsigned gcd = 0;
    unsigned gcdmax = 0;
    for (int i = 0, j = 0; (i < 50) && (j < 50) ; )
    {
        if ((amas[i] > bmas[j]) && (bmas[j+1] != 0))
            ++i;
        else if (amas[i] == bmas[j])
        {
            gcd = amas[i];
            break;
        }
        else
            ++j;
    }

    return gcd;

}





