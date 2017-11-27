#include <iostream>
#include "windows.h"
#include <future>
#include <list>
#include <vector>

template <class Iterator, typename UnFunc, typename BiFunc>
auto work( Iterator p, Iterator q, UnFunc f1, BiFunc f2)
                -> decltype(f1(*p))
{
    auto res = f1(*p);
    while(++p != q)
        res = f2(res, f1(*p));
    return res;
}

template <class Iterator, typename UnFunc, typename BiFunc>
auto map_reduce( Iterator p, Iterator q, UnFunc f1, BiFunc f2, size_t threads)
                -> decltype(f1(*p))
{
    using fRet = decltype(f1(*p));
    using fthread = std::thread;
    std::vector<fthread> thv(threads);
    std::vector<fRet> fr(threads);

    auto d = std::distance(p, q);

    long int i = 0;
    for (auto it = thv.begin(); it != thv.end() ; ++it, ++i)
    {
        auto p1 = p;
        auto q1 = p;
        std::advance(p1, static_cast<int>((i * d) / threads));
        std::advance(q1, static_cast<int>(((i+1) * d) / threads));

        thv[i] = std::thread([&fr, i, p1, q1, f1, f2] ()
                             {
                                 fr[i] = work(p1, q1, f1, f2);
                             }
                             );
    }

    thv[0].join();
    fRet ret = fr[0];

    for (size_t i = 1; i < threads ; ++i)
    {
        thv[i].join();
        ret = f2(ret, fr[i]);
    }

    return ret;
}

using namespace std;

int main()
{
    std::list<int> l = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto sum = map_reduce(l.begin(), l.end(),
                            [](int i){return i;},
                            std::plus<int>(), 10);
    cout << "sum = " << sum << endl;

    /*
    auto has_even = map_reduce(l.begin(), l.end(),
                                [](int i){return i % 2 == 0;},
                                std::logical_or<bool>(), 3);
    cout << "has_even = " << has_even << endl;



    std::vector<std::string> vs = { "Hello," , "", " world" , "!" };
    auto concatenated = map_reduce(vs.begin(), vs.end(),
                                    [] (std::string str) { return str; },
                                    [] (std::string str1, std::string str2) { return str1 + str2; },
                                    4);

    cout << "concatenated = " << concatenated << endl;
*/
    return 0;
}

