#include <iostream>

using namespace std;

#include <typeinfo>

struct Expression
{
    virtual ~Expression(){};
    int a;
};

struct number1 : Expression
{
    int b;
};

struct number2 : Expression
{
    double c;
};

bool check_equals(Expression const *left, Expression const *right)
{
    return typeid(*left) == typeid(*right);
}

int main()
{
    number1 * n1 = new(number1);
    number2 * n2 = new(number2);

    cout << "number1 == number2 ? " << check_equals(n1, n2) << endl;
    cout << "number1 == number1 ? " << check_equals(n1, n1) << endl;
    cout << "number2 == number2 ? " << check_equals(n2, n2) << endl;
    cout << "number2 == number1 ? " << check_equals(n2, n1) << endl;

    return 0;
}



