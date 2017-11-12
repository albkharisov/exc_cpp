#include <iostream>

using namespace std;

struct String
{
/*
    String & operator=(String && str)
    {
        cout << "oper &&" << endl;
    }

    String & operator=(const String & str)
    {
        cout << "oper &" << endl;
    }
*/
    String(String && str)
    {
        cout << "constr &&" << endl;
    }

    String(String const & str)
    {
        cout << "constr &" << endl;
    }

    String(void) /*: ptr(0), len(0)*/
    {
        cout << "constr" << endl;
    }

    ~String(void) /*: ptr(0), len(0)*/
    {
//        cout << "destr" << endl;
    }

    void * ptr;
    int len;
};


String & fun1(String & s)
{
    cout << __FUNCTION__ << ":";
    return s;
}

String && fun2(String & s)
{
    cout << __FUNCTION__ << ":";
    return std::move(s);
}

String fun3(String & s)
{
    cout << __FUNCTION__ << ":";
    return std::move(s);
}

String fun4(String s)
{
    cout << __FUNCTION__ << ":";
    return std::move(s);
}

String fun5(String s)
{
    cout << __FUNCTION__ << ":";
    return std::forward<String>(s);
}

String && fun6(String && s)
{
    cout << __FUNCTION__ << ":";
    return std::move(s);
}

String fun7(String && s)
{
    cout << __FUNCTION__ << ":";
    return s;
}


int main()
{
    String s;

cout << "======" << endl;

    fun1(s);
//    fun1(&s);
//    fun1(String());
cout << "======" << endl;

    fun2(s);
//    fun2(&s);
//    fun2(String());
cout << "======" << endl;

    fun3(s);
//    fun3(&s);
//    fun3(String());
cout << "======" << endl;

    fun4(s);
//    fun4(&s);
    fun4(String());
cout << "======" << endl;

    fun5(s);
    fun5(String());
//    fun5(&s);
cout << "======" << endl;

//    fun6(s);
//    fun6(&s);
    fun6(String());
cout << "======" << endl;

//    fun7(s);
//    fun7(&s);
    fun7(String());

cout << "======" << endl;


cout << "======" << endl;


    return 0;
}
