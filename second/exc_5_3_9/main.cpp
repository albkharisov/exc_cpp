#include <iostream>

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

//////

template <typename TL>
struct Length
{
    static int const value = 1 +
        Length<typename TL::Tail>::value;
};

template<>
struct Length<IntList<>>
{
    static int const value = 0;
};

//////

using namespace std;

int main()
{
#if 1
    using primes = IntList<2,3,5,13>;
#else
    using primes = IntList<5>;
#endif
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;

    std::cout << Length<primes>::value << std::endl;

    return 0;
}
