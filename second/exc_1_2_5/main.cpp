#include <iostream>

using namespace std;

struct Base
{
    int a;
};
struct D1 : Base
{
    int b;
};
struct D2 : Base
{
    int b;
};
struct D3 : D1, D2
{
    int c;
};

// base указывает на экземпляр Base, соответствующий D1
// нужно вернуть указатель на экземпляр Base, соответствующий D2
Base const * D1BaseToD2Base( Base const * base )
{
    const D3 * d3 = (D3 *) (D1 *) base;
    const D2 &d2 = *d3;
    return &d2;
}


int main()
{
    D3 d3;
    D2 & d2 = d3;
    D1 & d1 = d3;
    d2.a = 2;
    d1.a = 1;

    int g = D1BaseToD2Base(&d1)->a;

    cout << "g=" << g << endl;
    return 0;
}
