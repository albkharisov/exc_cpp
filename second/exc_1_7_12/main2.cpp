#include <iostream>
#include "main.h"

void func2()
{
    Test a;
    std::cout << a.data << std::endl;
    //std::string str = Test.data;
    //std::cout << Test << std::endl;
    std::cout << int(&foo) << std::endl;
    foo();
    std::cout << int(&bar) << std::endl;
    bar();
    std::cout << int(&foobar) << std::endl;
    foobar();
}

