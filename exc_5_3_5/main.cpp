#include <iostream>

using namespace std;

#include <iostream>

using namespace std;

struct Expression;
struct Number;
struct BinaryOperation;

struct Expression
{
    int a;
};

struct Number : Expression
{
    int b;
};

struct BinaryOperation : Expression
{
    int c;
};

struct ScopedPtr
{
     explicit ScopedPtr(Expression *ptr = 0)
     {
         if (ptr == 0)
            ptr_ = new Expression;
         else
            ptr_ = ptr;
     }

     ~ScopedPtr()
     {
         if (ptr_ != 0)
            delete ptr_;
     }

     Expression* get() const
     {
         return ptr_;
     }

     Expression* release()
     {
         Expression *ptr_tmp = ptr_;
         ptr_ = 0;
         return ptr_tmp;
     }

     void reset(Expression *ptr = 0)
     {
         delete ptr_;
         if (ptr != 0)
            ptr_ = ptr;
         else
            ptr_ = new Expression;
     }

     Expression& operator*() const
     {
         return *ptr_;
     }

     Expression* operator->() const
     {
         return ptr_;
     }

private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};





int main()
{
    cout << "Hello world!" << endl;

    ScopedPtr p;

    p->a = 17;

    cout << p->a << endl;

    return 0;
}









int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
