#include "exp.h"

Constant Expression::CalcExp(SymbolTable &sym,
        FuncTable &fsym,
        AST_Expression *exp) {
    if (exp->IsLeaf()) {
        return Expression::CalcOperand(sym, fsym, exp->o);
    }
    Constant con1 = CalcExp(sym, fsym, exp->e1);
    Constant con2 = CalcExp(sym, fsym, exp->e2);
    switch(exp->op) {
    case OP_ADD:
        return Arithmetic::Add(con1, con2);
    case OP_SUB:
        return Arithmetic::Sub(con1, con2);
    case OP_MUL:
        return Arithmetic::Mul(con1, con2);
    case OP_DIV:
        return Arithmetic::Div(con1, con2);
    default:
        return Constant();
    }
}

void Expression::DoPrefixOP(Operand *o) {
    if (o->GetPrefix().empty())
        return;
    for (OP op : o->GetPrefix()) {
        switch(op) {
            case OP_ADD:
                /* empty */
                break;
            case OP_SUB:
                o->ToNegative();
                break;
            case OP_INC:
                o->ToInc();
                break;
            case OP_DEC:
                o->ToDec();
                break;
            case OP_NOT:
                /* to do */
                break;
            default: ;
        }
    }
}

void Expression::DoSuffixOP(Operand *o) {
    if (o->GetSuffix().empty())
        return;
    for (OP op : o->GetSuffix()) {
        switch(op) {
            case OP_INC:
                o->ToInc();
                break;
            case OP_DEC:
                o->ToDec();
                break;
            default: ;
        }
    }
}

Constant Expression::CalcOperand(SymbolTable &sym, FuncTable &fsym, Operand *o) {
    Constant con;
    if (o->GetType() == OPRD_LITERAL) {
        Literal *l = (Literal*) o;
        DoPrefixOP(l);
        con = l->GetConst();  // con is independent of suffix operations
        DoSuffixOP(l);
    }
    else {
        Reference *r = (Reference*) o;
        /* todo */

        // // var
        // Constant con = sym.LookupSymbol(r->GetID());
        // if (con.GetType() != CONST_NONE) {
        //     if (r->IsEmptyParameter())
        //         return con;
        //     else {
        //         int index = CalcExp(r->GetParameters()[0]).GetInt();
        //         switch(con.GetType()) {
        //         case CONST_ARRAY_INT:
        //             return Constant(con.GetArrayInt()[index];
        //         case CONST_ARRAY_DOUBLE:
        //             return Constant(con.GetArrayDouble()[index];
        //         }
        //     }
        // }
        // // func
        // else if (fsym.LookupSymbol(r->GetID()))
        //     con = CalcFunc(sym, fsym, r);
        // else {
        //     cout << "Error in CalcOperand: symbol not defined- " << o.GetID() << endl;
        //     exit(0);
        // }
    }
    return con;
}

Constant Expression::CalcVar(SymbolTable &sym, FuncTable &fsym, Operand *o) {
    return Constant();
}

Constant Expression::CalcFunc(SymbolTable &sym, FuncTable &fsym, Operand *o) {
    return Constant();
}

