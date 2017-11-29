#include <iostream>
#include <tuple>
#include <type_traits>

template <int... I>
struct IntList;

template <int H, int... I>
struct IntList<H, I...>
{
    static int const Head = H;
    using Tail = IntList<I...>;
};

template <>
struct IntList<> { };

template<int H, typename T = IntList<>>
struct Generate;


template<int H, int ...I>
struct Generate<H, IntList<I...>>
{
    using type = typename Generate<H-1, IntList<H-1, I...>>::type;
};


template<int ...I>
struct Generate<0, IntList<I...>>
{
    using type = IntList<I...>;
};

template<typename T>
void check()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//////////////////////////////////////////////////////////////////

template<typename F, typename ...T, int ...I>
auto apply_help(F f, std::tuple<T...> t, IntList<I...> a)
    -> decltype(f(std::get<I>(t) ...))
{
    return f(std::get<I>(t) ...);
}

template<typename F, typename ...T>
auto apply(F f, std::tuple<T...>t)
    -> typename std::result_of<F(T...)>::type
{
    using List = typename Generate<sizeof...(T)>::type;
    static List const a;
    return apply_help(f,t,a);
}

//////////////////////////////////////////////////////////////////

using namespace std;
int main()
{
    auto f = [](int x, double y, double z) { return x + y + z; };
    auto t = std::make_tuple(30, 5.0, 1.6);     // std::tuple<int, double, double>
    auto res = apply(f, t);                     // res = 36.6

    cout << "res = " << res << endl;
    return 0;
}







