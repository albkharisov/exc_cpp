#include <typeinfo>
#include <iostream>

using namespace std;

int main()
{
    std::string s = "Compiler";

    auto sz = s.size();

    auto c1 = s[0];

    decltype(s[0]) c2 = s[7];

    decltype(s[0] + s[7]) c3 = s[1];

    decltype(s)   sa = s;

    decltype((s)) sb = s;

    c1 = 'K';
    c2 = '!';


    cout << "typeid(sz) = \"" << typeid(sz).name() << "\"" << endl;
    cout << "typeid(c1) = \"" << typeid(c1).name() << "\"" << endl;
    cout << "typeid(c2) = \"" << typeid(c2).name() << "\"" << endl;
    cout << "typeid(c3) = \"" << typeid(c3).name() << "\"" << endl;
    cout << "typeid(sa) = \"" << typeid(sa).name() << "\"" << endl;
    cout << "typeid(sb) = \"" << typeid(sb).name() << "\"" << endl;

    cout << "s = \"" << s << "\"" << endl;

    return 0;
}
