#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct String {
    String(const char * str = "") : size(strlen(str)), str(new char[size+1])
    {
        cout << "constr_string" << endl;
//        size = strlen(str);
//        this->str = new char[size+1];
        memcpy(this->str, str, size+1);
        this->str[size] = 0;
    }

    /* ... */
    char & at(size_t idx)       { cout << "not const" << endl; return str[idx]; }
    char   at(size_t idx) const { cout << "const" << endl; return str[idx]; }
    /* ... */
    size_t size;
    char *str;
};

int main()
{
    String greet("Hello");
    char ch1 = greet.at(0);
    ch1 = 5;

    String const const_greet("CHello, Const!");
    char const &ch2 = const_greet.at(0);
//    ch2 = 5;
    return 0;
}



