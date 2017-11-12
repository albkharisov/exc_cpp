#include <iostream>
#include <functional>

using namespace std;

template <class T, typename ...Args>
auto apply2(T func, Args&&... args) -> std::string
{
    return func(std::forward<Args>(args)...);
}

template <class T, typename ...Args>
auto apply(T func, Args&&... args) -> decltype(func(std::forward<Args>(args)...))
{
    return func(std::forward<Args>(args)...);
}

int main()
{
    auto fun = [](std::string a, std::string const& b) { return a += b; };
    std::string s("world!");
    cout << s << endl;
    s = apply(fun, std::string("Hello, "), s);


    cout << s << endl;
    return 0;
}
