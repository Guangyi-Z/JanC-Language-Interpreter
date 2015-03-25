#include "constant.h"

class Literal: public Constant {
public:
    Literal(CONST_T _t) : Constant(_t) {}

    virtual Literal Concat(Literal *o2) = 0;

private:
    ;
};


class Char : public Literal {
    ;
};

class String : public Literal {
    ;
};

