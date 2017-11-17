#include <iostream>
#include <vector>
#include <list>
#include <iterator>

template<class T>
class VectorList
{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    struct MyIt;
    struct MyItR;
    typedef MyIt iterator;
    typedef MyIt const_iterator;
    typedef MyItR reverse_iterator;
    typedef MyItR const_reverse_iterator;
//    typedef std::const_reverse_iterator<VectorList::const_iterator> MyItR;
//    typedef MyItR const_reverse_iterator;

    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;
    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    template<class It>
    void append(It p, It q)
    {
        if (p != q)
            VectorList::data_.push_back(VectT(p,q));
    }

    bool empty() const { return size() == 0; }

    size_t size() const
    {
        int i = 0;
        for (auto It = data_.begin(); It != data_.end() ; ++It)
            i += It->size();
        return i;
    }

    struct MyIt : std::iterator<std::bidirectional_iterator_tag, const T>
    {
        MyIt(const MyIt & myit) = default;
        MyIt(const MyItR & myitr) : itL(myitr.itL), itV(myitr.itV) { }
        MyIt() = default;

        MyIt & operator=(MyIt &&)      = default;
        MyIt & operator=(MyIt const &) = default;

        bool operator==(const MyIt& rhs) const
        {
            return (this->itL == rhs.itL) && (this->itV == rhs.itV);
        }

        bool operator!=(const MyIt& rhs) const
        {
            return !(*this == rhs);
        }

        MyIt& operator++ ()
        {
            ++itV;
            if (itV == itL->end())
            {
                ++itL;
                itV = itL->begin();
            }
            return *this;
        }
        MyIt operator++(int) { MyIt temp = *this; ++*this; return temp; }

        MyIt& operator-- ()
        {
            if (itV == itL->begin())
            {
                --itL;
                itV = itL->end();
            }
            --itV;

            return *this;
        }
        MyIt operator--(int) { MyIt temp = *this; --*this; return temp; }

        const T& operator* () const
        {
            return *itV;
        }
        const T * operator->() const
        {
            return &(*itV);
        }

        typename VectT::const_iterator itV;
        typename ListT::const_iterator itL;
    };

    const MyIt begin() const
    {
        MyIt myit;
        myit.itL = data_.begin();
        myit.itV = myit.itL->begin();
        return myit;
    }

    const MyIt end() const
    {
        MyIt myit;
        myit.itL = data_.end();
        myit.itV = myit.itL->begin();
        return myit;
    }

////////////////////////////////////////////////////////////////////////////////////////
    struct MyItR : std::iterator<std::bidirectional_iterator_tag, const T>
    {
        MyItR(const MyItR & myitr) = default;
        MyItR(const MyIt & myit) : itL(myit.itL), itV(myit.itV)
        {
        }
        MyIt base() const
        {
            MyIt m;
            m.itL = itL.base();
            m.itV = itV.base();
            return m;
        }
        MyItR() = default;
        MyItR & operator=(MyItR &&)      = default;
        MyItR & operator=(MyItR const &) = default;

        bool operator==(const MyItR& rhs) const
        {
            return (this->itL == rhs.itL) && (this->itV == rhs.itV);
        }

        bool operator!=(const MyItR& rhs) const
        {
            return !(*this == rhs);
        }

        MyItR& operator++ ()        // prefix ++
        {
            ++itV;
            if (itV == itL->rend())
            {
                ++itL;
                itV = itL->rbegin();
            }
            return *this;
        }
        MyItR operator++(int) { MyItR temp = *this; ++*this; return temp; }

        MyItR& operator--()
        {
            if (itV == itL->rbegin())
            {
                --itL;
                itV = itL->rend();
            }
            --itV;

            return *this;
        }
        MyItR operator--(int) { MyItR temp = *this; --*this; return temp; }


        const T& operator* () const
        {
            return *itV;
        }
        const T * operator->() const
        {
            return &(*itV);
        }

        typename VectT::const_reverse_iterator itV;
        typename ListT::const_reverse_iterator itL;
    };

    const MyItR rbegin() const
    {
        MyItR myitr;
        myitr.itL = data_.rbegin();
        myitr.itV = myitr.itL->rbegin();
        return myitr;
    }

    const MyItR rend() const
    {
        MyItR myitr;
        myitr.itL = data_.rend();
        myitr.itV = myitr.itL->rbegin();
        return myitr;
    }

private:
    ListT data_;
};


using namespace std;

struct myclass
{
    int a;
    int b;
};
/*
error: static assertion failed: Incorrect iterator value_type
     static_assert(std::is_same <typename std::iterator_traits<VL::const_iterator>::reference,
                                std::string const&>
                                ::value,
                    "Incorrect iterator value_type");
     ^
main.cpp: In function ‘void check_vec()’:
main.cpp:493:39: error: passing ‘const const_iterator {aka const VectorList<std::basic_string<char> >::MyIt}’ as ‘this’ argument of ‘bool VectorList<T>::MyIt::operator==(const VectorList<T>::MyIt&) [with T = std::basic_string<char>]’ discards qualifiers [-fpermissive]
         bool btest1 = cit == v1.begin() && cit != v1.begin();
                                       ^
main.cpp:493:60: error: passing ‘const const_iterator {aka const VectorList<std::basic_string<char> >::MyIt}’ as ‘this’ argument of ‘bool VectorList<T>::MyIt::operator!=(const VectorList<T>::MyIt&) [with T = std::basic_string<char>]’ discards qualifiers [-fpermissive]
         bool btest1 = cit == v1.begin() && cit != v1.begin();
                                                            ^
main.cpp:494:41: error: passing ‘const const_reverse_iterator {aka const VectorList<std::basic_string<char> >::MyItR}’ as ‘this’ argument of ‘bool VectorList<T>::MyItR::operator==(const VectorList<T>::MyItR&) [with T = std::basic_string<char>]’ discards qualifiers [-fpermissive]
         bool btest2 = crit == v1.rbegin() && crit != v1.rbegin();
                                         ^
main.cpp:494:64: error: passing ‘const const_reverse_iterator {aka const VectorList<std::basic_string<char> >::MyItR}’ as ‘this’ argument of ‘bool VectorList<T>::MyItR::operator!=(const VectorList<T>::MyItR&) [with T = std::basic_string<char>]’ discards qualifiers [-fpermissive]
         bool btest2 = crit == v1.rbegin() && crit != v1.rbegin();
                                                                ^




*/

int main()
{
    std::vector<int> v1 = { 1, 2, 3 };
    std::vector<int> v2 = { 4, 5, 6, 7 };
    std::vector<int> v3 = { };
    std::vector<int> v4 = { 8, 9 };
    VectorList<int> vlist;
    auto itb = v1.begin();
    auto ite = v1.end();
    vlist.append(itb, ite);
    itb = v2.begin();
    ite = v2.end();
    vlist.append(itb, ite);
    itb = v3.begin();
    ite = v3.end();
    vlist.append(itb, ite);
    itb = v4.begin();
    ite = v4.end();
    vlist.append(itb, ite);

#if 0
    for (auto It : vlist)
        cout << It << endl;

    cout << "size = " << vlist.size() << endl;

    for (auto It = vlist.begin(); It != vlist.end(); It++)
        cout << *It << endl;
    cout << "======" << endl;
    for (auto It = vlist.end(); It-- != vlist.begin(); )
        cout << *It << endl;

    cout << "=== reverse ===" << endl;

    for (auto It = vlist.rbegin(); It != vlist.rend(); It++)
        cout << *It << endl;
    cout << "======" << endl;
    for (auto It = vlist.rend(); It-- != vlist.rbegin(); )
        cout << *It << endl;


    cout << "============================================================" << endl;

    std::vector<std::string> vs1 = { "One", "Two", "Tri" };

    VectorList<std::string> vslist;
    auto its1 = vs1.begin();
    auto its2 = vs1.end();
    vslist.append(its1, its2);

    cout << endl << endl;
    cout << "str size = " << vslist.size() << endl;

    for (auto It : vslist)
        cout << It << endl;

    auto It = vslist.begin();
    cout << "It = " << *It << endl;


    cout << "============================================================" << endl;

    std::vector<myclass> vm1;
    myclass m;
    m.a = 1; m.b = m.a * 10;
    vm1.push_back(m);
    m.a = 2; m.b = m.a * 10;
    vm1.push_back(m);
    m.a = 3; m.b = m.a * 10;
    vm1.push_back(m);
    m.a = 4; m.b = m.a * 10;
    vm1.push_back(m);
    m.a = 5; m.b = m.a * 10;
    vm1.push_back(m);
    m.a = 6; m.b = m.a * 10;
    vm1.push_back(m);
    VectorList<myclass> vmlist;
    auto itm1 = vm1.begin();
    auto itm2 = vm1.end();
    vmlist.append(itm1, itm2);

    cout << "============================================================" << endl;

    auto It10 = vmlist.begin();
    cout << It10->a << " : " << (*It10).b << endl;
    ++It10;
    cout << It10->a << " : " << (*It10).b << endl;

    auto It11 = vmlist.rbegin();
    cout << It11->a << " : " << (*It11).b << endl;
    ++It11;
    cout << It11->a << " : " << (*It11).b << endl;

    cout << "============================================================" << endl;


#endif


    VectorList<int>::const_iterator cit = vlist.begin();        // cit = 1
    cout << "cit = " << *cit << endl;
    ++cit;      // cit = 2
    cout << "cit = " << *cit << endl;
    ++cit;      // cit = 3
    cout << "cit = " << *cit << endl;
    auto crit = VectorList<int>::const_reverse_iterator(cit);

    cout << "crit = " << *crit << endl;
    ++crit;
    cout << "crit = " << *crit << endl;
    ++crit;

//    auto cit2 = VectorList<int>::const_iterator(crit);

    auto cit2 = crit.base();

#if 1
    cout << "cit = " << *cit2 << endl;
    ++cit2;      // cit = 2
    cout << "cit = " << *cit2 << endl;
    ++cit2;      // cit = 3
    cout << "cit = " << *cit2 << endl;
#endif

    typedef VectorList<int> VL;
static_assert(std::is_same<typename std::iterator_traits<VL::const_iterator>::reference, int const &>::value, "Incorrect iterator value_type");


    return 0;
}




