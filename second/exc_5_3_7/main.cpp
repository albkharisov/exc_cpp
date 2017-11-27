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


using namespace std;

int main()
{
#if 0
    using primes = IntList<2,3,5,7,11,13>;
#else
    using primes = IntList<5>;
#endif
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;

    return 0;
}
