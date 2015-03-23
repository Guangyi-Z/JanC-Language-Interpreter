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

void Constant::TypeUpGrade() {
    switch(type) {
        case CONST_INT:
            SetValue((double)GetInt());
            break;
        case CONST_DOUBLE:
            break;
        default:
            cout << "Error in TypeUpGrade: type- " << type << endl;
            exit(0);
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
