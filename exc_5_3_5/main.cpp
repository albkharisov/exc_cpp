#include <iostream>

using namespace std;

struct Expression;
struct Number;
struct BinaryOperation;
typedef struct pc;

int operator++(pc &);
int operator--(pc &);

struct pc
{
    pc& operator=(int * cnt)
    {
        cnt_ = cnt;
        cout << "pc (*cnt)operator=, cnt_ = " << cnt_ << " *cnt_ = " << *cnt_ << endl;
        return *this;
    }

    pc& operator=(int cnt)
    {
        *cnt_ = cnt;
        cout << "pc (cnt)operator=, cnt_ = " << cnt_ << " *cnt_ = " << *cnt_ << endl;
        return *this;
    }

    explicit pc(int *cnt = 0)
    {
        if (cnt == 0)
        {
//            cnt = new int;
            cnt_ = new int;
            *cnt_ = 0;
            cout << "new cnt_ = " << cnt_ << endl;
        }
        else
            cnt_ = cnt;

        cout << "pc constructor: cnt_ = " << cnt_ << ", *cnt_ = " << *cnt_ << endl;
    }

    ~pc()
    {
        cout << "pc destruct, cnt_ = " << cnt_ << ", *cnt_= " << *cnt_ << endl;
        if (!*cnt_)
        {
            delete cnt_;
            cout << "free cnt_" << endl;
        }
        else
            cout << "NO free cnt_, *cnt_= " << *cnt_ << endl;
    }

//    private:
    int *cnt_;
};

int operator++(pc &pc1)
{
    ++(*pc1.cnt_);
    return *pc1.cnt_;
}

int operator--(pc &pc1)
{
    --(*pc1.cnt_);
    return *pc1.cnt_;
}

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
    SharedPtr(const SharedPtr& other)
                    : pci(other.pci.cnt_), ptr_(other.ptr_)
    {
        cout << "SharedPtr const copy: ptr_= " << ptr_ << " cnt= " << *pci.cnt_;
        if (ptr_)
            ++pci;
        cout << " after(" << *pci.cnt_ << ")" << endl;
    }

    explicit SharedPtr(Expression *ptr = 0)
                        : ptr_(ptr)
    {
        if (ptr == 0)
        {
            pci = 0;
        }
        else
        {
            pci = 1;
        }

        cout << "constructor: ptr_= " << ptr_ << " *cnt= " << *pci.cnt_ << endl;
    }

    ~SharedPtr()
    {
        cout << "destructor: ptr_= " << ptr_ << " *cnt= " << *pci.cnt_ << endl;
        if (ptr_ != 0)
        {
            if (!--pci)
            {
                cout << "free ptr" << endl;
                delete ptr_;
                ptr_ = 0;
            }
            else
                cout << "NO free ptr_, *cnt_= " << *pci.cnt_ << endl;
        }
    }

    Expression* get() const
    {
        cout << endl << __FUNCTION__ << endl << endl;
        return ptr_;
    }

    Expression* release()
    {
        cout << endl << __FUNCTION__ << endl << endl;
        Expression *ptr_tmp = ptr_;
        ptr_ = 0;
        --pci;
        return ptr_tmp;
    }

    // !!!! A lot of to think about !!!!
    void reset(Expression *ptr = 0)
    {
        cout << endl << __FUNCTION__ << endl << endl;
        --pci;
        if (ptr != 0)
            ptr_ = ptr;
        else
            ptr_ = new Expression;
        pci = 1;
    }

    SharedPtr& operator=(SharedPtr& other)
    {
        cout << "1 SharedPtr op=: other.ptr= " << other.ptr_ << " other.pci= " << *other.pci.cnt_ <<
                                         " this->ptr= " << ptr_ << " this.pci= " << *pci.cnt_ << endl;
	    if (this != &other)
        {
            ++other.pci;
            --this->pci;
            this->pci = other.pci;
            this->ptr_ = other.ptr_;
        }
        cout << "2 SharedPtr op=: other.ptr= " << other.ptr_ << " other.pci= " << *other.pci.cnt_ <<
                                         " this->ptr= " << ptr_ << " this.pci= " << *pci.cnt_ << endl;
        return *this;
    }

    Expression& operator*() const
    {
        return *ptr_;
    }

    Expression* operator->() const
    {
        return ptr_;
    }

    Expression *ptr_;

private:
    pc pci;
};




int main()
{
//    SharedPtr p(new Expression);
    SharedPtr p((Expression *) 0);
//    p->a = 3;

//    p.ptr_ = 0;
//    cout << "p->a = " << p->a << endl;
    SharedPtr q = p;
//    q->a = 17;

//    cout << "p->a = " << p->a << endl;
//    cout << "q->a = " << q->a << endl;

    return 0;
}


