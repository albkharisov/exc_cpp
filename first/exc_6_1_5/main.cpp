#include <iostream>
using namespace std;

#include <cstddef>

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0,
                   const T& value = T())
                    : mas (new T[size]), sz(size)
    {
        for (int i = 0; i < size; ++i)
        {
            mas[i] = value;
        }
    }

    Array(const Array & other)
            : mas (new T[other.sz]), sz(other.sz)
    {
//        sz = other.sz;
//        mas = new Array[sz];
        for (int i = 0; i < sz; ++i)
        {
            mas[i] = other.mas[i];
        }
    }

    ~Array()
    {
        delete[] mas;
    }

    Array& operator=(const Array & other)
    {
        if (!(*this == other))
        {
            delete[] mas;
            sz = other.sz;
            mas = new T[other.sz];
            for (int i = 0; i < sz; ++i)
            {
                mas[i] = other.mas[i];
            }
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

//private:
    T *mas;
    size_t sz;
};

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
//    obj& operator=(const obj & other) { return *this; }
};
int obj::cnt;

int main()
{
    Array<obj> a(15, 7);
    a[1] = 15;
    for (int i = 0; i < 15 ; ++i)
    {
        cout << a[i].a << endl;
    }
    return 0;
}






