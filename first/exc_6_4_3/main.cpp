#include <iostream>

using namespace std;

//template <typename T>
template <typename T, size_t n>
size_t array_size(T (&a) [n])
{
    return n;
};

int main()
{
    int ints[] = {1, 2, 3, 4};
    int *iptr = ints;
    double doubles[] = {3.14};
    array_size(ints); // ������ 4
    array_size(doubles); // ������ 1
    array_size(iptr); // ��� ������ ��������� ������ ����������
    return 0;
}
