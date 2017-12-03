#include <iostream>
#include <string>

typedef char YES;
struct NO { YES m[2]; };

template <class T>
struct is_foo_defined
{
    template<class Z, size_t (Z::*)() const = &Z::size>
    struct wrapper{};


    template <class C>
    static YES check(wrapper<C> * p);

    template <class C>
    static NO check(...);

    static bool const value =
        sizeof(YES) == sizeof(check<T>(0));
};


template<class T, class E = void>
size_t get_size();


template<class T>
size_t get_size
<T, typename std::enable_if<is_foo_defined<T>::value, T>::type>
(T a)
{
    std::cout << "get_size1" << std::endl;
    return 15;
}

struct Struct
{
    size_t size1 = 0;
//    size_t size() const { return 17; }
};

using namespace std;
int main()
{
    /*
    std::string s{"Hello"};
    size_t s_size = get_size(s);   // 5, вызывается метод size()
*/


    cout << "is_foo_defined<std::string> = " << is_foo_defined<std::string>::value << endl;
    cout << "is_foo_defined<Struct> = " << is_foo_defined<Struct>::value << endl;



#if 0
    string s("hello");
    s.size();
    Struct x;
    x.size1 = 10;
    size_t x_size = get_size(x);  // 10, читается поле size
    auto s_size =  get_size(s);
    cout << s_size << endl;
    cout << x_size << endl;
    return 0;
#endif // 0
}
