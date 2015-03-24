#include "exp.h"

Constant Expression::CalcExp(SymbolTable *sym,
        FuncTable *fsym,
        AST_Expression *exp) {
    if (exp->IsLeaf()) {
        return Expression::CalcOperand(sym, fsym, exp->o);
    }
    // For assgiment
    if (exp->op == OP_ASSIGN) {
        AST_Expression *lv = exp->e1;
        Reference *r = (Reference*)(lv->o);
        if (!lv->IsLeaf() || r->GetType() != OPRD_REF) {
            cerr << "Error in CalcExp: l-value must be assignable" << endl;
            exit(0);
        }
        Constant rv = CalcExp(sym, fsym, exp->e2);
        sym->AddSymbol(r->GetID(), rv);
        return rv;
    }
    // Normal recursive process
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

Constant Expression::CalcOperand(SymbolTable *sym, FuncTable *fsym, Operand *o) {
    if (o->GetType() == OPRD_LITERAL) {
        Literal *l = (Literal*) o;
        DoPrefixOP(l);
        Constant con = l->GetConst();  // con is independent of suffix operations
        DoSuffixOP(l);
        return con;
    }
    else {
        Reference *r = (Reference*) o;

        // var
        if (sym->IsSymbolDefined(r->GetID())) {
            Constant con = sym->LookupSymbol(r->GetID());
            if (r->IsEmptyParameter())  // single var
                return con;
            else {  // array element
                AST_Expression *e = r->GetParameters()[0];
                Constant cindex = CalcExp(sym, fsym, e);
                if (cindex.GetType() != CONST_INT) {
                    cerr << "Error in CalcOperand: array index must be Int- " << cindex.GetType() << endl;
                    exit(0);
                }
                int index = cindex.GetInt();
                switch(con.GetType()) {
                case CONST_ARRAY_INT:
                    return Constant(con.GetArrayInt()[index]);
                case CONST_ARRAY_DOUBLE:
                    return Constant(con.GetArrayDouble()[index]);
                default:
                    cerr << "Error in CalcOperand: wrong array type- " << con.GetType() << endl;
                    exit(0);
                }
            }
        }
        // func
        /* todo */
        // else if (fsym.LookupSymbol(r->GetID()))
        //     con = CalcFunc(sym, fsym, r);
        else {
            cout << "Error in CalcOperand: symbol not defined- " << r->GetID() << endl;
            exit(0);
        }
    }
    /* never been here */
    return Constant();
}

Constant Expression::CalcVar(SymbolTable *sym, FuncTable *fsym, Operand *o) {
    return Constant();
}

Constant Expression::CalcFunc(SymbolTable *sym, FuncTable *fsym, Operand *o) {
    return Constant();
}

