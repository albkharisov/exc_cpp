#include <iostream>
#include "main.h"

void func2();
void func();

void func()
{
//    std::cout << Test << std::endl;
}

int main()
{
    func();
    func2();

    std::cout << std::endl;
    std::cout << std::endl;
    Test a;
    std::cout << a.data << std::endl;

    std::cout << int(&foo) << std::endl;
    foo();
    std::cout << int(&bar) << std::endl;
    bar();
    std::cout << int(&foobar) << std::endl;
    foobar();

    std::cout << "Hello world!" << std::endl;
    return 0;
}
