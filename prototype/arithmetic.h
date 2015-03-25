#include "constant.h"
#include "relational.h"

class Arithmetic: public Constant {
public:
    Arithmetic(CONST_T _t) : Constant(_t) {}

    virtual Arithmetic Add(Arithmetic* o2) = 0;
    virtual Arithmetic Sub(Arithmetic* o2) = 0;
    virtual Arithmetic Mul(Arithmetic* o2) = 0;
    virtual Arithmetic Div(Arithmetic* o2) = 0;

    virtual Relational GT(Arithmetic* o2) = 0;
    virtual Relational GTEQ(Arithmetic* o2) = 0;
    virtual Relational LT(Arithmetic* o2) = 0;
    virtual Relational LTEQ(Arithmetic* o2) = 0;
    virtual Relational EQ(Arithmetic* o2) = 0;
    virtual Relational NEQ(Arithmetic* o2) = 0;
private:
    ;
};

class Int : public Arithmetic {
public:
    Int(int _i) : i(_i) {}
private:
    int i;
};

class Double : public Arithmetic {
public:
    Double(int _d) : d(_d) {}
private:
    int d;
};
