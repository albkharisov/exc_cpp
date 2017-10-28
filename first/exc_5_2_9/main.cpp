#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstddef> // size_t

using namespace std;


//struct String {
//	String(const char *str = "");
//	String(size_t n, char c);
//	~String();
//
//    String(const String &other);
//    String &operator=(const String &other);
//
//	void append(const String &other);
//
//	size_t size;
//	char *str;
//};

struct String
{
    String(const char * str = "") : size(strlen(str)), str(new char[size+1])
    {
//        cout << "constr_string" << endl;
//        size = strlen(str);
//        this->str = new char[size+1];
        memcpy(this->str, str, size+1);
        this->str[size] = 0;
    }

    String(char c, int a) : str(new char[a+1]), size(a)
    {
//        cout << "constr_mulchar" << endl;
        memset(str, c, a);
        str[a] = 0;
    }

    ~String()
    {
        delete [] str;
//        cout << "destruction" << endl;
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

// answer Start
	struct StringFolded
	{
        const String operator [](int end_) const
        {
            cout << "StringFoldedOperator[]:" << end_ << endl;
            int curlen = end_ - this->start_;

            char *s = new char[curlen + 1];
            s[curlen] = 0;

            cout << curlen << "|" << "s = \"" << s << "\"" << endl;

            memcpy(s, this->str, curlen);
            String tmp(s);
            delete [] s;
            return tmp;
        }
        int start_;
        char *str;
	};

	StringFolded operator [](int start_) const
	{
        cout << "StringOperator[]:" << start_ << endl;
	    StringFolded tmp;
	    tmp.start_ = start_;
	    tmp.str = &this->str[start_];
	    return tmp;
	}

// answer End

    int size;
    char *str;
};

std::ostream& operator <<(std::ostream &os, const String &str){
    os << "[" << str.size << "] |" << str.str << "|" << endl;
    return os;
}

int main()
{
    String abc("hello");
    cout << abc << endl;

    const String hell = abc[0][4];
    const String ell = abc[1][4];

    cout << hell << endl;
    cout << ell << endl;
    return 0;
}


