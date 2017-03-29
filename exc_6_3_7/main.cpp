#include <iostream>

using namespace std;

struct Dummy { };
typedef int type;

template <typename T1, typename T2>
class SameType
{
public:
    static const bool value = false;
};

template <>
template <typename T>
class SameType <T, T>
{
public:
    static const bool value = true;
};


int main()
{
    std::cout << SameType<int, int>::value << ": 1" << std::endl; // выведет 1, т. е. true
    std::cout << SameType<int, type>::value << ": 1" << std::endl; // 1, type == int
    std::cout << SameType<int, int&>::value << ": 0" << std::endl; // 0, int и ссылка на int - различные типы
    std::cout << SameType<Dummy, Dummy>::value << ": 1" << std::endl; // 1
    std::cout << SameType<int, const int>::value << ": 0" << std::endl; // 0, const - часть типа
    cout << "Hello world!" << endl;
    return 0;
}
