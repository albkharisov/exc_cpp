#include <iostream>

using namespace std;

struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }
protected:
    Foo(const char *msg) : msg(msg) { }
private:
    const char *msg;
};

struct Bar : Foo
{
#if 0
    Bar(const char *msg)
    {
        str = new char[sizeof(msg)];
        memcpy(str, msg);
        str[sizeof(msg)] = 0;
    }
    int size;
    char * str;
#else
    Bar (const char * msg) : Foo(msg){}
#endif

};

void foo_says(const Foo& foo) { foo.say(); }

Bar get_foo(const char *msg) {
    Bar bar(msg);
    return bar;
}

Foo get_foo2(const char *msg) {
    Bar bar(msg);
    Foo f1 = bar;
    return f1;
}

int main()
{
    Foo foo1 = get_foo2("lol");

    foo1.say();

    return 0;
}
