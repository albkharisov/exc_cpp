#include <iostream>

using namespace std;

void swap4ik(int * a, int * b);

void rotate(int a[], unsigned size, int shift)
{
    shift %= size;

    if (!size) return;

    while (shift--)
    {
        swap4ik(&a[0], &a[size-1]);
        for (int i = 0; i < size-2; ++i)
            swap4ik(&a[i+1], &a[i]);
//        cout << endl;
    }
}

void swap4ik(int * a, int * b)
{
//    cout << "a=" << *a << " b=" << *b << endl;
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
//    cout << "a=" << *a << " b=" << *b << endl;
}

#define MAS_SIZE(x)                 (sizeof(x)/sizeof(int))
int main()
{
    int a[] = {1,2,3,4,5};

//    swap4ik(&a[0], &a[4]);
    cout << endl << "a: ";
    for (int i = 0; i < MAS_SIZE(a) ; ++i)
    {
        cout << " " << a[i];
    }
    cout << endl;

    rotate(a, MAS_SIZE(a), 4);

    cout << endl << "a: ";
    for (int i = 0; i < MAS_SIZE(a) ; ++i)
    {
        cout << " " << a[i];
    }
    cout << endl;

    return 0;
}
