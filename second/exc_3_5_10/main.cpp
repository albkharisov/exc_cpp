#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

template<class Iterator, class Pred>
Iterator remove_if1(Iterator p, Iterator q, Pred pred)
{
    Iterator s = std::find_if(p, q, pred);
    if (s == q)
        return q;

    Iterator out = s;
    ++s;
    return remove_copy_if(s, q, out, pred);
}

struct ElementN
{
    explicit ElementN(size_t n)
        : n(n), pi(new size_t(0))
    {}

    template<class T>
    bool operator()(T const& t) { return ((*pi)++ == n); }

    size_t n;
    std::shared_ptr<size_t> pi;
};

int main()
{
    {
        std::vector<int> v = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };

        v.erase(remove_if1(v.begin(), v.end(), ElementN(3)), v.end());

        for (int i: v)
            std::cout << i << ' ';
    }

    std::cout << endl;

    {
        std::vector<int> v1 = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };

        v1.erase(remove_if1(v1.begin(), v1.end(), ElementN(3)), v1.end());

        for (int i: v1)
            std::cout << i << ' ';
    }

    return 0;
}

