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

struct SharedPtr
{
    explicit SharedPtr(Expression *ptr = 0) : pc(1)
    {
        if (ptr == 0)
            pc = 0;
        else
            ptr_ = ptr;
    }

    ~SharedPtr()
    {
        if (ptr_ != 0)
        {
            if (--pc)
            {
                delete ptr_;
                ptr_ = 0;
            }
        }
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

    // !!!! A lot of to think about !!!!
    void reset(Expression *ptr = 0)
    {
        delete ptr_;
        --pc;
        if (ptr != 0)
            ptr_ = ptr;
        else
            ptr_ = new Expression;
        pc = 1;
    }

    Expression& operator*() const
    {
        return *ptr_;
    }

    Expression* operator->() const
    {
        return ptr_;
    }
//----------------------------------------
#if 0
    String(const String &other) : size(other.size), str(new char[other.size+1])
    {
        str[size] = 0;
        memcpy(str, other.str, size);
    }
#endif

    SharedPtr(const other&) : ptr_(other.ptr_), pc(other.pc)
    {
        if (ptr_)
            ++pc;
    }

//----------------------------------------
#if 0
	String &operator=(const String &other)
    {
	    if (this != &other)
        {
            delete [] str;
            size = other.size;
            str = new char [size+1];
            str[size] = 0;
            memcpy(str, other.str, size);
        }
        return *this;
    }
#endif
    SharedPtr& operator=(const other&)
    {
	    if (this != &other)
        {
            ++other.pc;
            --this.pc;
            this.pc = other.pc;
            this.ptr_ = other.ptr_;
        }
        return *this;
    }

    Expression *ptr_;

private:
    struct pc
    {
        pc(int cnt = 1)
        {
            cnt_ = new int;
            *cnt_ = cnt;
        }

        ~pc()
        {
            if (cnt_)
                delete cnt_;
        }

        int operator++(void)
        {
            return ++pc.cnt_;
        }

        int operator--(void)
        {
            return --pc.cnt_;
        }

        explicit pc& operator=(int cnt)
        {
            this->cnt_ = cnt;
        }

    private:
        int *cnt_;
    }
};





int main()
{
    cout << "Hello world!" << endl;

    SharedPtr p;

    p->a = 17;

    cout << p->a << endl;

    return 0;
}


