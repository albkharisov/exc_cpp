#include <iostream>
#include <typeinfo>

using namespace std;

void print_values(std::ostream & os) {}

template <typename T, typename... Args>
void print_values(std::ostream & os, T value, Args... args)
{
    os << typeid(value).name() << ": " << value << std::endl;
    print_values(os, args...);
}

int main()
{
    print_values(std::cout, 0, 3.5, "Hello");
//    std::cout << "Hello world!" << std::endl;
//    cout << typeid(3.5).name() << endl;
    return 0;
}

/**

i: 0
d: 3.5
PKc: Hello

*/
