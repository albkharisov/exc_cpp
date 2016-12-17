#include <iostream>

#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

using namespace std;

struct Point
{
    Point (int x = 0, int y = 0) : x(x), y(y) {};
    int x;
    int y;
    int getdx() { return x += 2; };
};

struct Rational
{
    Rational(int numerator = 0, int denominator = 1);

    void add(Rational rt);
    void sub(Rational rt);
    void mul(Rational rt);
    void div(Rational rt);
    void neg();
    void inv();
    double to_double() const;

    int & getnum();
    int & getden();

    void priv();

//    Point getpoint() { return pt; };
//    Point & getpoints() { return pt; };
//    Point pt;
private:
    int numerator_;
    int denominator_;
};

double Rational::to_double() const
{
    return numerator_/denominator_;
}

std::ostream& operator<<(std::ostream &os, Rational &r)
{
    os << r.getnum() << '/' << r.getden();
}

Rational::Rational(int numerator, int denominator)
                    : numerator_(numerator), denominator_(denominator)
{
    priv();
};

void Rational::priv()
{
//    cout << *this << endl;
    int nod = 1;
    for (int i = 2; i <= MIN(numerator_, denominator_); i++)
    {
//        cout << i << ':' << numerator_ % i << ' ' << denominator_ % i;
        if (!(numerator_ % i) && !(denominator_ % i))
        {
//            cout << " MAX";
            nod = MAX(nod,i);
        }
//        cout << endl;
    }
//    cout << "nod=" << nod << endl;
    numerator_ /= nod;
    denominator_ /= nod;
}

int & Rational::getnum() { return numerator_; };
int & Rational::getden() { return denominator_; };

void Rational::add(Rational rt)
{
    rt.numerator_ *= denominator_;
    numerator_ *= rt.denominator_;
    numerator_ += rt.numerator_;
    denominator_ *= rt.denominator_;
    priv();
}

void Rational::sub(Rational rt)
{
    rt.numerator_ *= denominator_;
    numerator_ *= rt.denominator_;
    numerator_ -= rt.numerator_;
    denominator_ *= rt.denominator_;
    priv();
}
void Rational::mul(Rational rt)
{
    numerator_ *= rt.numerator_;
    denominator_ *= rt.denominator_;
    priv();
}
void Rational::div(Rational rt)
{
    numerator_ *= rt.denominator_;
    denominator_ *= rt.numerator_;
    priv();
}

void Rational::neg()
{
    numerator_ = -numerator_;
}

void Rational::inv()
{
    numerator_ += denominator_;
    denominator_ = numerator_ - denominator_;
    numerator_ -= denominator_;
}

Rational & operator+(Rational r1, Rational r2)
{
    r1.add(r2);
    return r1;
}

Rational & operator-(Rational r1, Rational r2)
{
    r1.sub(r2);
    return r1;
}

Rational & operator*(Rational r1, Rational r2)
{
    r1.mul(r2);
    return r1;
}

Rational & operator/(Rational r1, Rational r2)
{
    r1.div(r2);
    return r1;
}

Rational & operator+=(Rational &r1, Rational r2)
{
    r1 = r1 + r2;
    return r1;
}

Rational & operator-=(Rational &r1, Rational r2)
{
    r1 = r1 - r2;
    return r1;
}

Rational & operator*=(Rational &r1, Rational r2)
{
    r1 = r1 * r2;
    return r1;
}

Rational & operator/=(Rational &r1, Rational r2)
{
    r1 = r1 / r2;
    return r1;
}

int main()
{
    Rational rat1(4,6);
    Rational rat2(1,2);
    Rational rat3(3,10);
    Rational rat4(2,11);

    cout << "rat1:" << rat1 << endl;
    cout << "rat2:" << rat2 << endl;
    cout << "rat3:" << rat3 << endl;
    cout << "rat4:" << rat4 << endl;
    cout << "========" << endl;
//    rat2 = rat2 + rat2;
    cout << rat1 << " - " << rat2 << " = " << rat1 - rat2 << endl;



//    rat2 -= rat1;
//    cout << "rat2:" << rat2 << endl;

//    rat2 = rat2*rat2;
//    cout << "rat2:" << rat2 << endl;
//
//    rat2 = rat2/rat2;
//    cout << "rat2:" << rat2 << endl;



//    rat.getpoints().x = 1;
//    cout << rat.getpoint().getdx() << endl;

//    cout << "Hello world!" << endl;
    return 0;
}


