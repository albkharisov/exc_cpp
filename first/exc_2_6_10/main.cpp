#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define MIN(x,y)        ((x) < (y) ? (x) : (y))
char *resize(const char *str, unsigned size, unsigned new_size)
{
    char *p = new char[new_size];
    memcpy(p, str, MIN(size, new_size));
    delete [] str;
    return p;
}

void addsym(char **pch, char ch);
char *getline()
{
    char c = 0;
    char *pch = new char[1];
    pch[0] = 0;
    while (((c = getchar()) != EOF) && (c != '\n'))
    {
        addsym(&pch, c);
    }
    addsym(&pch, 0);

    return pch;
}

void addsym(char **pch, char ch)
{
    int sz = strlen(*pch);
    *pch = resize(*pch, sz + 1, sz + 2);
    (*pch)[sz] = ch;
    (*pch)[sz+1] = 0;
}

int main()
{
    char *p = getline();
    cout << "getline returns(" << strlen(p) << "): \"" << p << "\"" << endl;
    return 0;
}
