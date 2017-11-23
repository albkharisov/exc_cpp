#include <iostream>
#include <utility> // std::declval
#include <type_traits>


// внутри do_math объекты типа T
// - копируются
// - присваиваются
// - складываются оператором +
template<class T>
void do_math()
    noexcept(
        noexcept(std::declval<T>() + std::declval<T>()) &&
        std::is_nothrow_copy_constructible<T>::value &&
        std::is_nothrow_copy_assignable<T>::value &&
        std::is_nothrow_move_constructible<T>::value &&
        std::is_nothrow_move_assignable<T>::value
    )
{
    // тело функции нужно оставить пустым
}


using namespace std;

class myclass
{
    foo() noexcept
    {
        ++cnt;
    }

public:
    int cnt;
};



int main()
{
    bool b1 = noexcept(do_math<int>()); // true
    bool b2 = noexcept(do_math<std::string>()); // false

    cout << "b1 = " << b1 << endl;
    cout << "b2 = " << b2 << endl;
    return 0;
}
