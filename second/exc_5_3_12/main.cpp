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

//////////////////////////////////////////////////////////////////

template<int H, typename TL>
struct IntCons;

template<int H, int... Ints>
struct IntCons<H, IntList<Ints...>>
{
    using type = IntList<H, Ints...>;
};

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

//////////////////////////////////////////////////////////////////

template<typename T>
void check()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

using namespace std;

int main()
{
#if 0
    using primes = IntList<2,3,5,7,11,13>;
    using primes2 = IntList<5>;
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;
#endif

    using L1 = IntList<2,3,4>;
    using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>
    using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>

    check<L3>();

    return 0;
}
