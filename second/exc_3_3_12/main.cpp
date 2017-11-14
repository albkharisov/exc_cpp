#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <map>
#include <functional>
#include <utility>
#include <utility>

using namespace std;



struct Shape
{
    virtual void method(void) = 0;

//    Shape() {}
    ~Shape() {}

//    int a;
};

struct Triangle : public Shape
{
    void method(void) // override
    {
        cout << "Trian_method" << endl;
    }

    ~Triangle(){}
    int b;
};

struct Rectangle : public Shape
{
    void method(void) // override
    {
        cout << "Rect_method" << endl;
    }

    ~Rectangle(){}
    int c;
};

void is_intersect_r_rv(Shape * r1, Shape *r2)
{
//    cout << __FUNCTION__ << endl;
    cout << "";
    return;
}

bool is_intersect_r_r(Shape * r1, Shape *r2)
{
//    cout << __FUNCTION__ << endl;
    cout << "";
    return true;
}

bool is_intersect_r_t(Shape * r1, Shape *t1)
{
//    cout << __FUNCTION__ << endl;
    cout << "";
    return true;
}

#if 0
        cout << __FUNCTION__ << endl;
        for (auto It = cont.begin(); It != cont.end(); ++It)
        {
            cout << It->first.first.name() << "  :  "
                 << It->first.second.name() << "  :  "
                 << It->second << endl;
        }
        cout << "find1: " << para.first.name() << " : " << para.second.name() << endl;
#endif  // 0

template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    typedef std::function<Result(Base*, Base*)> func_t;
    typedef std::pair<std::type_index, std::type_index> key_t;

    Multimethod2()
    {
        cont.clear();
    }

    void addImpl( std::type_index t1, std::type_index t2, func_t f )
    {
        key_t para = { t1, t2 };
        cont[para] = f;
    }

    bool hasImpl(Base * a, Base * b) const
    {
        key_t para = { std::type_index(typeid(*a)), std::type_index(typeid(*b)) };
        key_t para2 = { std::type_index(typeid(*b)), std::type_index(typeid(*a)) };

        return (cont.find(para) != cont.end())
                || (Commutative && (cont.find(para2) != cont.end()));
    }

    Result call(Base * a, Base * b)
    {
        key_t para = { std::type_index(typeid(*a)), std::type_index(typeid(*b)) };
        key_t para2 = { std::type_index(typeid(*b)), std::type_index(typeid(*a)) };

        if (cont.find(para) != cont.end())
            return cont[para](a, b);
        else if (Commutative && (cont.find(para2) != cont.end()))
            return cont[para2](b, a);
    }

    std::map<std::pair<std::type_index, std::type_index>, func_t> cont;
};

#define OK()            do { cout << "OK" << endl; } while(0)
#define FAILED()        do { cout << "FAILED" << endl; } while(0)
#define PREPARE(x)      do { cout << "TEST " << (x) << " : " ; } while(0)

void test1()
{
    cout << endl << __FUNCTION__ << ":" << endl;
    Shape * s1 = new Rectangle();
    Shape * s2 = new Triangle();

    Multimethod2<Shape, bool, true> is_intersect1;
    is_intersect1.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);
    is_intersect1.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // ==========
    PREPARE(__COUNTER__);
    if (is_intersect1.hasImpl(s2, s1))
    {
        OK();
        is_intersect1.call(s2, s1);
        is_intersect1.call(s1, s2);
    }
    else
    {
        FAILED();
        is_intersect1.call(s2, s1);
        is_intersect1.call(s1, s2);
    }
    // ==========
    PREPARE(__COUNTER__);
    if (is_intersect1.hasImpl(s1, s2))
    {
        OK();
        is_intersect1.call(s2, s1);
        is_intersect1.call(s1, s2);
    }
    else
    {
        FAILED();
        is_intersect1.call(s2, s1);
        is_intersect1.call(s1, s2);
    }
    // ==========
    PREPARE(__COUNTER__);
    if (is_intersect1.hasImpl(s1, s1))
    {
        OK();
        is_intersect1.call(s1, s1);
    }
    else
    {
        FAILED();
        is_intersect1.call(s1, s1);
    }
}

void test2()
{
    cout << endl << __FUNCTION__ << ":" << endl;
    Shape * s1 = new Rectangle();
    Shape * s2 = new Triangle();

    Multimethod2<Shape, bool, false> is_intersect1;
    is_intersect1.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);
    is_intersect1.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    PREPARE(__COUNTER__);
    if (is_intersect1.hasImpl(s2, s1))
    {
        FAILED();
        is_intersect1.call(s2, s1);
        is_intersect1.call(s1, s2);
    }
    else
    {
        OK();
        is_intersect1.call(s2, s1);
        is_intersect1.call(s1, s2);
    }
}


void test3()
{
    cout << endl << __FUNCTION__ << ":" << endl;
    Shape * s1 = new Triangle();
    Shape * s2 = new Rectangle();

    Multimethod2<Shape, void, false> is_intersect3;

    is_intersect3.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_rv);

    PREPARE(__COUNTER__);
    if (is_intersect3.hasImpl(s2, s2))
    {
        OK();
        is_intersect3.call(s2, s2);
    }
    else
        FAILED();
}


int main()
{
    test1();
    test2();
    test3();

    return 0;
}

