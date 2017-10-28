#include <iostream>

using namespace std;

int main()
{
    int a = 27;
    int const b = 412;
    int * pa = &a;

//    int const c = const_cast<int const &>(a);
//    int d = const_cast<int &>(b);
//    int const * p1 = const_cast<int const *>(pa);
//    int * const * p2 = const_cast<int * const *>(&pa);
//    int const ** p3 = const_cast<int const **>(&pa);
//    int const * const * p4 = const_cast<int const * const *>(&pa);

    int const c = a;
    int d = b;
    int const * p1 = pa;
    int * const * p2 = &pa;
//    int const ** p3 = &pa;
    int const * const * p4 = &pa;

    int * const p5 = pa;


    cout << "Hello world!" << endl;
    return 0;
}
