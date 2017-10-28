#include <iostream>
#include <stdio.h>

using namespace std;

/*
 * Класс Cls определен точно таким образом:
 */
struct Cls {
public:
    Cls(char c = 0, double d = 0, int i = 0) : c(c), d(d), i(i)
    {
//        ch1 = 'A';
//        ch2 = 'B';
    }
private:
    char c;
    double d;
    int i;
};

unsigned char get_ind(Cls &cls, int i) {

    void *ptr = (void *) &cls;
    return ((char *) ptr)[i];
}


// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls) {
    void *ptr = (void *) &cls;
    return ((char *) ptr)[0];
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
    void *ptr = (void *) &cls;
    return ((double *)ptr + 1)[0];
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls &cls) {
    void *ptr = (void *) &cls;
    return ((int *)ptr + 4)[0];
}

int main()
{
    Cls cls1('A', 2.3, 1);

    int c1 = get_c(cls1);

    printf("dec=%d, hex=%#06x, adr=%d\r\n", c1, c1, (void *) &cls1);

    for (int i = 0; i < 21; i++)
    {
        unsigned char ch1 = get_ind(cls1, i);
        printf("%02d:0x%8X %c \r\n", i, ch1, ch1);
    }
//    cout << "c = " << c1 << "; d = " << d1 << "; i = " << i1 << endl;

    printf("\r\n\r\n");
    printf("c=%c\r\n", get_c(cls1));
    printf("d=%f\r\n", (double)get_d(cls1));
    printf("i=%d\r\n", get_i(cls1));
    printf("\r\n\r\n");

    get_c(cls1) = 'B';
    printf("\r\n\r\n");
    printf("c=%c\r\n", get_c(cls1));
    printf("d=%f\r\n", (double)get_d(cls1));
    printf("i=%d\r\n", get_i(cls1));
    printf("\r\n\r\n");


    return 0;
}
