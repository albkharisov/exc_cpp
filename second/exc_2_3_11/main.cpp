#include <iostream>

using namespace std;
template<class F>

void for_each_int(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        f(*p);
}

int main()
{
    auto square_fun = [] (int & j) { j *= j; };
    int m[10] = {1,2,3,4,5,6,7,8,9,10};

    for_each_int(m, m + 10, square_fun); // теперь m = {1,4,9,16,25,36,49,64,81,100};

    cout << endl;
    for (int t : m)
    {
        cout << t << " : ";
    }
    cout << endl;

    return 0;
}
