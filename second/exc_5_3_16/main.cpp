#include <iostream>
#include <typeinfo>

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

template<typename T>
constexpr const char * check2()
{
    return __PRETTY_FUNCTION__;
}

using namespace std;

// бинарная метафункция
template<int a, int b>
struct Plus
{
    static int const value = a + b;
};

template<int a, int b>
struct Minus
{
    static int const value = a - b;
};

template<typename T = IntList<0,0,0,0,0,0,0>>
struct Quantity;

template<typename TL1, typename TL2, template<int, int> class F>
struct Zip2;

template<int... I, int... J, template<int, int> class F>
struct Zip2<IntList<I...>, IntList<J...>, F>
{
    using type = IntList<F<I, J>::value...>;
};

////////////////////////////////////////////////////////////////////////

template<typename TL1, typename TL2, template<int, int> class F>
struct Zip;

template<int... I, int... J, template<int, int> class F>
struct Zip<Quantity<IntList<I...>>, Quantity<IntList<J...>>, F>
{
    using type = Quantity<IntList<F<I, J>::value...>>;
};

////////////////////////////////////////////////////////////////////////

template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

////////////////////////////////////////////////////////////////////////

template<int a, int b>
struct Plus
{
    static int const value = a + b;
};

template<int a, int b>
struct Minus
{
    static int const value = a - b;
};

template<typename T = IntList<0,0,0,0,0,0,0>>
struct Quantity;

template<int i1, int i2, int i3, int i4, int i5, int i6, int i7>
struct Quantity<Dimension<i1,i2,i3,i4,i5,i6,i7>>
{
    using type = Quantity<IntList<i1,i2,i3,i4,i5,i6,i7>>;

    type operator +(type bb)
    {
        type k(dbl + bb.dbl);
        return k;
    }

    type operator -(type bb)
    {
        type k(dbl - bb.dbl);
        return k;
    }

    template<typename A>
    auto operator *(A bb) -> typename Zip<Quantity::type, A, Plus>::type
    {
        using TYPE = typename Zip<Quantity::type, A, Plus>::type;
        TYPE k(dbl * bb.dbl);
        return k;
    }

    template<typename A>
    auto operator /(A a) -> typename Zip<Quantity::type, A, Minus>::type
    {
        using TYPE = typename Zip<Quantity::type, A, Minus>::type;
        TYPE k(dbl / a.dbl);
        return k;
    }

    Quantity() : dbl(0) {}
    explicit Quantity(double dbl) : dbl(dbl) {}
    double value () { return dbl; }
    double dbl;
};


template<typename A>
auto operator *(double a, A b) -> typename Zip<A, Quantity<>::type, Plus>::type
{
    Quantity<> c(a);
    return c * b;
}

template<typename A>
auto operator *(A b, double a) -> typename Zip<A, Quantity<>::type, Plus>::type
{
    return a * b;
}

template<typename A>
auto operator /(double a, A b) -> typename Zip<A, Quantity<>::type, Minus>::type
{
    Quantity<> c(a);
    return c / b;
}

template<typename A>
auto operator /(A b, double a) -> typename Zip<A, Quantity<>::type, Minus>::type
{
    Quantity<> c(a);
    return b / c;
}








using namespace std;

template<typename T>
void print(T a, char const * str)
{
    cout << str << "=" << a.dbl << "      "; check<T>();
}

#define PRINT(x)        do {print(x, #x);} while(0)

int main()
{
    using NumberQ   = Quantity<Dimension<>>;           // число без размерности
    using LengthQ   = Quantity<Dimension<1>>;          // метры
    using MassQ     = Quantity<Dimension<0, 1>>;       // килограммы
    using TimeQ     = Quantity<Dimension<0, 0, 1>>;    // секунды
//    using VelocityQ = Quantity<Dimension<1, 0, -1>>;   // метры в секунду
//    using AccelQ    = Quantity<Dimension<1, 0, -2>>;   // ускорение, метры в секунду в квадрате
//    using ForceQ    = Quantity<Dimension<1, 1, -2>>;   // сила в ньютонах

#if 0
    LengthQ m1{5};
    TimeQ m2{10};
    auto m3 = m1 / m2;
    cout << "m1=" << m1.dbl << "      "; check<decltype(m1)>();
    cout << "m2=" << m2.dbl << "      "; check<decltype(m2)>();
    cout << "m3=" << m3.dbl << "      "; check<decltype(m3)>();
#endif  // 0

    double d1 = 2;
    LengthQ m4(d1);
    LengthQ m5{5};

    auto m6 = m5 * d1;
    auto m7 = m5 / d1;
    PRINT(m4);
    PRINT(m5);
    PRINT(m6);
    PRINT(m7);




/*

conversion from
'Zip<Quantity<IntList<0, 1, 0, 0, 0, 0, 0> >,
Quantity<IntList<1, 0, 0, 0, 0, 0, 0> >, Plus>::type {aka IntList<1, 1, 0, 0, 0, 0, 0>}'
to non-scalar type 'Quantity<IntList<1, 1, 0, 0, 0, 0, 0> >'


conversion from
'Zip<Quantity<IntList<0, 1, 0, 0, 0, 0, 0> >,
Quantity<IntList<1, 0, 0, 0, 0, 0, 0> >, Plus>::type {aka IntList<1, 1, 0, 0, 0, 0, 0>}'
to non-scalar type 'Quantity<IntList<1, 1, 0, 0, 0, 0, 0> >'




    TimeQ     t{10 * 60};    // 10 минут
    VelocityQ v = l / t;     // результат типа VelocityQ, 50 м/с

    AccelQ    a{9.8};        // ускорение свободного падения
    MassQ     m{80};         // 80 кг
    ForceQ    f = m * a;     // результат типа ForceQ
*/

//    using t = Quantity<Dimension<0,1,2,3>>;
//    check<t>();




    return 0;
}
