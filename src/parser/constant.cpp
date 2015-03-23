#include "constant.h"

void Constant::ToNegative() {
    if (type == CONST_INT)
        val.i = -val.i;
    else if (type == CONST_DOUBLE)
        val.d = -val.d;
    else {
        cout << "Error in ToNegative: not allow for type- " << type << endl;
        exit(0);
    }
}
void Constant::ToInc() {
    if (type == CONST_INT)
        val.i++;
    else {
        cout << "Error in ToInc: not allow for type- " << type << endl;
        exit(0);
    }
}
void Constant::ToDec() {
    if (type == CONST_INT)
        val.i--;
    else {
        cout << "Error in ToDec: not allow for type- " << type << endl;
        exit(0);
    }
}
// con1 and con2 will be the same type after the check
void CheckType(Constant &con1, Constant &con2) {
    CONST_T t1 = con1.GetType();
    CONST_T t2 = con2.GetType();
    if (t1 == t2 && t1 != CONST_CHAR)
        return;
    if (t1 == CONST_INT && t2 == CONST_DOUBLE ||
        t1 == CONST_DOUBLE && t2 == CONST_INT ||
        t1 == CONST_ARRAY_INT && t2 == CONST_ARRAY_DOUBLE ||
        t1 == CONST_ARRAY_DOUBLE && t2 == CONST_ARRAY_INT
            ) {
        con1.TypeUpGrade();
        con2.TypeUpGrade();
        return;

    }
    cout << "Error in CheckType: type1- " << t1 << " and type2- " << t2 << endl;
    exit(0);
}

void CheckOP(OP op, CONST_T t) {
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

void Constant::TypeUpGrade() {
    switch(type) {
        case CONST_INT:
            SetValue((double)val.i);
            return;
        case CONST_DOUBLE:
            return;
        default:
            cout << "Error in TypeUpGrade: type- " << type << endl;
            exit(0);
    }
}

Constant Add(Constant con1, Constant con2) {
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
Constant Sub(Constant con1, Constant con2) {
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
Constant Mul(Constant con1, Constant con2) {
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
Constant Div(Constant con1, Constant con2) {
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

void Constant::Print() {
    switch(type) {
        ;
    case CONST_INT:
        cout << ">> " << GetInt() << endl;
        break;
    case CONST_DOUBLE:
        cout << ">> " << GetDouble() << endl;
        break;
    case CONST_CHAR:
        cout << ">> " << GetChar() << endl;
        break;
    case CONST_STRING:
        cout << ">> " << GetString() << endl;
        break;
    case CONST_ARRAY_INT:
        cout << ">> [ ";
        for (int i : GetArrayInt()) {
            cout << i << " ";
        }
        cout << "]" << endl;
        break;
    case CONST_ARRAY_DOUBLE:
        cout << ">> [ ";
        for (double d : GetArrayDouble()) {
            cout << d << " ";
        }
        cout << "]" << endl;
        break;
    default:
        cout << "Empty Constant Instance" << endl;
    }
}
