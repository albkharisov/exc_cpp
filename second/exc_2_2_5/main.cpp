#include <iostream>

using namespace std;

template<class T>
struct Array
{
    // все объявленные ниже методы уже реализованы
    explicit Array(size_t size = 0) : size_(size)
    {
        cout << "const 1" << endl;
        data_ = new T [size_];

        for (int i = 0; i < size_ ; ++i)
        {
            data_[i] = 0;
        }
    }

    explicit Array(const T & t, size_t size = 0) : size_(size)
    {
        cout << "const 2" << endl;
        data_ = new T [size_];

        for (int i = 0; i < size_ ; ++i)
        {
            data_[i] = t;
        }
    }

    Array(Array const& a) : size_(a.size_)
    {
        cout << "const copy" << endl;
        data_ = new T [a.size_];
        for (int i = 0 ; i < a.size_ ; ++i)
        {
            data_[i] = a.data_[i];
        }
    }

    Array & operator=(Array const& a)
    {
        cout << "oper copy" << endl;
        delete[] data_;
        data_ = new T [a.size_];

        for (int i = 0 ; i < a.size_ ; ++i)
        {
            data_[i] = a.data_[i];
        }
        size_ = a.size_;

        return *this;
    }

    ~Array()
    {
        cout << "destr" << endl;
        delete[] data_;
    }

    size_t size() const
    {
        return size_;
    }

    T & operator[](size_t i)
    {
        return data_[i];
    }

    T const & operator[](size_t i) const
    {
        return data_[i];
    }

    void swap_(Array & a)
    {
        std::swap(data_, a.data_);
        std::swap(size_, a.size_);
    }

    Array(Array && a) : Array()
    {
        swap_(a);
    }

    Array & operator=(Array && a)
    {
        swap_(a);
        return *this;
    }

private:
    size_t  size_;
    T *     data_;
};

template<typename T>
void print(T & arr)
{
    cout << arr[0] << "  :  " << arr[1] << "  :  " << arr[2] << "  :  " << arr[3] << endl;
}

Array<int> func(Array<int> arr)
{
    cout << "-----------------------" << endl;
    print(arr);
    cout << "-----------------------" << endl;
    arr[0] = arr[0] + 1;
    arr[1] = arr[1] + 1;
    return arr;
}

void func2(Array<int> & arr)
{
//    arr[2] = arr[0];
    Array<int> arr2(2, 3);
    arr = arr2;
}

int main()
{
    Array<int> arr1(1, 3);
    Array<int> arr2(8, 3);

    print(arr1);
    print(arr2);

    cout << "=====================" << endl;
    Array<int> arr3 = func(arr1);
    cout << "=====================" << endl;

    print(arr1);
    print(arr2);
    print(arr3);


    return 0;
}
