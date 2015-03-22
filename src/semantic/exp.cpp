#include "exp.h"

void Expression::DoPrefixOP(Operand &o) {
    if (o.GetPrefix().empty())
        return;
    for (OP op : o.GetPrefix()) {
        switch(op) {
            case OP_ADD:
                /* empty */
                break;
            case OP_SUB:
                o.ToNegative();
                break;
            case OP_INC:
                o.ToInc();
                break;
            case OP_DEC:
                o.ToDec();
                break;
            case OP_NOT:
                /* to do */
                break;
            default: ;
        }
    }
}

void Expression::DoSuffixOP(Operand &o) {
    if (o.GetSuffix().empty())
        return;
    for (OP op : o.GetSuffix()) {
        switch(op) {
            case OP_INC:
                o.ToInc();
                break;
            case OP_DEC:
                o.ToDec();
                break;
            default: ;
        }
    }
}


Constant Expression::CalcVar(Interpreter &intr, Operand o) {
    ;
}

Constant Expression::CalcFunc(Interpreter &intr, Operand o) {
    ;
}

