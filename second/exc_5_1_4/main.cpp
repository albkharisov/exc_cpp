#include <iostream>
#include <future>
#include <list>
#include <vector>

template <class Iterator, typename UnFunc, typename BiFunc>
auto map_reduce( Iterator p, Iterator q, UnFunc f1, BiFunc f2, size_t threads)
                -> decltype(f1(*p))
{
    using fRet = decltype(f1(*p));
    using fthread = std::future<fRet>;
    std::vector<fthread> thv(threads);

    auto d = std::distance(p, q);

    long int i = 0;
    for (auto it = thv.begin(); it != thv.end() ; ++it, ++i)
    {
        auto p1 = p;
        auto q1 = p;
        std::advance(p1, static_cast<int>((i * d) / threads));
        std::advance(q1, static_cast<int>(((i+1) * d) / threads));

        *it = std::async(std::launch::async,
                         [] (Iterator p, Iterator q, UnFunc f1, BiFunc f2) -> fRet { auto res = f1(*p); while(++p != q) res = f2(res, f1(*p)); return res; },
                         p1, q1, f1, f2);
    }

    fRet ret = thv.begin()->get();
    for (auto it = std::next(thv.begin()); it != thv.end() ; ++it)
    {
        ret = f2(ret, it->get());
    }

    return ret;
}

using namespace std;

int main()
{
    std::list<int> l = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto sum = map_reduce(l.begin(), l.end(),
                            [](int i){return i;},
                            std::plus<int>(), 2);
    cout << "sum = " << sum << endl;

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

    return 0;
}

