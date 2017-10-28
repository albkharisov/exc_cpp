#include <iostream>

using namespace std;

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0,
                   const T& value = T())
                    : mas (new T[size]), sz(size)
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            mas[i] = value;
        }
    }

    Array(const Array & other)
            : mas (new T[other.sz]), sz(other.sz)
    {
//        sz = other.sz;
//        mas = new Array[sz];
        for (unsigned int i = 0; i < sz; ++i)
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

bool less1(int a, int b);
bool less1(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const { return b < a; } };

template <typename var_t, class func_t>
var_t minimum(Array<var_t> arr, func_t func)
{
    int ind = 0;
    for (unsigned int i = 0; i < arr.size(); ++i)
    {
        if (func(arr[i], arr[ind]))
            ind = i;
    }

    return arr[ind];
}

int main()
{
    Array<int> ints(3);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    int min = minimum(ints, less1); // в min должно попасть число 2
    int max = minimum(ints, Greater()); // в max должно попасть число 15

    cout << "min=" << min << endl;
    cout << "max=" << max << endl;
    return 0;
}


