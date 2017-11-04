#include <iostream>
#include <tuple>


using namespace std;

template <int ARG1, int ARG2, typename... args>
auto to_pair(std::tuple<args...> t) -> decltype(std::make_pair(std::get<ARG1>(t), std::get<ARG2>(t)))
{
    return std::make_pair(std::get<ARG1>(t), std::get<ARG2>(t));
}

int main()
{
    auto t = std::make_tuple(0, 3.5, "Hello");
    auto p = to_pair<1,2>(t);
    cout << p.first << ":" << p.second << endl;

    auto p1 = to_pair<0,1>(t);
    cout << p1.first << ":" << p1.second << endl;
    return 0;
}


#if 0
// example
auto t = std::make_tuple(0, 3.5, "Hello");
std::pair<double, char const *> p = to_pair<1,2>(t);
 p содержит 3.5 и "Hello"
#endif
