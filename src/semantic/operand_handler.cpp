#include "operand_handler.h"

/**********************
 * OperandHandlerFactory
 */

OperandHandler* OperandHandlerFactory::GetOperandHandler(Operand *o) {
    switch(o->GetType()) {
    case OPRD_LITERAL:
        return new LiteralHandler((Literal*)o);
    case OPRD_REFARRAY:
        return new RefArrayHandler((RefArray*)o);
    case OPRD_REFFUNC:
        return new RefFuncHandler((RefFunc*)o);
    case OPRD_REF:
        return new ReferenceHandler((Reference*)o);
    default: return NULL;
    }
    return NULL;
}

/**********************
 * OperandHandler
 */

Constant* LiteralHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    Constant *res = l->DoPrefixAssignableOP(l->GetConst());
    /* Literal type has no suffix unary OP,
     * if has, let error happens. */
    l->DoSuffixAssignableOP(res);
    res = l->DoPrefixUnassignableOP(l->GetConst());
    return res;
}

Constant* RefArrayHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    AST_Expression *e = r->GetIndex();
    Constant *cindex = Interpreter::IntrExpression(e, sym, fsym, back);
    if (cindex->GetType() != CONST_INT) {
        cerr << "Error in UnpackVar: array index must be Int- " << cindex->GetType() << endl;
        exit(0);
    }
    int index = ((Int*)cindex)->GetInt();
    Array *arr = (Array*)(sym->GetCurSymbolTable()->LookupSymbol(r->GetID()));
    Constant *res = arr->At(index);
    /* deal with unary OP */
    res = r->DoPrefixAssignableOP(res);
    arr->SetElement(index, r->DoSuffixAssignableOP(res));
    res = r->DoPrefixUnassignableOP(res);
    return res;
}

Constant* RefFuncHandler::illegal_ret_built = new Int(1);
Constant* RefFuncHandler::IntrBuiltinFunc(NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    if (r->GetID() == "len") {
        vector<AST_Expression*> vp = r->GetParameters();
        if (vp.size() != 1) {
            cerr << "Error in IntrBuiltinFunc::len: incorrect args number" << endl;
            exit(0);
        }
        Constant *carr = Interpreter::IntrExpression(vp[0], sym, fsym, back);
        if (carr->GetType() != CONST_ARRAY) {
            cerr << "Error in IntrBuiltinFunc::len: array symbol not defined- " << r->GetID() << endl;
            exit(0);
        }
        Array* arr = (Array*) carr;
        return new Int(arr->GetSize());
    }
    if (r->GetID() == "print") {
        bool is_first = true;
        for (AST_Expression* para: r->GetParameters()) {
            if (!is_first)
                cout << " ";
            else
                is_first = false;
            Constant *con = Interpreter::IntrExpression(para, sym, fsym, back);
            con->Print();
        }
        cout << endl;
        return NULL;
    }
    return illegal_ret_built;
}

void RefFuncHandler::BindFuncArgs(NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    sym->NewFuncSymbolTable();

    AST_Func *func = (AST_Func*)(fsym->LookupSymbol(r->GetID()));
    vector<AST_Expression*> paras = r->GetParameters();
    vector<string> names = func->GetFormalParameters();
    if (paras.size() != names.size()) {
        cerr << "Error in BindFuncArgs: incorrect number of args" << endl;
        exit(0);
    }
    int cnt = 0;
    for (string name : names) {
        Constant* con = Interpreter::IntrExpression(paras[cnt++], sym, fsym, back);
        sym->GetCurSymbolTable()->AddSymbol(name, con);
    }
}

void RefFuncHandler::UnbindFuncArgs(NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    sym->DelFuncSymbolTable();
}

Constant* RefFuncHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    /* Built-in Functions */
    Constant *res_builtin = IntrBuiltinFunc(sym, fsym, back);
    if (illegal_ret_built != res_builtin)
        return res_builtin;

    /* User-defined Functions */
    BindFuncArgs(sym, fsym, back);
    if (!fsym->IsSymbolDefined(r->GetID())) {
        cerr << "Error in IntrOperand: symbol " << r->GetID() << " not defined" << endl;
        exit(0);
    }
    AST_Func *func = (AST_Func*)(fsym->LookupSymbol(r->GetID()));
    for (AST_Statement *st : func->block->statements) {
        Interpreter::IntrStatement(st, sym, fsym, back);
    }
    UnbindFuncArgs(sym, fsym, back);
    Constant *res = *back;
    *back = NULL;
    /* Function return type has no unary OP,
     * if has, let error happens. */
    res = r->DoPrefixAssignableOP(res);
    r->DoSuffixAssignableOP(res);
    res = r->DoPrefixUnassignableOP(res);
    return res;
}

Constant* ReferenceHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    Constant* con = sym->GetCurSymbolTable()->LookupSymbol(r->GetID());
    if (!con)
        cerr << "Error in IntrOperand: symbol not defined- " << r->GetID() << endl;
    if (con->GetType() == CONST_ARRAY) {
        /* array ref */
        return con;
    }
    else {
        /* single var */
        /* deal with unary OP */
        Constant *res = con;
        res = r->DoPrefixAssignableOP(res);
        sym->GetCurSymbolTable()->ChangeSymbol(r->GetID(), r->DoSuffixAssignableOP(res));
        res = r->DoPrefixUnassignableOP(res);
        return res;
    }

    /* todo */
    // Ref to array or func
}
