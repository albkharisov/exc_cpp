#include <iostream>
using namespace std;
#include <algorithm>
#include <array>
#include <vector>
#include <typeinfo>

template <typename T>
void print(T i1, T i2)
{
    for (auto i = i1; i != i2; ++i)
        cout << *i << " ";
    cout << endl;
}

template<class Iterator>
size_t count_permutations1(Iterator p, Iterator q)
{
    sort(p, q);
    print(p, q);



    int cnt = 0;
    do
    {
        if (adjacent_find(p, q) == q)
        {
            ++cnt;
            print(p, q);
        }
    }
    while (next_permutation(p, q));

    return cnt;
}


template<class Iterator>
size_t count_permutations(Iterator p1, Iterator q1)
{
    using T = typename std::iterator_traits<Iterator>::value_type;
    vector<T> v(distance(p1,q1));
    auto p = v.begin();
    auto q = v.end();
    copy(p1,q1,p);
    sort(p, q);

    int cnt = 0;
    do
    {
        if (adjacent_find(v.begin(), v.end()) == v.end())
        {
            ++cnt;
        }
    }
    while (next_permutation(v.begin(), v.end()));

    return cnt;
}






int main()
{
#if 1
    std::array<int, 3> a1 = {1,2,3};
    size_t c1 = count_permutations(a1.begin(), a1.end()); // 6
    std::cout << c1 << std::endl;
#endif // 0

#if 1
    std::array<int, 5> a2 = {1,2,3,4,4};
    size_t c2 = count_permutations(a2.begin(), a2.end()); // 36
    std::cout << c2 << std::endl;
#endif  // 0
    return 0;
}
