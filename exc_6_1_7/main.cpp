#include <iostream>
using namespace std;

#include <cstddef>
#include <stdlib.h>

class obj
{
public:
    obj(int i = 88) : a(i)
    {
        cout << "DBG: " << "obj:constructor(" << a << "), cnt=" << ++cnt << endl;
    }
    ~obj()
    {
        cout << "DBG: " << "obj:destructor(" << a << "), cnt=" << --cnt << endl;
    }
    int a;

    static void resetcnt(void)
    {
        cnt = 0;
    }

    static int cnt;
    obj(const obj & other)
        : a(other.a)
    {
        cout << "DBG: " << "obj:constructor_copy(" << a << "), cnt=" << ++cnt << endl;
    }

private:
    obj& operator=(const obj & other) { return *this; }
};
int obj::cnt;

//        mas = (T *) new char[sz * sizeof(T)];
//        mas = malloc(sz * sizeof(T));

#if 0
#define MY_MALLOC           ((T *) new char[sz * sizeof(T)])
#define MY_FREE(x)          (delete (x))
#elif 0
#define MY_MALLOC           ((T *) malloc(sz * sizeof(T)))
#define MY_FREE(x)          (free(x))
#else
#define MY_MALLOC           static_cast<T*>(operator new[](sz * sizeof(T)))
#define MY_FREE(x)          delete[] static_cast<char*>(static_cast<void*>(x))
#endif


template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0,
                   const T& value = T())
                    : sz(size)
    {
        cout << "DBG: " << "constructor (size=" << sz << ")" << endl;

        mas = MY_MALLOC;
        for (unsigned int i = 0; i < sz; ++i)
        {
            cout << "DBG: " << "i=" << i << endl;
            new ((void *)mas + i*sizeof(T)) T(value);
        }
    }

    Array(const Array & other)
            : sz(other.sz)
    {
        cout << "DBG: " << "constructor_copy (size=" << sz << ")" << endl;

        mas = MY_MALLOC;
        for (unsigned int i = 0; i < sz; ++i)
            new ((void *)mas + i*sizeof(T)) T(other.mas[i]);
    }

    ~Array()
    {
        cout << "DBG: " << "destructor (size=" << sz << ")" << endl;
        for (unsigned int i = 0; i < sz; ++i)
        {
            cout << "DBG: i=" << i << endl;
            mas[i].~T();
        }

        char *p = (char *) mas;
        MY_FREE(p);
    }

    Array& operator=(const Array & other)
    {
        if (!(*this == other))
        {
            cout << "DBG: " << "op=" << endl;
            this->~Array();

            sz = other.sz;

            mas = MY_MALLOC;

            for (unsigned int i = 0; i < sz; ++i)
                new ((void *)mas + i*sizeof(T)) T(other.mas[i]);
        }
        return *this;
    }

    bool operator==(const Array & other)
    {
        return ((mas == other.mas) && (sz == other.sz));
    }

    size_t size() const
    {
        return sz;
    }

    T& operator[](size_t n)
    {
        return mas[n];
    }

    const T& operator[](size_t n) const
    {
        return mas[n];
    }

    T *mas;
    size_t sz;
};

int main()
{
    obj::resetcnt();
    cout << "==============" << endl;
    obj o(5);
    cout << "==============" << endl;
    obj o2(3);
    cout << "==============" << endl;

    Array<obj> a(2, o);
    cout << "==============" << endl;
    Array<obj> a2(2, o2);
    cout << "==============" << endl;
    cout << "*************************" << endl;
//
    a[0].a = 1;
    a[1].a = 2;
    a2[0].a = 3;
    a2[1].a = 4;
//
    cout << "a[0]=" << a[0].a << endl;
    cout << "a[1]=" << a[1].a << endl;
    cout << "a2[0]=" << a2[0].a << endl;
    cout << "a2[1]=" << a2[1].a << endl;
    cout << "==============" << endl;
    a2 = a;
    cout << "==============" << endl;



    cout << "a[0]=" << a[0].a << endl;
    cout << "a[1]=" << a[1].a << endl;
    cout << "a2[0]=" << a2[0].a << endl;
    cout << "a2[1]=" << a2[1].a << endl;
    cout << "==============" << endl;
//    cout << "==============" << endl;

    a.~Array();
    cout << "==============" << endl;
    a2.~Array();
    o.~obj();
    o2.~obj();
    cout << "****************************" << endl;
    return 0;
}



