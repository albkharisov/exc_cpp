#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    for ( ; (n > 0) && (p != q) ; ++p, --n);

    if (p != q)
    {
        auto p1 = p;
        ++p1;
        std::copy(p1, q, p);
        advance(p, std::distance(p, q) - 1);
        q = p;
    }

    return q;
}

void remove_nth_(vector<int> vi, size_t n)
{

    auto its = vi.begin();
    auto ite = vi.end();

    for (auto i : vi)
        cout << i << " ";
    cout << endl;

    vi.erase(remove_nth(its, ite, n), vi.end());

    for (auto i : vi)
        cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0 ; i < 12; ++i)
    {
        cout << "Remove " << i << endl;
        remove_nth_(vi, i);
    }

    return 0;
}
