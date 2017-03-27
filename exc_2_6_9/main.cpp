#include <iostream>

using namespace std;

#include <string.h>
#define MIN(x,y)        ((x) < (y) ? (x) : (y))
char *resize(const char *str, unsigned size, unsigned new_size)
{
    char *p = new char[new_size];
    memcpy(p, str, MIN(size, new_size));
    delete [] str;
    return p;
}

int main()
{

    cout << "Hello world!" << endl;
    return 0;
}
