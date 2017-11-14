#include <iostream>
#include <list>

using namespace std;


// так как в задании не указан тип элементов,
// которые хранятся в списке, то давайте сделаем
// эту функцию шаблонной
// Параметр It — это тип итератора
template<class It>
size_t max_increasing_len2(It p, It q)
{
    size_t maxcnt = 0;

    if (p == q)
        return 0;
    if (p == --q)
        return 1;

    for (size_t cnt = 1 ; p != q; )
    {
        if (*p >= *(++p))
            cnt = 1;
        else
            ++cnt;
        maxcnt = cnt > maxcnt ? cnt : maxcnt;
    }

    return maxcnt;
}



template<class It>
size_t max_increasing_len(It p, It q)
{
    size_t maxcnt = 0;

    if (p == q)
        return 0;
    if (p == --q)
        return 1;

    for (size_t cnt = 1 ; p != q; ++p )
    {
        It a = p;
        ++a;
        if (*p >= *a)
            cnt = 1;
        else
            ++cnt;
        maxcnt = cnt > maxcnt ? cnt : maxcnt;
    }

    return maxcnt;
}




int main()
{
    std::list<int> const l11 = {7,8,9,4,5,6,1,2,3,4};
    size_t len11 = max_increasing_len(l11.begin(), l11.end()); // 4, соответствует подотрезку 1,2,3,4
    cout << "len1=" << len11 << endl;

#if 1
    std::list<int> const l12 = {-3,-2,-1,0,0,1,2,3,4,5,0,0};
    size_t len12 = max_increasing_len(l12.begin(), l12.end()); // 6, соответствует подотрезку 0,1,2,3,4,5
    cout << "len12=" << len12 << endl;
#endif  // 0




#if 0
    std::list<int> const l = {3,2,1};
    int len1 = max_increasing_len(l.begin(), l.end());
    if(len1 == 1) std::cout << "1 TRUE" << std::endl;
    else std::cout << "1 FALSE. Expected 1, got " << len1 << std::endl;

    std::list<int> const l2 = {7,8,9,4,5,6,1,2,3,4};
    size_t len2 = max_increasing_len(l2.begin(), l2.end()); // 4, соответствует подотрезку 1,2,3,4
    if(len2 == 4) std::cout << "2 TRUE" << std::endl;
    else std::cout << "2 FALSE. Expected 4, got " << len2 << std::endl;

    std::list<int> const l3 = {-3,-2,-1,0,0,1,2,3,4,5};
    size_t len3 = max_increasing_len(l3.begin(), l3.end()); // 6, соответствует подотрезку 0,1,2,3,4,5
    if(len3 == 6) std::cout << "3 TRUE" << std::endl;
    else std::cout << "3 FALSE. Expected 6, got " << len3 << std::endl;

    std::list<int> const l4 = {1,2,3};
    int len4 = max_increasing_len(l4.begin(), l4.end());
    if(len4 == 3) std::cout << "4 TRUE" << std::endl;
    else std::cout << "4 FALSE. Expected 3, got " << len4 << std::endl;

    std::list<int> const l5 = {};
    int len5 = max_increasing_len(l5.begin(), l5.end());
    if(len5 == 0) std::cout << "5 TRUE" << std::endl;
    else std::cout << "5 FALSE. Expected 0, got " << len5 << std::endl;

    std::list<int> const l6 = {1, 1, 1, 1, 1};
    int len6 = max_increasing_len(l6.begin(), l6.end());
    if(len6 == 1) std::cout << "6 TRUE" << std::endl;
    else std::cout << "6 FALSE. Expected 1, got " << len6 << std::endl;

    std::list<int> const l7 = {3};
    int len7 = max_increasing_len(l7.begin(), l7.end());
    if(len7 == 1) std::cout << "7 TRUE" << std::endl;
    else std::cout << "7 FALSE. Expected 1, got " << len7 << std::endl;

    std::list<int> const l8 = {3, 5};
    int len8 = max_increasing_len(l8.begin(), l8.end());
    if(len8 == 2) std::cout << "8 TRUE" << std::endl;
    else std::cout << "8 FALSE. Expected 2, got " << len8 << std::endl;

    std::list<int> const l9 = {3, 1};
    int len9 = max_increasing_len(l9.begin(), l9.end());
    if(len9 == 1) std::cout << "9 TRUE" << std::endl;
    else std::cout << "9 FALSE. Expected 1, got " << len9 << std::endl;

    std::list<int> const l10 = {3, 3};
    int len10 = max_increasing_len(l10.begin(), l10.end());
    if(len10 == 1) std::cout << "10 TRUE" << std::endl;
    else std::cout << "10 FALSE. Expected 1, got " << len10 << std::endl;
#else
        std::list<int> const l = {3,2,1};
        size_t len1 = max_increasing_len(l.begin(), l.end());
        if(len1 == 1) std::cout << "1 TRUE" << std::endl;
        else std::cout << "1 FALSE. Ожидается 1, получено " << len1 << std::endl;

        std::list<int> const l2 = {7,8,9,4,5,6,1,2,3,4};
        size_t len2 = max_increasing_len(l2.begin(), l2.end()); // 4, соответствует подотрезку 1,2,3,4
        if(len2 == 4) std::cout << "2 TRUE" << std::endl;
        else std::cout << "2 FALSE. Ожидается 4, получено " << len2 << std::endl;

        std::list<int> const l3 = {-3,-2,-1,0,0,1,2,3,4,5};
        size_t len3 = max_increasing_len(l3.begin(), l3.end()); // 6, соответствует подотрезку 0,1,2,3,4,5
        if(len3 == 6) std::cout << "3 TRUE" << std::endl;
        else std::cout << "3 FALSE. Ожидается 6, получено " << len3 << std::endl;

        std::list<int> const l4 = {1,2,3};
        size_t len4 = max_increasing_len(l4.begin(), l4.end());
        if(len4 == 3) std::cout << "4 TRUE" << std::endl;
        else std::cout << "4 FALSE. Ожидается 3, получено " << len4 << std::endl;

        std::list<int> const l5 = {};
        size_t len5 = max_increasing_len(l5.begin(), l5.end());
        if(len5 == 0) std::cout << "5 TRUE" << std::endl;
        else std::cout << "5 FALSE. Ожидается 0, получено " << len5 << std::endl;

        std::list<int> const l6 = {1, 1, 1, 1, 1};
        size_t len6 = max_increasing_len(l6.begin(), l6.end());
        if(len6 == 1) std::cout << "6 TRUE" << std::endl;
        else std::cout << "6 FALSE. Ожидается 1, получено " << len6 << std::endl;

        std::list<int> const l7 = {0,1};
        size_t len7 = max_increasing_len(l7.begin(), l7.end());
        if (len7 == 2)std::cout << "7 TRUE" << std::endl;
        else std::cout << "7 FALSE. Ожидается 2, получено " << len7 << std::endl;

        std::list<int> const l8 = {0,0};
        size_t len8 = max_increasing_len(l8.begin(), l8.end());
        if(len8 == 1)std::cout << "8 TRUE" << std::endl;
        else std::cout << "8 FALSE. Ожидается 1, получено " << len8 << std::endl;

        std::list<int> const l9 = {1,0};
        size_t len9 = max_increasing_len(l9.begin(), l9.end());
        if(len9 == 1)std::cout << "9 TRUE" << std::endl;
        else std::cout << "9 FALSE. Ожидается 1, получено " << len9 << std::endl;
#endif








    return 0;
}
