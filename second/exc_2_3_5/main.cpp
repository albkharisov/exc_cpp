#include <iostream>

using namespace std;

 struct Point
{
    constexpr Point(double x, double y)
        : x(x), y(y)
    {}

    double x = 0;
    double y = 0;
};


constexpr Point operator + (const Point & p1, const Point & p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}

constexpr Point operator - (const Point & p1, const Point & p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}

constexpr double operator * (const Point & p1, const Point & p2)
{
    return (p1.x * p2.x + p1.y * p2.y);
}

int main()
{
    constexpr size_t size = static_cast<size_t>(Point(2,4) * Point(4,3));
    int m[size]; // массив из 20 элементов
    cout << "sizeof(m) = " << sizeof(m) << endl;
    return 0;
}
