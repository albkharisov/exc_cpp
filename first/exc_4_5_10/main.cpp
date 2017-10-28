#include <iostream>

using namespace std;

struct Number;
struct BinaryOperation;

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * operation) = 0;
    virtual ~Visitor() { }
};

struct Expression
{
    virtual double evaluate() const = 0;
    virtual void visit(Visitor * vistitor) const = 0;
    virtual ~Expression() {}
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}

    ~Number(){}

    double evaluate() const { return value; }

    double get_value() const { return value; }

    void visit(Visitor * visitor) const { visitor->visitNumber(this); }

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    { }

    ~BinaryOperation() {}

    Expression const * get_left() const { return left; }
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }

    void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }

    double evaluate() const
    {
        switch (op)
        {
        case '+': return (left->evaluate() + right->evaluate());
        case '-': return (left->evaluate() - right->evaluate());
        case '*': return (left->evaluate() * right->evaluate());
        case '/': return (left->evaluate() / right->evaluate());
        }
    }

private:
    Expression const * left;
    Expression const * right;
    char op;
};

#include <iostream>

/* Этот класс вам нужно реализовать */
struct PrintVisitor : Visitor {
    void visitNumber(Number const * number)
    {
        std::cout << number->get_value() << " ";
    }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        std::cout << "(";
        bop->get_left()->visit(this);
        std::cout << bop->get_op() << " ";
        bop->get_right()->visit(this);
        std::cout << ")";
    }
};

int main()
{
//    Number n1(1);
    Expression const * n1 = new Number(1);
    Expression const * n2 = new Number(2);
    Expression const * n3 = new Number(3);
    Expression const * n4 = new Number(4);
//    // ((1 + 2) * 3) - 4
    Expression const * ex1 = new BinaryOperation(n1, '+', n2);
    Expression const * ex2 = new BinaryOperation(ex1, '*', n3);
    Expression const * ex3 = new BinaryOperation(ex2, '-', n4);
    PrintVisitor visitor;
    ex3->visit(&visitor);


    return 0;
}
