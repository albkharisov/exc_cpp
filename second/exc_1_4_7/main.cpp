#include <iostream>

using namespace std;

struct base
{
    int a;
    virtual ~base() {}
};

template<class T>
bool isSameObject(T const * p, T const * q)
{
    if ((dynamic_cast<T const *> (p)) && (dynamic_cast<T const *> (q)))
        return (dynamic_cast<void const *> (p)) == (dynamic_cast<void const *> (q));
    else
        return 0;
}

struct num1 : base
{
    float b;
};

struct num2 : base
{
    double c;
};

struct num3 : num1, num2
{
    char d;
};

int main()
{
    base b1;
    num3 n;

    num1  & n1_ = n;
    base  & bn1_ = n1_;
    num2  & n2_ = n;
    base  & bn2_ = n2_;

    cout << "n = " << reinterpret_cast<void *>(&n) << endl;
    cout << "n1_ = " << reinterpret_cast<void *>(&n1_) << endl;
    cout << "bn1_ = " << reinterpret_cast<void *>(&bn1_) << endl;
    cout << "n2_ = " << reinterpret_cast<void *>(&n2_) << endl;
    cout << "bn2_ = " << reinterpret_cast<void *>(&bn2_) << endl;

    cout << endl;
    cout << "base = base class. Has Virtual Table (bn1_, bn2_)." << endl;
    cout << "n1 and n2 are derived from n." << endl;
    cout << "n is derived from n1 and n2." << endl;
    cout << endl;

    cout << "dynamic_cast<num3 *>(&bn1_) = " << dynamic_cast<num3 *>(&bn1_) << endl;
    cout << "dynamic_cast<num3 *>(&bn2_) = " << dynamic_cast<num3 *>(&bn2_) << endl;
    cout << "dynamic_cast<void *>(&bn1_) = " << dynamic_cast<void *>(&bn1_) << endl;
    cout << "dynamic_cast<void *>(&bn2_) = " << dynamic_cast<void *>(&bn2_) << endl;

    cout << "bn1 == bn2 ? " << isSameObject(&bn1_, &bn2_) << endl;

    return 0;
}


