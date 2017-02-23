#include <iostream>

using namespace std;

struct Expression;
struct Number;
struct BinaryOperation;
struct pc;

int operator++(pc &);
int operator--(pc &);

#define PCI_CNT_        (pci.cnt_ ? *pci.cnt_ : 0)
#define CNT_            (cnt_ ? *cnt_ : 0)

struct pc
{
    pc& operator=(pc &other)
    {
        cnt_ = other.cnt_;
//        cout << "pc (&pc)operator=, cnt_ = " << cnt_ << " *cnt_ = " << CNT_ << endl;
        return *this;
    }

    pc& operator=(int * pcnt)
    {
        cnt_ = pcnt;
//        cout << "pc (*cnt)operator=, cnt_ = " << cnt_ << " *cnt_ = " << CNT_ << endl;
        return *this;
    }

    pc& operator=(int cnt)
    {
        *cnt_ = cnt;
//        cout << "pc (cnt)operator=, cnt_ = " << cnt_ << " *cnt_ = " << CNT_ << endl;
        return *this;
    }

    explicit pc(int *cnt = 0) : cnt_(cnt)
    {
//        if (cnt_)
//            cout << "pc constructor: cnt_ = " << cnt_ << ", *cnt_ = " << CNT_ << endl;
//        else
//            cout << "pc constructor: cnt_ = " << cnt_ << endl;
    }

    ~pc()
    {
//        cout << "pc destruct, cnt_ = " << cnt_ << ", *cnt_= " << CNT_ << endl;
//        if (!*cnt_)
//        {
//            delete cnt_;
//            cout << "free cnt_" << endl;
//        }
//        else
//            cout << "NO free cnt_, *cnt_= " << CNT_ << endl;
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
    SharedPtr& operator=(SharedPtr& other)
    {
        cout << "1 SharedPtr " << ptr_ << " , " << PCI_CNT_ << " == " <<
                    " " << other.ptr_ << " , " << (other.pci.cnt_ ? *other.pci.cnt_ : 0) << endl;
	    if (this != &other)
        {
            if (other.ptr_)
                ++other.pci;
            if (this->ptr_)
            {
                decrease_and_free();
            }

            this->pci = other.pci;
            this->ptr_ = other.ptr_;
        }
        else
            cout << "nothing to set" << endl;
        cout << "2 SharedPtr " << ptr_ << " , " << PCI_CNT_ << " == " <<
                    " " << other.ptr_ << " , " << (other.pci.cnt_ ? *other.pci.cnt_ : 0) << endl;
        return *this;
    }

    SharedPtr(const SharedPtr& other)
                    : pci(other.pci.cnt_), ptr_(other.ptr_)
    {
        cout << "SharedPtr const copy: ptr_= " << ptr_ << " cnt= " << PCI_CNT_;
        if (ptr_)
            ++pci;
        cout << " after(" << PCI_CNT_ << ")" << endl;
    }

    explicit SharedPtr(Expression *ptr = 0)
                        : ptr_(ptr) /*, pci((int *) ptr)*/
    {
        if (ptr)
        {
            cout << "____ NEW PTR ____ " << ptr_ << endl;
            pci = new int;
            pci = 1;
        }

        cout << "constructor: ptr_= " << ptr_ << " *cnt= " << PCI_CNT_ << endl;
    }

    ~SharedPtr()
    {
        cout << "=========" << endl << "destructor: ptr_= " << ptr_ << " *cnt= " << PCI_CNT_ << endl;
        if (ptr_ != 0)
        {
            decrease_and_free();
        }
        else
            cout << "nothing to destruct" << endl;
            cout << endl << "=========" << endl;
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
        if (ptr_)
            --pci;

        if (ptr != 0)
            ptr_ = ptr;
        else
            ptr_ = new Expression;
        pci = 1;
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

    bool decrease_and_free()
    {
        if (!--pci)
        {
            cout << "____ FREE PTR ____ " << ptr_ << endl;
            delete ptr_;
            delete pci.cnt_;
            ptr_ = 0;
            pci.cnt_ = 0;
            return true;
        }
        else
            return false;
    }
};


void func(SharedPtr gav)
{
    gav->a = 18;
}

int main()
{

    SharedPtr p(new Expression);
    SharedPtr p2(new Expression);
//    SharedPtr p((Expression *) 0);
    p->a = 3;

    SharedPtr q2(new Expression);
    p2 = q2;

    {
        cout << "p->a = " << p->a << endl;
        SharedPtr q;
        q = p;
        q->a = 17;
        SharedPtr r((Expression *) 0);
//        r = p;
//        r = q;
        q = r;
        p = r;

        r = p2;
    }

//    func(p);

//    cout << "p->a = " << p->a << endl;
//    cout << "q->a = " << q->a << endl;

    return 0;
}


