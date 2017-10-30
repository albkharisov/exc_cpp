#include <iostream>
#include <string>

using namespace std;

// typedef P (T * mptr) (const T &, const T &);

template<class T, typename P>
bool compare(const T & a, const T & b, P (T:: * mptr) () const)
{
    return (a.*mptr)() < (b.*mptr)();
}

int main()
{
    std::string s1("Elf");
    std::string s2("Archer");

// сравнение строк по длине
    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false

    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    return 0;
}
