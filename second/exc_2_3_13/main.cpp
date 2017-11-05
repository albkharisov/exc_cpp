#include <iostream>
#include <functional>

using namespace std;

template<class F>
bool find_if(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        if (f(*p))
            return true;
    return false;
}


std::function<bool (int)> gen_finder(int * p, int * q)
{
    return [=] (int a) -> bool
    {
        for (int *i = p ; i != q ; ++i)
            if (*i == a)
                return true;
        return false;
    };
}


int main()
{
    int primes[5] = {2,3,5,17,11};
    int m[10] = {0,0,1,1,4,6,7,8,9,10};

    bool has_primes = find_if(m, m + 10, gen_finder(primes, primes + 5));
    cout << "has_primes = " << has_primes << endl;
    return 0;
}
