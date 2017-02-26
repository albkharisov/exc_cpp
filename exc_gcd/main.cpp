#include <iostream>

using namespace std;
unsigned mangcd(unsigned a, unsigned b);
unsigned int gcd(unsigned int a, unsigned int b);

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

//	cout << "gcd... a = " << a << ", b = " << b << ", c = " << c << endl;

	if (c == 0)
		return MIN(a, b);
	else
		return gcd(b, c);
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

unsigned strlen(const char * str)
{
    unsigned int i = 0;

    while(str[i])
        ++i;

    return i;
}

// my cat
// tolen = 2
//
void strcat(char *to, const char *from)
{
    unsigned tolen = strlen(to);

    unsigned i = 0;
    do
    {
        to[tolen+i] = from[i];
    }
    while(from[i++]);
}

/**
 *
 * text = mycat is cat
 * pattern = cat
 *
 */
int strstr(const char *text, const char *pattern)
{
    unsigned i = 0;
    unsigned j = 0;

    do
    {
        if (!pattern[j])
            return (int) (i - j);
        if (text[i] == pattern[j])
            ++j;
        else
            j = 0;
    }
    while (text[i++]);

    return -1;
}

int main()
{
#if 1
    char str1[] = "cat my is cat";
    char str2[] = "dig";
    cout << "str1=\"" << str1 << "\", " << "size=" << strlen(str1) << endl;
    cout << "str2=\"" << str2 << "\", " << "size=" << strlen(str2) << endl;

    int i = strstr(str1, str2);

    if (i < 0)
        cout << "no substr found" << endl;
    else
    {
        cout << "substr pos = " << i << endl;
        char *p = str1 + i;
        cout << "str1 left=\"" << p << "\"" << "size=" << strlen(p) << endl;
    }

#else
    char str1[30] = "my ZZZZZXXXXXXXXXXXXXXX";
    str1[3] = 0;
    char str2[30] = "catt**********************";
    str2[4] = 0;
    cout << "str1=\"" << str1 << "\", " << "size=" << strlen(str1) << endl;
    cout << "str2=\"" << str2 << "\", " << "size=" << strlen(str2) << endl;

    strcat(str1, str2);
    cout << "str1=\"" << str1 << "\", " << "size=" << strlen(str1) << endl;
    cout << "str2=\"" << str2 << "\", " << "size=" << strlen(str2) << endl;


//#else
    unsigned char str[] = "test string";
    cout << "str=\"" << str << "\", " << "size=" << strlen(str) << endl;

//#else
    // 8124
    // 1323
    unsigned int a = 0;
    unsigned int b = 0;
    cout << "Enter a" << endl;
    cin >> a;
    cout << "Enter b" << endl;
    cin >> b;

//    cout << "GCD by pereborom:" << endl;
//
//    cout << "mang = " << mangcd(a, b) << endl;
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
#endif
}




