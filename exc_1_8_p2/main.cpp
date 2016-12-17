#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a, b, c;

    cin >> a >> b >> c;

    double D = b*b - 4*a*c;

//    cout << "a=" << a << endl;
//    cout << "b=" << b << endl;
//    cout << "c=" << c << endl;
//
//    cout << "D=" << D << endl;

    if (D >= 0)
    {
        cout << ((-b + sqrt(D)) / (2*a)) << ' ' << ((-b - sqrt(D)) / (2*a)) << endl;
    }
    else
    {
        cout << "No real roots" << endl;
    }
    // ...

    return 0;
}
