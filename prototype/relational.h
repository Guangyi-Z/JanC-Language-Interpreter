#include "constant.h"

class Relational : public Constant {
public:
    Relational(CONST_T _t) : Constant(_t) {}

    virtual Relational And(Relational* o2) = 0;
    virtual Relational Or(Relational* o2) = 0;
    virtual Relational Not(Relational* o2) = 0;

private:
    ;
};

class Bool : public Relational {
    ;
};
