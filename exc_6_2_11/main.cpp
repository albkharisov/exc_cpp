#include <iostream>
#include  <string>

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

//private:
    obj& operator=(const obj & other)
    {
        a = other.a;
        ++cnt;
        return *this;
    }
};
int obj::cnt;

#include "stdio.h"
#include "string.h"
class obj2
{
public:
    obj2(const char * str)
    {
        cout << "DBG: " << "obj2:constructor(" << str << "), cnt=" << ++cnt << endl;
        int sz_l = strlen(str);
        sz = sz_l;
        ptr = new char(sz+1);
        memcpy(ptr, str, sz+1);
    }
    ~obj2()
    {
        cout << "DBG: " << "obj2:destructor(" << ptr << "), cnt=" << --cnt << endl;
        delete ptr;
    }
    char *ptr;
    int sz;
    static int cnt;

//    static int cnt;
    obj2(const obj2 & other)
        : sz(other.sz)
    {
        cout << "DBG: " << "obj2:constructor_copy(" << other.ptr << "), cnt=" << ++cnt << endl;
        int sz_l = strlen(other.ptr);
        sz = sz_l;
        ptr = new char(sz+1);
        memcpy(ptr, other.ptr, sz+1);
    }

//private:
    obj2& operator=(const obj2 & other)
    {
        int sz_l = strlen(other.ptr);
        sz = sz_l;
        ptr = new char(sz+1);
        memcpy(ptr, other.ptr, sz+1);
        ++cnt;
        return *this;
    }
};
int obj2::cnt;

struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

template <typename T>
struct ValueHolder : ICloneable
{
    ValueHolder(const T& value = T())
                : data_(value)
    {}

    ValueHolder* clone() const
    {
        return new ValueHolder(data_);
    }
    T data_;
};

struct ValueHolder2 : ICloneable
{
    ValueHolder2(const int& vi)
                : i(vi)
    {}

    ValueHolder2* clone() const
    {
        cout << "vh2" << endl;
        return new ValueHolder2(i);
    }
    int i;
};

struct ValueHolder3 : ICloneable
{
    ValueHolder3(const int& vi)
                : i(vi)
    {}

    ValueHolder3* clone() const
    {
        cout << "vh3" << endl;
        return new ValueHolder3(i);
    }
    int i;
};

class Any
{
    ICloneable *pvh;
public:
    /**
     ¬ классе Any должен быть конструктор,
     который можно вызвать без параметров,
     чтобы работал следующий код:
        Any empty; // empty ничего не хранит
    */
    Any () : pvh(0) {}

    /**
     ¬ классе Any должен быть шаблонный
     конструктор от одного параметра, чтобы
     можно было создавать объекты типа Any,
     например, следующим образом:
        Any i(10); // i хранит значение 10
    */

    template <typename T1>
    Any (const T1& t) : pvh(new ValueHolder<T1> (t)) {}

    /**
     Ќе забудьте про деструктор. ¬се выделенные
     ресурсы нужно освободить.
     */

    ~Any ()
    {
        if (pvh)
        {
            delete pvh;
            pvh = 0;
        }
    }

    /**
     ¬ классе Any также должен быть конструктор
     копировани€ (вам поможет метод clone
     интерфейса ICloneable)
     */

    Any (const Any& other)
    {
        if (other.pvh)
            this->pvh = other.pvh->clone();
        else
            this->pvh = 0;
    }

    /**
     ¬ классе должен быть оператор присваивани€ и/или
     шаблонный оператор присваивани€, чтобы работал
     следующий код:
        Any copy(i); // copy хранит 10, как и i
        empty = copy; // empty хранит 10, как и copy
        empty = 0; // а теперь empty хранит 0
    */
    Any& operator=(const Any & other)
    {
        if (this != &other)
        {
            if (pvh)
            {
                delete pvh;
                pvh = 0;
            }

            if (other.pvh)
                this->pvh = other.pvh->clone();
            else
                this->pvh = 0;
        }
        return *this;
    }

    /**
     Ќу и наконец, мы хотим уметь получать хранимое
     значение, дл€ этого определите в классе Any
     шаблонный метод cast, который возвращает
     указатель на хранимое значение, или нулевой
     указатель в случае несоответстви€ типов или
     если объект Any ничего не хранит:
        int *iptr = i.cast<int>(); // *iptr == 10
        char *cptr = i.cast<char>(); // cptr == 0,
            // потому что i хранит int, а не char
        Any empty2;
        int *p = empty2.cast<int>(); // p == 0
     ѕри реализации используйте оператор dynamic_cast.

     ƒопустим у вас есть два наследника класса Base: Derived1
     и Derived2.  роме того у вас есть указать baseptr
     типа Base*.  ак проверить указывает ли этот указатель на
     самом деле на объект класса Derived1 или на объект
     класса Derived2? ƒл€ этого можно воспользоватьс€ dynamic_cast-ом:

     Derived1 *derived1ptr = dynamic_cast<Derived1*>(baseptr);

     ≈сли derived1ptr не равен 0, то  baseptr на самом деле
     указывал на объект класса Derived1, если же derivedptr равен 0,
     то baseptr на самом деле указывал на объкт какого-то другого
     класса (например, Derived2). Ёто можно проверить так:

     Derived2 *derived2ptr = dynamic_cast<Derived2*>(baseptr);

     dynamic_cast работает только, если в классе есть хот€ бы
     один виртуальный метод, и в шаблоне ValueHolder такой
     как раз имеетс€.
     */
    template <typename T2>
    T2 * cast()
    {
        ValueHolder<T2> *pt = dynamic_cast<ValueHolder<T2> *> (pvh);
        if (!pt)
            return 0;
        else
            return &pt->data_;
    }
};

/*** T E S T S ***/

void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();

void test0()
{
	struct X
	{
		ICloneable *p;
	};
	cout << endl << "***** Empty ***" << " (" << __FUNCTION__ << ")" << endl;
	Any aEmpty(NULL);
	cout << *aEmpty.cast<int>() << endl;
	Any bEmpty;
	if (((X*)&bEmpty)->p == NULL) {
		cout << "Empty: OK";
	}
	else
	{
		cout << "Empty: Failed" << endl;
	}
	cout << endl;
	if (bEmpty.cast<string>()) { cout << *bEmpty.cast<string>() << endl; }

    cout << "Empty: Done" << endl;

	Any  cEmpty;
	bEmpty = cEmpty;
	cout << "Address: " << &bEmpty << " Pointer value: " << (((X*)&bEmpty)->p) << endl;
}
void test1()
{
	cout << endl << "***** INT (Self = Self ) ***" << " (" << __FUNCTION__ << ")" << endl;
	int INT = 1;
	Any aINT(INT);
	cout << *aINT.cast<int>() << " == " << INT << endl;
	aINT = aINT;
	cout << *aINT.cast<int>() << " == " << INT << endl;
}
void test2()
{
	cout << endl << "***** INT (Copy ) ***" << " (" << __FUNCTION__ << ")" << endl;
	int INT = 2;
	Any aINT(INT);
	cout << *aINT.cast<int>() << " == " << INT << endl;;
	Any nEmpy(aINT);
	cout << *nEmpy.cast<int>() << " == " << INT << endl;


}

void test3()
{
	cout << endl << "***** INT (Empty, =, copy, cast) ***" << " (" << __FUNCTION__ << ")" << endl;
	int INT = 10;
	{
		Any aINT(INT);
		cout << *aINT.cast<int>() << " == " << INT ;
	}
	cout << endl;
	{
		Any aINT(INT);
		Any aEmpty;
		aEmpty = aINT;
		int tmp = *aEmpty.cast<int>();
		cout << tmp << " == " << INT ;
	}
	cout << endl;
	{
		Any aINT(INT);
		Any aEmpty;
		aEmpty = aINT;
		aEmpty = aEmpty;
		cout << *aEmpty.cast<int>() << " == " << INT ;
	}
	cout << endl;
	{
		Any aEmpty;
		aEmpty = 0;
		cout << *aEmpty.cast<int>() << " == " << 0 ;
	}
	cout << endl;
	{
		struct X
		{
			ICloneable *p;
		};
		Any aEmpty;
		Any bEmpty(aEmpty);
		if (((X*)&bEmpty)->p == NULL) {
			cout << "Empty: OK";
		}
		else
		{
			cout << "Empty: Failed" << endl;
		}
	}
	cout << endl;
	return;
}

void test4()

{
	string  STR("Hello!");
	cout << endl << "***** STRING (empty, =, copy, cast) ***" << " (" << __FUNCTION__ << ")" << endl;
	{

		Any aINT(STR);
		cout << *aINT.cast<string>() << " == " << STR ;
	}
	cout << endl;
	{
		Any aINT(STR);
		Any aEmpty;
		aEmpty = aINT;
		cout << *aEmpty.cast<string>() << " == " << STR << endl;
	}
	cout << endl;
	{
		string sEmpty("");
		Any aEmpty(sEmpty);
		aEmpty = aEmpty;
		cout << *aEmpty.cast<string>() << " == " << STR << endl;
		aEmpty = aEmpty;
		cout << *aEmpty.cast<string>() << " == " << STR << endl;
		Any nEmpty(aEmpty);
		cout << *nEmpty.cast<string>() << " == " << STR << endl;
	}
	cout << endl;
	{
		int i = 10;
		ValueHolder<int>* intHolder = new ValueHolder<int>(i);
		ValueHolder<char>* charHolder = dynamic_cast<ValueHolder<char>*>(intHolder->clone());
		ValueHolder<int>* int2Holder = dynamic_cast<ValueHolder<int>*>(intHolder->clone());
		cout << "Char* 4 Int* " << (charHolder ? "Cast: OK" : "Cast: Failed") << endl;
		cout << "Int* 4 Int*" << (int2Holder ? "Cast: OK" : "Cast: Failed") ;
		delete intHolder;
		delete charHolder;
		delete int2Holder;
	}
	cout << endl;
}
void test5()
{
	cout << endl << "*** INT, DOUBLE, STRING ***" << " (" << __FUNCTION__ << ")" << endl;
	string Hello = "Hello World People";
	ValueHolder<int> Int(10);
	ValueHolder<string> Str(Hello);
	double Dbl = 10.112233;

	Any aHello(Hello);
	Any aInt(Int);
	Any aStr(Str);
	Any aDbl(Dbl);

	cout << aHello.cast<string>()->data() << " == " << Hello.data() << endl;
	cout << aInt.cast<ValueHolder<int> >()->data_ << " == " << Int.data_ << endl;
	cout << aStr.cast<ValueHolder<string> >()->data_.data() << " == " << Hello.data() << endl;
	cout << *aDbl.cast<double>() << " == " << Dbl << endl;

	aHello = (char*)"Any other simple text";
	aInt = 10241;
	aDbl = 234.5675;

	cout << *aHello.cast<char *>() << " == " << "Any other simple text" << endl;
	cout << *aInt.cast<int>() << " == " << 10241 << endl;
	cout << *aDbl.cast<double>() << " == " << 234.5675 << endl;
}
void test6()
{
	// Memory leak!!!
	cout << endl << "*** Array (= new Any(i))***" << " (" << __FUNCTION__ << ")" << endl;
	int n = 5;
	{
		Any *pAny = new Any[n];
		for (int i = 0; i < n; i++)
			pAny[i] = new Any(i*i + 1);

		for (int i = 0; i < n; i++)
			cout << "\tpAny[" << i << "] = " << *(*pAny[i].cast<Any*>())->cast<int>() << " == " << i*i + 1 << endl;
		delete[] pAny;
	}
	cout << endl;
}

void test7()
{
	cout << endl << "*** Array (= Any(i))***" << " (" << __FUNCTION__ << ")" << endl;
	const int n = 30;
	Any pAny2[n];

	for (int i = 0; i < n; i++)
		pAny2[i] = Any(i + 1);

	for (int i = 0; i < n; i++)
		cout << "\tpAny2[" << i << "] = " << *pAny2[i].cast<int>() << " == " << i + 1 << endl;
}

void my_func(Any a);
int main()
{
#if 0
    Any a(10);
    int *paInt = a.cast<int>();
    Any b((char)45);
    cout << "a = " << *paInt << endl;
    char *pbChr = b.cast<char>();
    cout << "b = " << (int)(*pbChr) << endl;

    obj objA(15);
    Any c(objA);
    obj *pcobj = c.cast<obj>();
    cout << "c = " << pcobj->a << endl;

    c = b;
    char *pcChr = c.cast<char>();
    cout << "c = " << (int)*pcChr << endl;

    Any d(10);
    int *pdInt = d.cast<int>();
    cout << "d = " << *pdInt << endl;
    Any e(d);
    int *peInt = e.cast<int>();
    cout << "e = " << *peInt << endl;
    Any f((long long) 30);
    f = e;
//    long long *pfLL = f.cast<long long>();
    int *pfLL = f.cast<int>();
    if (pfLL)
        cout << "f = " << *pfLL << endl;
    else
        cout << "f = NULL" << endl;

//    obj objB = 5;
//    Any c1(objB);
    Any c1;
    c1 = c;
    obj *pc1obj = c1.cast<obj>();
    cout << "c1 = " << (pc1obj->a) << endl;



#elif 0


	test0();
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();

#else

//    obj oA(17);
//	Any aEmpty(oA);
////	Any bEmpty = aEmpty;
//
////    my_func(aEmpty);
//
//
//    obj2 o2("test1");
//    obj2 o21("test2");
//    cout << "str(" << o2.sz << ") \"" << o2.ptr << "\"" << endl;
//    cout << "==================" << endl;
//    Any a(o2);
//    Any b(o21);
//    cout << "==================" << endl;
//    cout << "a:" << a.cast<obj2>()->ptr << endl;
//    cout << "==================" << endl;
//    cout << "b:" << b.cast<obj2>()->ptr << endl;
//    cout << "==================" << endl;
//
//    b = a;
//    b = aEmpty;
//    Any c = aEmpty;
//    cout << "==================" << endl;
//    cout << "a:" << a.cast<obj2>()->ptr << endl;
//    cout << "==================" << endl;
////    cout << "b:" << b.cast<obj2>()->ptr << endl;
//    cout << "b:" << b.cast<obj>()->a << endl;
//    cout << "==================" << endl;
//    cout << "c:" << c.cast<obj>()->a << endl;
//    cout << "==================" << endl;

    ValueHolder2 vh2(102);
    ValueHolder3 vh3(103);

    Any a2(vh2);
    Any a3(vh3);

    ValueHolder3 * pa3 = a3.cast<ValueHolder3>();

    a2 = a3;
//    ValueHolder2 * pa2 = a2.cast<ValueHolder2>();
    ValueHolder3 * pa2 = a2.cast<ValueHolder3>();

    if (pa2)
        cout << "*pa2=" << pa2->i << endl;
    else
        cout << "pa2==NULL" << endl;

    if (pa3)
        cout << "*pa3=" << pa3->i << endl;
    else
        cout << "pa3==NULL" << endl;


    cout << "=======================" << endl;

#endif

    return 0;
}

void my_func(Any a)
{
//    Any b;
//    b = a;
}


