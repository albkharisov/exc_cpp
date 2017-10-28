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


// ¬есь вывод должен осуществл€тьс€ в поток out,
// переданный в качестве параметра.
//
// ћожно заводить любые вспомогательные функции,
// структуры или даже измен€ть сигнатуру flatten,
// но при этом все примеры вызова из задани€ должны
// компилироватьс€ и работать.

template <typename T>
void flatten(const Array<T>& array, std::ostream& out)
{
    for (int i = 0; i < array.size(); ++i)
    {
        out << array[i] << " ";
    }
}

template <typename T>
void flatten(const Array< Array <T> >& array, std::ostream& out)
{
    for (int i = 0; i < array.size(); ++i)
    {
        flatten(array[i], out);
    }
}

int main()
{
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout); // выводит на экран строку "10 20"

    cout << endl << "===========" << endl;
    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"

    cout << endl << "===========" << endl;
    Array<double> doubles(10, 0.0);
    flatten(doubles, std::cout); // работать должно не только дл€ типа int


    cout << endl << "===========" << endl;
    return 0;
}
