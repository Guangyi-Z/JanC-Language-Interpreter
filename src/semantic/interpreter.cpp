#include "interpreter.h"

/* Interpreter Start Point */
void Interpreter::IntrStatement (AST_Statement *st) {
    if (!st)
        return;
    switch(st->type) {
        break;
    case ST_BLOCK:
        IntrBlock((AST_Block*)st);
        break;
    case ST_EXP:
        {
        Constant con = IntrExpression((AST_Expression*)st);
        con.Print();
        }
        break;
    case ST_FUNC:
        IntrFunc((AST_Func *)st);
        break;
    case ST_VAR:
    case ST_ARRAY:
        IntrVar(st);
        break;
    default:
        cout << "Error in IntrStatement: wrong type for default" << endl;
        exit(0);
    };
}

void Interpreter::IntrBlock(AST_Block* block) {
    sym.NewSymbolTable();
    for (AST_Statement *st : block->statements) {
        IntrStatement(st);
    }
    sym.DelSymbolTable();
}

Constant Interpreter::IntrArrayContent(AST_Array *array) {
    if (array->ve.empty())
        return Constant();  // not initialized

    bool is_double = false;
    vector<Constant> vc;
    for (AST_Expression* e : array->ve) {
        Constant _con = IntrExpression(e);
        vc.push_back(_con);
        if (_con.GetType() == CONST_DOUBLE)
            is_double = true;
    }
    if (is_double) {
        vector<double> vd;
        for (Constant &con : vc)
            vd.push_back(con.GetDouble());
        return Constant(vd, array->sz_array);
    }
    else {
        vector<int> vi;
        for (Constant &con : vc)
            vi.push_back(con.GetInt());
        return Constant(vi, array->sz_array);
    }
}

void Interpreter::IntrVar(AST_Statement *st) {
    Constant con;
    if (st->GetType() == ST_ARRAY) {
        AST_Array *array = (AST_Array*) st;
        Constant val = IntrArrayContent(array);
        if (sym.GetCurSymbolTable()->IsSymbolDefined(array->id)) {
            cerr << "Error in IntrVar: symbol " << array->id << " has been defined" << endl;
            exit(0);
        }
        sym.GetCurSymbolTable()->AddSymbol(array->id, val);
    }
    else {
        AST_Var *var = (AST_Var*) st;
        Constant val;
        if (var->val)
            val = IntrExpression(var->val);
        if (sym.GetCurSymbolTable()->IsSymbolDefined(var->id)) {
            cerr << "Error in IntrVar: symbol " << var->id << " has been defined" << endl;
            exit(0);
        }
        sym.GetCurSymbolTable()->AddSymbol(var->id, val);
    }
}

void Interpreter::IntrFunc(AST_Func* func) {
    fsym.AddSymbol(func->id, func);
}

Constant Interpreter::IntrExpression(AST_Expression* exp) {
    if (exp->IsLeaf()) {
        return IntrOperand(exp->o);
    }
    // For assgiment
    if (exp->op == OP_ASSIGN) {
        AST_Expression *lv = exp->e1;
        Reference *r = (Reference*)(lv->o);
        if (!lv->IsLeaf() || r->GetType() != OPRD_REF) {
            cerr << "Error in IntrExpression: l-value must be assignable" << endl;
            exit(0);
        }
        Constant rv = IntrExpression(exp->e2);
        sym.GetCurSymbolTable()->ChangeSymbol(r->GetID(), rv);
        return rv;
    }
    // Normal recursive process
    Constant con1 = IntrExpression(exp->e1);
    Constant con2 = IntrExpression(exp->e2);
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

Constant Interpreter::IntrOperand(Operand *o) {
    if (o->GetType() == OPRD_LITERAL) {
        Literal *l = (Literal*) o;
        DoPrefixOP(l);
        Constant con = l->GetConst();  // con is independent of suffix operations
        DoSuffixOP(l);
        return con;
    }
    else {
        Reference *r = (Reference*) o;
        if (sym.GetCurSymbolTable()->IsSymbolDefinedRecursively(r->GetID()))    // var
            return UnpackVar(r);
        else if (fsym.LookupSymbol(r->GetID())) // func
            return UnpackFunc(r);
        else {
            cout << "Error in IntrOperand: symbol not defined- " << r->GetID() << endl;
            exit(0);
        }
    }
    /* never been here */
    return Constant();
}

Constant Interpreter::UnpackVar(Reference *r) {
    Constant con = sym.GetCurSymbolTable()->LookupSymbol(r->GetID());
    if (r->IsEmptyParameter())  // single var
        return con;
    // array element
    AST_Expression *e = r->GetParameters()[0];
    Constant cindex = IntrExpression(e);
    if (cindex.GetType() != CONST_INT) {
        cerr << "Error in UnpackVar: array index must be Int- " << cindex.GetType() << endl;
        exit(0);
    }
    int index = cindex.GetInt();
    switch(con.GetType()) {
    case CONST_ARRAY_INT:
        return Constant(con.GetArrayInt()[index]);
    case CONST_ARRAY_DOUBLE:
        return Constant(con.GetArrayDouble()[index]);
    default:
        cerr << "Error in UnpackVar: wrong array type- " << con.GetType() << endl;
        exit(0);
    }
}

Constant Interpreter::UnpackFunc(Reference *r) {
    if (!fsym.IsSymbolDefined(r->GetID())) {
        cerr << "Error in UnpackFunc: symbol " << r->GetID() << " not defined" << endl;
        exit(0);
    }
    sym.NewFuncSymbolTable();
    AST_Func *func = fsym.LookupSymbol(r->GetID());
    AST_Return *rt = (AST_Return*)(func->block->statements[0]);
    Constant con = IntrExpression(rt->e);
    sym.DelFuncSymbolTable();
    return con;
}

void Interpreter::DoPrefixOP(Operand *o) {
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

void Interpreter::DoSuffixOP(Operand *o) {
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
