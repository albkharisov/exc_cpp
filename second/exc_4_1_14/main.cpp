#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <typeinfo>


struct bad_from_string : std::exception
{
    bad_from_string(std::string const & str) : s(str) {}
    bad_from_string(const char * str) : s(str) {}

    const char * what() const noexcept override
    {
        return s.data();
    }
    std::string s;
};


// функция from_string
template<class T>
T from_string(std::string const& s)
{
    T a;
    T b;
    char c;
    std::istringstream str(s);
    str >> std::noskipws;
    bool exc = false;

    try
    {
        if ( !(str >> a) || (str >> c) )
        {
//            cout << "FAIL" << endl;
            exc = true;
        }
    }
    catch (...)
    {
//        std::cout << "ERROR type(" << typeid(T).name() << ")" << std::endl;
        throw bad_from_string(typeid(T).name());
    }

    if (exc)
    {
        throw bad_from_string(typeid(T).name());
    }
    return a;
    // реализация
}

#define CONST_WRAPPER(x)                \
try {                                   \
    x;                                  \
} catch (std::exception const & e) {    \
    cout << "exception poimal, type(" << e.what() << ")" << endl;   \
} catch (...) {                             \
    cout << "unknown exception" << endl;    \
}

using namespace std;

int main()
{
#if 1
    string s1("123");
    cout << "string = \"" << s1 << "\"" << endl;
    CONST_WRAPPER(int    a1 = from_string<int>   (s1); std::cout << "a1<int>= "    << a1 << std::endl );     // a1 = 123
    CONST_WRAPPER(double b1 = from_string<double>(s1); std::cout << "b1<double>= " << b1 << std::endl );     // b1 = 123.0
    CONST_WRAPPER(string c1 = from_string<string>(s1); std::cout << "c1<string>= " << c1 << std::endl );     // c1 = "123"
    cout << endl;

    string s2("12.3");
    cout << "string = \"" << s2 << "\"" << endl;
    CONST_WRAPPER(int    a2 = from_string<int>   (s2); std::cout << "a2<int>= "    << a2 << std::endl );     // исключение
    CONST_WRAPPER(double b2 = from_string<double>(s2); std::cout << "b2<double>= " << b2 << std::endl );     // b2 = 12.3
    CONST_WRAPPER(string c2 = from_string<string>(s2); std::cout << "c2<string>= " << c2 << std::endl );     // c2 = "12.3"
    cout << endl;
#endif  // 0

    string s3("abc");
    cout << "string = \"" << s3 << "\"" << endl;
    CONST_WRAPPER(int    a3 = from_string<int>   (s3); std::cout << "a3<int>= " << a3 << std::endl );     // исключение
    CONST_WRAPPER(double b3 = from_string<double>(s3); std::cout << "b3<double>= " << b3 << std::endl );     // исключение
    CONST_WRAPPER(string c3 = from_string<string>(s3); std::cout << "c3<string>= " << c3 << std::endl );     // c3 = "abc"
    cout << endl;

    return 0;
}
