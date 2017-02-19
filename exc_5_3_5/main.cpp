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
    explicit SharedPtr(Expression *ptr = 0) : pci(ptr)
    {
    }

    ~SharedPtr()
    {
        cout << "destructor: ptr_=" << this->pci.ptr_;
        if (pci.ptr_ != 0)
        {
            if (--pci)
            {
                delete pci.ptr_;
                pci.ptr_ = 0;
            }
        }
    }

    Expression* get() const
    {
        return pci.ptr_;
    }

    Expression* release()
    {
        Expression *ptr_tmp = pci.ptr_;
        pci.ptr_ = 0;
        return ptr_tmp;
    }

    // !!!! A lot of to think about !!!!
    void reset(Expression *ptr = 0)
    {
        --pci;
        if (ptr != 0)
            pci.ptr_ = ptr;
        else
            pci.ptr_ = new Expression;
        pci = 1;
    }

    Expression& operator*() const
    {
        return *pci.ptr_;
    }

    Expression* operator->() const
    {
        return pci.ptr_;
    }
//----------------------------------------
#if 0
    String(const String &other) : size(other.size), str(new char[other.size+1])
    {
        str[size] = 0;
        memcpy(str, other.str, size);
    }
#endif

    SharedPtr(const SharedPtr& other)
                    : pci(other.pci.ptr_, other.pci.cnt_)
    {
        ++other.pci;
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
    SharedPtr& operator=(const SharedPtr& other)
    {
	    if (this != &other)
        {
            ++other.pci;
            --this.pci;
            this.pci = other.pci;
            this.pci.ptr_ = other.pci.ptr_;
        }
        return *this;
    }

    struct pc
    {
        pc(Expression *ptr, int *cnt = 0)
        {
            if (cnt == 0)
                cnt = new int;
            if (ptr == 0)
                pc = 0;
            else
                pc.ptr_ = ptr;

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
            if (pc.ptr_)
                ++pc.cnt_;
            return pc.cnt_;
        }

        int operator--(void)
        {

            if (pc.ptr_)
            {
                --pc.cnt_;
                if (pc.cnt == 0)
                {
                    delete pc.ptr_;
                    pc.ptr_ = 0;
                }
            }
            return pc.cnt;
        }

        pc& operator=(int cnt)
        {
            this->cnt_ = cnt;
            return *this;
        }

        Expression *ptr_;
    private:
        int *cnt_;
    };
    pc pci;
};





int main()
{
    cout << "Hello world!" << endl;

    SharedPtr p;

    p->a = 17;

    cout << p->a << endl;

    return 0;
}


