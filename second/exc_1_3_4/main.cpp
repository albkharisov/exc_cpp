#include <iostream>

using namespace std;

struct Number {
    int a;
};

struct BigInt : Number
{
    BigInt(int x) {}
};
struct String
{
    explicit String(char const * s)
    {
    }
};

#include "stdio.h"
int main()
{
//    int a = static_cast<int>(3.5);
//    double b = static_cast<double>(7);
//    BigInt c = static_cast<BigInt>(100500);
//    String d = static_cast<String>("Stepik");
//    Number * e = static_cast<Number *>(&c);
//    BigInt * f = static_cast<BigInt *>(e);
//    void * g = static_cast<void *>(f);
//    BigInt * h = static_cast<BigInt *>(g);


//    int a = static_cast<int>(3.5);
//    double b = static_cast<double>(7);
//    BigInt c = static_cast<BigInt>(100500);
//    String d = static_cast<String>("Stepik");
//    Number * e = static_cast<Number *>(&c);
//    BigInt * f = static_cast<BigInt *>(e);
//    void * g = static_cast<void *>(f);
//    BigInt * h = static_cast<BigInt *>(g);
#if 0
    int a = 3.5;
    double b = 7;
    BigInt c = 100500;
//    String d = "Stepik";    // String d = String("Stepik");        // need
    Number * e = &c;
//    BigInt * f = e;           // need
    BigInt * f = 0;
    void * g = f;
    BigInt * h = g;
#else
    int a = 5;
    void * b = NULL;
    b = &a;
    int * c = (int *) 0x08005430;
    void * d = NULL;
    c = d;

#endif


    cout << "Hello world!" << "!"<< endl;
//    printf("d1=%s\r\n", d);
    return 0;
}
