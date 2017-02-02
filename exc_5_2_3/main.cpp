#include <iostream>

#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

using namespace std;

//std::ostream& operator<<(std::ostream &os, Rational r);

//====================================================================================
struct Rational
{

    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator)
    {
        priv();
    };

    void priv(void);

    int & getnum(void)
    {
        return numerator_;
    }

    int & getden(void)
    {
        return denominator_;
    }

    void add(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void sub(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void mul(Rational rational) {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
    }

    void div(Rational rational) {
        numerator_ *= rational.denominator_;
        denominator_ *= rational.numerator_;
    }

    void neg() {
        numerator_ = -numerator_;
    }

    void inv() {}

    const double to_double() const {
        return numerator_ / (double) denominator_;
    }

    const Rational& operator+() const{
        return *this;
    }

    const Rational operator-() const{
        Rational rt = *this;
        rt.neg();
        return rt;
    }

    Rational& operator+=(Rational rational);
    Rational& operator-=(Rational rational);
    Rational& operator*=(Rational rational);
    Rational& operator/=(Rational rational);

    operator double () const
    {
        return to_double();
    }

private:
    int numerator_;
    int denominator_;
};

std::ostream& operator<<(std::ostream &os, Rational r)
{
    os << r.getnum() << '/' << r.getden();
    return os;
}

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

Rational operator+(Rational r1, Rational r2)
{
    r1.add(r2);
    return r1;
}

Rational operator-(Rational r1, Rational r2)
{
    r1.sub(r2);
    return r1;
}

Rational operator*(Rational r1, Rational r2)
{
    r1.mul(r2);
    return r1;
}

Rational operator/(Rational r1, Rational r2)
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




bool operator>(Rational r1, Rational r2)
{
    return (r1 - r2).getnum() > 0;
}

bool operator<(Rational r1, Rational r2)
{
    return r2 > r1;
}

bool operator==(Rational r1, Rational r2)
{
    return (!(r1 > r2) && !(r2 > r1));
}

bool operator!=(Rational r1, Rational r2)
{
    return !(r1 == r2);
}

bool operator<=(Rational r1, Rational r2)
{
    return (r1 < r2) || (r1 == r2);
}

bool operator>=(Rational r1, Rational r2)
{
    return (r1 > r2) || (r1 == r2);
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

    -rat1;
    cout << "rat1:" << rat1 << endl;
    rat1 = -rat1;
    cout << "rat1:" << rat1 << endl;
//    cout << "rat1.num:" << rat1.getnum() << endl;
//    cout << "rat1.den:" << rat1.getden() << endl;

//    rat2 = rat2 + rat2;
    rat3 = rat1 - rat2;

    Rational rat5;
    rat5 = rat1 - rat2;

    cout << rat1 << " - " << rat2 << " = " << rat1 - rat2 << endl;
    cout << rat1 << " - " << rat2 << " = " << rat5 << endl;
    cout << "rat5.getden() = " << rat5.getden() << endl;
    cout << rat1 << " - " << rat2 << " = " << rat5 << endl;

    cout << "=====" << endl;
    cout << rat1 << " > " << rat2 << " = " << (rat1 > rat2) << endl;
    cout << rat2 << " > " << rat1 << " = " << (rat2 > rat1) << endl;


    cout << "rat1 (" << rat1 << ") " << ">" << " rat2 (" << rat2 << ") = " << (rat1 > rat2) << endl;
    cout << "rat1 (" << rat1 << ") " << ">=" << " rat2 (" << rat2 << ") = " << (rat1 >= rat2) << endl;
    cout << "rat1 (" << rat1 << ") " << "<" << " rat2 (" << rat2 << ") = " << (rat1 < rat2) << endl;
    cout << "rat1 (" << rat1 << ") " << "<=" << " rat2 (" << rat2 << ") = " << (rat1 <= rat2) << endl;
    cout << "rat1 (" << rat1 << ") " << "!=" << " rat2 (" << rat2 << ") = " << (rat1 != rat2) << endl;
    cout << "rat1 (" << rat1 << ") " << "==" << " rat2 (" << rat2 << ") = " << (rat1 == rat2) << endl;

    cout << "============" << endl;

    rat1.getnum() = 5;
    rat1.getden() = 7;
    int a = 3;
//    cout << "rat1 (" << rat1 << ") " << ">" << " 3 = " << (rat1 > a) << endl;
//    cout << "3 " << ">" << " rat1 (" << rat1 << ") = " << (a > rat1) << endl;
//
//    cout << "rat1 (" << rat1 << ") " << ">" << " 2 = " << (rat1 > 2) << endl;
//    cout << "rat1 (" << rat1 << ") " << ">=" << " 2 = " << (rat1 >= 2) << endl;
//    cout << "rat1 (" << rat1 << ") " << "<" << " 2 = " << (rat1 < 2) << endl;
//    cout << "rat1 (" << rat1 << ") " << "<=" << " 2 = " << (rat1 <= 2) << endl;
//    cout << "rat1 (" << rat1 << ") " << "!=" << " 2 = " << (rat1 != 2) << endl;
//    cout << "rat1 (" << rat1 << ") " << "==" << " 2 = " << (rat1 == 2) << endl;
//
//
//    cout << "(rat1 - 2).getnum() = " << ((rat1 - 2).getnum()) << endl;
//
//    if ((rat1 - 2).getnum() == 0)
//        cout << "(r1 - r2).getnum() == 0";
//    else
//        cout << "(r1 - r2).getnum() != 0";
//
    cout << "rat1 = " << rat1 << "(" << (double)rat1 << ")" << endl;

    return 0;
}


