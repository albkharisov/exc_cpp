#include <iostream>

using namespace std;

template <typename Type1, typename Type2>
void copy_n(Type1 *d, Type2 *s, int num)
{
    for (int i = 0; i < num ; ++i)
    {
        d[i] = (Type1) s[i];
    }
}

int main()
{
    float floats[] = {5, 6.1, 7, 8};
    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4);

    cout << "outm = ";
    for (int i = 0 ; i < 4 ; ++i)
    {
        cout << doubles[i] << ", ";
    }
    cout << endl;

    copy_n(doubles, floats, 4);
    cout << "outm = ";
    for (int i = 0 ; i < 4 ; ++i)
    {
        cout << doubles[i] << ", ";
    }

    cout << endl;

    return 0;
}
