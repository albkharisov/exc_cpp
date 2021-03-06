#include <iostream>
#include <typeinfo>

template <int... I> struct IntList;
template <int H, int... I> struct IntList<H, I...> { static int const Head = H; using Tail = IntList<I...>; };
template <>
struct IntList<> { };
template<typename T>
void check() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

//////////////////////////////////////////////////////////////////

using namespace std;

// бинарная метафункция
#if 0
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

template<typename TL1, typename TL2, template<int, int> class F>
struct Zip2;

template<int... I, int... J, template<int, int> class F>
struct Zip2<Quantity<IntList<I...>>, Quantity<IntList<J...>>, F>
{
    using type = Quantity<IntList<F<I, J>>::value...>;
};
#endif  // 0

////////////////////////////////////////////////////////////////////////

template<typename TL1, typename TL2, template<int, int> class F>
struct Zip;

template<int... I, int... J, template<int, int> class F>
struct Zip<IntList<I...>, IntList<J...>, F>
{
    using type = IntList<F<I, J>::value...>;
};

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
    using typeIntList = IntList<i1,i2,i3,i4,i5,i6,i7>;

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

    template<int j1, int j2, int j3, int j4, int j5, int j6, int j7>
    auto operator *(Quantity<IntList<j1,j2,j3,j4,j5,j6,j7>> bb)
        -> typename Quantity<typename Zip<typeIntList, IntList<j1,j2,j3,j4,j5,j6,j7>, Plus>::type>::type
    {
        using TYPE = typename Zip<typeIntList, IntList<j1,j2,j3,j4,j5,j6,j7>, Plus>::type;
        Quantity<TYPE> k(dbl * bb.dbl);
        return k;
    }

    template<int j1, int j2, int j3, int j4, int j5, int j6, int j7>
    auto operator /(Quantity<IntList<j1,j2,j3,j4,j5,j6,j7>> bb)
        -> typename Quantity<typename Zip<typeIntList, IntList<j1,j2,j3,j4,j5,j6,j7>, Minus>::type>::type
    {
        using TYPE = typename Zip<typeIntList, IntList<j1,j2,j3,j4,j5,j6,j7>, Minus>::type;
        Quantity<TYPE> k(dbl / bb.dbl);
        return k;
    }

    Quantity() : dbl(0) {}
    explicit Quantity(double dbl) : dbl(dbl) {}
    double value () const { return dbl; }
    double dbl;
};

#if 0
template<typename A>
auto operator *(double a, A b) -> decltype(operator *(Quantity<Dimension<>>(a), b))
{
    Quantity<> c(a);
    return c * b;
}
template<typename A>
auto operator *(A a, double b) -> decltype(operator *(a, Quantity<Dimension<>>(b)))
{
    Quantity<> c(b);
    return a * b;
}
template<typename A>
auto operator /(double a, A b) -> decltype(operator /(Quantity<Dimension<>>(a), b))
{
    Quantity<> c(a);
    return c / b;
}
template<typename A>
auto operator /(A a, double b) -> decltype(operator /(Quantity<Dimension<>>(b), a))
{
    Quantity<> c(b);
    return a / c;
}
#else
template<int ...I>
auto operator *(double a, Quantity<IntList<I...>> b)
        -> typename Quantity<typename Zip<Dimension<>, IntList<I...>, Plus>::type>::type
{
    Quantity<> c(a);
    return c * b;
}
template<int ...I>
auto operator *(Quantity<IntList<I...>> a, double b)
        -> typename Quantity<typename Zip<IntList<I...>, Dimension<>, Plus>::type>::type
{
    Quantity<> c(b);
    return a * c;
}
template<int ...I>
auto operator /(double a, Quantity<IntList<I...>> b)
        -> typename Quantity<typename Zip<Dimension<>, IntList<I...>, Minus>::type>::type
{
    Quantity<> c(a);
    return c / b;
}
template<int ...I>
auto operator /(Quantity<IntList<I...>> a, double b)
        -> typename Quantity<typename Zip<IntList<I...>, Dimension<>, Minus>::type>::type
{
    Quantity<> c(b);
    return a / c;
}
#endif



////////////////////////////////////////////////////////////////////////

using NumberQ   = Quantity<Dimension<>>;           // число без размерности
using LengthQ   = Quantity<Dimension<1>>;          // метры
using MassQ     = Quantity<Dimension<0, 1>>;       // килограммы
using TimeQ     = Quantity<Dimension<0, 0, 1>>;    // секунды
using VelocityQ = Quantity<Dimension<1, 0, -1>>;   // метры в секунду
using AccelQ    = Quantity<Dimension<1, 0, -2>>;   // ускорение, метры в секунду в квадрате
using ForceQ    = Quantity<Dimension<1, 1, -2>>;   // сила в ньютонах






using namespace std;

template<typename T>
void print(T a, char const * str) { cout << str << "=" << a.dbl << "      "; check<T>(); }
#define PRINT(x)        do {print(x, #x);} while(0)

int main()
{
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
    MassQ m5{5};

    auto m6 = m5 / m4;
    auto m7 = m5;
    PRINT(m4);
    PRINT(m5);
    print(m6, "m5 / m4");
    PRINT(m7);

    auto m8(m6);
    PRINT(m8);

    auto p = d1 * m4;
    auto q = m4 * d1;
    auto z = m4 * m4;
    auto l = m4 * m5;


    auto const c = 1.0 / LengthQ(1) / MassQ(1 + 1 / 2) / 5.0;
    cout << c.value() << endl;

    PRINT(c);

/*

no match for 'operator*' (
    operand types are 'Quantity<IntList<1, 0, 0, 0, 0, 0, 0> >::type {aka Quantity<IntList<1, 0, 0, 0, 0, 0, 0> >}'
                  and 'MassQ                                         {aka Quantity<IntList<0, 1, 0, 0, 0, 0, 0> >}')|




*/

    return 0;
}
