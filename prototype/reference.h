#include "arithmetic.h"
#include "relational.h"
#include "literal.h"

enum OPRD_T {
    OPRD_VALUE,
    OPRD_FUNC,
    OPRD_ARRAY,
    OPRD_VAR
};

class Operand {
    ;
};

class ValueRef : Operand {
    Constant con;
};

class FuncRef : Operand {
    string id;
    /* value || VarRef */
    vector<Expression*> paras;
};

class ArrayRef : Operand {
    string id;
    Expression *index;
};

/* Different when for Function parameters or return type, may be ref to Func or Array */
class VarRef : Operand {
    string id;
};

