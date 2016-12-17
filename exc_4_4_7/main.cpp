#include <iostream>
#include <stdio.h>

using namespace std;



struct Expression
{
    virtual char evaluate() const = 0;
    virtual char evaluate2() const = 0;
    virtual char evaluate3() const = 0;
    virtual ~Expression(){ cout << "ex destr\r\n" << endl; printf("12345");}
};

struct Num : Expression
{
    Num(char value, char a, char b, char c)
        : value(value), a(a), b(b), c(c)
    {}

    char evaluate() const { return value; printf("12345");}
    char evaluate2() const { return value*2; printf("12345");}
    char evaluate3() const { return value*3; printf("12345");}

    ~Num(){cout << "num destr\r\n" << endl; printf("12345");}

private:
    double value;
    char a;
    char b;
    char c;
};

struct Bop : Expression
{
    Bop(char value, char a, char b, char c)
        : value(value), a(a), b(b), c(c)
    {}

    char evaluate() const { return 0; printf("12345");}
    char evaluate2() const { return value*2+1; printf("12345");}
    char evaluate3() const { return value*3+2; printf("12345");}

    ~Bop(){cout << "bop destr\r\n" << endl;printf("12345");}

private:
    double value;
    char a;
    char b;
    char c;
};




typedef char (*func_t) (const Expression *);

func_t f;

bool check_equals2(Expression const *left, Expression const *right)
{
    void * ptr = (void *) (*(unsigned size_t const *) left);
    printf("ptr=0x%08X, *ptr=0x%08X\r\n", ptr, *(unsigned size_t const *) ptr);

    for (int i = 0; i < 32/4; i++)
        printf("(%2d) 0x%08X\r\n", i, ((unsigned int const *)ptr)[i]);

//    void * pptr = (void *) (*(unsigned long const *) ptr);
//    for (int i = 0; i < 30; i++)
//        printf("(%2d) 0x%02X\r\n", i, ((unsigned char const *)pptr)[i]);

}

bool check_equals(Expression const *left, Expression const *right)
{
//    void const * ptr = (const void *) left;
//    void const * ptr2 = (const void *) left;
//
//    void **ptr3 = (void **) left;
//
//    printf("ptr=0x%08X, *ptr=0x%08X, **ptr=0x%08X\r\n", ptr3, *(unsigned size_t const *) ptr3,
//           *(unsigned size_t const *) (*(unsigned size_t const *) ptr3)  );
//    printf("ptr=0x%08X, *ptr=0x%08X\r\n", ptr, *(unsigned size_t const *) ptr);
//
//    printf("\r\n");

//    printf("sizeof(void *)=%d\r\n", sizeof(void *));
//    unsigned int const vt = (unsigned int const *) ptr;

//    func_t *func2 = (func_t *) (*(unsigned long const *) ptr);
//    void *func2 = (void *) *(unsigned size_t const *)left;
    func_t func = (func_t)   (*(unsigned size_t const *) (*(unsigned size_t const *) left+8));

//    printf("adr=0x%08X, func() = %d\r\n", (void *)(func2), left->evaluate());
//    printf("adr=0x%08X, func() = %d\r\n", (void *)func(left), 0);
    printf("adr=0x%08X, func() = %d\r\n", (void *)func, (*func)(left));

    (*func)(left);

    return false;

//    for (int i = 0; i < 32/4; i++)
//        printf("(%2d) 0x%08X : 0x%08X, %s\r\n", i, ((unsigned int const *)ptr)[i],
//                                                   ((unsigned int const *)ptr2)[i],
//                ((unsigned int const *)ptr)[i] == ((unsigned int const *)ptr2)[i]? "" : "DIFF");
//
//    printf("============\r\n");
//
//
//    return true;
}


bool check_equal(Expression const *left, Expression const *right)
{
    void * p1 = (void *) left;
    void * p2 = (void *) right;


    if (*(unsigned int *)p1 == *(unsigned int *)p2)
        return true;
    else
        return false;
}

int main()
{
//    Expression * sube = new Bop(new Num(4.5), '*', new Num(5));
//    Expression * expr = new Bop(new Num(3), '+', sube);
//    std::cout << expr->evaluate() << std::endl;
//    delete expr;


    Bop * be = new Bop(51, 'a', 'b', 'c');
    Num * ne = new Num(51, 'a', 'b', 'c');
    Num * ne2 = new Num(51, 'a', 'b', 'c');
//    Bop * be = new Bop(ne, '+', ne);

    cout << "ne:ne2" << check_equals2(ne, ne2) << endl;

    printf("\r\n\r\n");
    cout << "ne:be" << check_equals(ne, ne2) << endl;

    return 0;
}
