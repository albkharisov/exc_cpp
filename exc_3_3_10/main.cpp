#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct String
{
    String(const char * str = "") : size(strlen(str)), str(new char[size+1])
    {
        cout << "constr_string" << endl;
//        size = strlen(str);
//        this->str = new char[size+1];
        memcpy(this->str, str, size+1);
        this->str[size] = 0;
    }

    String(char c, int a) : str(new char[a+1]), size(a)
    {
        cout << "constr_mulchar" << endl;
        memset(str, c, a);
        str[a] = 0;
    }

    ~String()
    {
        delete [] str;
        cout << "destruction" << endl;
    }

	void append(String &other)
	{
        cout << "append" << endl;
        char *pr_str = new char[other.size + size + 1];
        memcpy(pr_str, str, size);
        memcpy(pr_str + size, other.str, other.size);

        size += other.size;
        delete [] str;
        str = pr_str;
        str[size] = 0;
	}

//    String(const String &other) : size(other.size), str(new char[other.size+1])
//    {
//        cout << "constr_copy" << endl;
//        str[size] = 0;
//        memcpy(str, other.str, size);
//    }

	String &operator=(const String &other)
	{
        cout << "oper_=" << endl;
	    if (this != &other)
        {
            delete [] str;
            size = other.size;
            str = new char [size+1];
            str[size] = 0;
            memcpy(str, other.str, size);
        }
	}

    int size;
    char *str;
};

void printStr(String &str)
{
    cout << str.str << endl;
}

int main()
{
#if 0
    String s1("let");
    cout << "string:\"" << s1.str << "\"\r\nis size of:" << s1.size << endl;

    String s2('a', 5);
    String s3("here is 5A->");

    cout << "string:\"" << s2.str << "\"" << endl;

    s3.append(s2);

    cout << "string:\"" << s3.str << "\"" << endl;
#endif

    String a("gtrk");
//    String a('2', 3);
    String b("enot");
    b = a;
    printStr(b);
//    delete a;
    return 0;
}


