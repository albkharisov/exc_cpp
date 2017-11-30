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

template<typename T>
void check()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

using namespace std;

//////////////////////////////////////////////////////////////////

// бинарная метафункция
template<int a, int b>
struct Plus
{
    static int const value = a + b;
};

template<typename TL1, typename TL2, template<int, int> class F>
struct Zip;

template<int... I, int... J, template<int, int> class F>
struct Zip<IntList<I...>, IntList<J...>, F>
{
    using type = IntList<F<I, J>::value...>;
};

//////////////////////////////////////////////////////////////////

int main()
{

    // два списка одной длины
    using L1 = IntList<1,2,3,4,5>;
    using L2 = IntList<1,3,7,7,2>;

    // результат применения — список с поэлементными суммами
    using L3 = Zip<L1, L2, Plus>::type;  // IntList<2, 5, 10, 11, 7>

    check<L3>();
    return 0;
}



#if 0
    using primes = IntList<2,3,5,7,11,13>;
    using primes2 = IntList<5>;
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;

    using L1 = IntList<2,3,4>;
    using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>
    using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>

    check<L3>();
#endif


