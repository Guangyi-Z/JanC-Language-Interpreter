#include "arithmetic.h"

// con1 and con2 will be the same type after the check
void Arithmetic::CheckType(Constant &con1, Constant &con2) {
    CONST_T t1 = con1.GetType();
    CONST_T t2 = con2.GetType();
    if (t1 == t2 && t1 != CONST_CHAR)
        return;
    if ((t1 == CONST_INT) && (t2 == CONST_DOUBLE) ||
        (t1 == CONST_DOUBLE) && (t2 == CONST_INT)
            ) {
        con1.TypeUpGrade();
        con2.TypeUpGrade();
        return;

    }
    cout << "Error in CheckType: type1- " << t1 << " and type2- " << t2 << endl;
    exit(0);
}

void Arithmetic::CheckOP(OP op, CONST_T t) {
    switch(t) {
        case CONST_INT:
        case CONST_DOUBLE:
            {
                switch(op) {
                case OP_ADD:
                case OP_SUB:
                case OP_MUL:
                case OP_DIV:
                    return;
                }
            }
        case CONST_STRING:
            if (op == OP_ADD)
                return;
        default:
            cout << "Error in CheckOP: no OP- " << op << " for type- " << t << endl;
            exit(0);
    }
}

Constant Arithmetic::Add(Constant con1, Constant con2) {
    CheckType(con1, con2);
    CheckOP(OP_ADD, con1.GetType());
    switch(con1.GetType()) {
    case CONST_INT:
        return Constant(con1.GetInt() + con2.GetInt());
    case CONST_DOUBLE:
        return Constant(con1.GetDouble() + con2.GetDouble());
    case CONST_STRING:
        return Constant(con1.GetString() + con2.GetString());
    default:
        return Constant();
    }
}
Constant Arithmetic::Sub(Constant con1, Constant con2) {
    CheckType(con1, con2);
    CheckOP(OP_ADD, con1.GetType());
    switch(con1.GetType()) {
    case CONST_INT:
        return Constant(con1.GetInt() - con2.GetInt());
    case CONST_DOUBLE:
        return Constant(con1.GetDouble() - con2.GetDouble());
    default:
        return Constant();
    }
}
Constant Arithmetic::Mul(Constant con1, Constant con2) {
    CheckType(con1, con2);
    CheckOP(OP_ADD, con1.GetType());
    switch(con1.GetType()) {
    case CONST_INT:
        return Constant(con1.GetInt() * con2.GetInt());
    case CONST_DOUBLE:
        return Constant(con1.GetDouble() * con2.GetDouble());
    default:
        return Constant();
    }
}
Constant Arithmetic::Div(Constant con1, Constant con2) {
    CheckType(con1, con2);
    CheckOP(OP_ADD, con1.GetType());
    switch(con1.GetType()) {
    case CONST_INT:
        return Constant(con1.GetInt() / con2.GetInt());
    case CONST_DOUBLE:
        return Constant(con1.GetDouble() / con2.GetDouble());
    default:
        return Constant();
    }
}
