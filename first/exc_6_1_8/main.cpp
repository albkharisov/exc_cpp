#include <iostream>

using namespace std;

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

struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

// Ўаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// ¬ шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Ўаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.


/**                   const T& value = T()     */
template <typename T>
struct ValueHolder : ICloneable
{
    ValueHolder(const T& value = T())
                : data_(value)
    {}

    ValueHolder* clone() const
    {
//        void* a;
//        a = operator new (sizeof(T));
//        new (a) T(data_);
//        return (T *) a;
        return new ValueHolder(data_);
    }
    T data_;
};




int main()
{
    ValueHolder<obj> vh1(3);
    ValueHolder<obj> * vh2 = vh1.clone();
    cout << "vh1=" << vh1.data_.a << endl;
    cout << "vh2=" << vh2->data_.a << endl;
    return 0;
}



