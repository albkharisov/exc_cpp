#include <iostream>

using namespace std;

struct String
{
    String (const char *sarg)
    {
        sp = new char [10];
        for (int i = 0; i < 10 ; ++i)
        {
            sp[i] = sarg[i];
        }
    }

    explicit operator char const *() const
    {
        std::cout << "1" << endl;
    }

    char *sp;
};

int main()
{
    String s("Hello");

    //delete s;    // 1

    //if (s) { }   // 2

    //char const * p1 = s;  // 3

    char const * p2 = (char const*)s;  // 4

    char const * p3 = static_cast<char const*>(s);  // 5

    //char const * s2 = s + 4;  // 6

    cout << "Hello world!" << endl;

    return 0;
}
