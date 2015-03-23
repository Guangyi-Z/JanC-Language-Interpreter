#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#include "parser/constant.h"
#include "lexer/op.h"

class Arithmetic {
public:
    static void CheckType(Constant &con1, Constant &con2);
    static void CheckOP(OP op, CONST_T t);
    static Constant TypeUpGrade(Constant con);
    static Constant Add(Constant con1, Constant con2);
    static Constant Sub(Constant con1, Constant con2);
    static Constant Mul(Constant con1, Constant con2);
    static Constant Div(Constant con1, Constant con2);
};


#endif
