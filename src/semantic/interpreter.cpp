#include "interpreter.h"

/* Interpreter Start Point */
void Interpreter::IntrStatement (AST_Statement *st) {
    switch(st->type) {
    case ST_EMPTY:
        break;
    case ST_BLOCK:
        IntrBlock((AST_Block*)st);
        break;
    case ST_EXP:
        {
        Constant con = Expression::CalcExp(cur_sym, &fsym, (AST_Expression*)st);
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
    NewSymbolTable();
    for (AST_Statement *st : block->statements) {
        IntrStatement(st);
    }
    DelSymbolTable();
}

Constant Interpreter::IntrArrayContent(AST_Array *array) {
    if (array->ve.empty())
        return Constant();  // not initialized

    bool is_double = false;
    vector<Constant> vc;
    for (AST_Expression* e : array->ve) {
        Constant _con = Expression::CalcExp(cur_sym, &fsym, e);
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
        if (cur_sym->IsSymbolDefined(array->id)) {
            cerr << "Error in IntrVar: symbol " << array->id << " has been defined" << endl;
            exit(0);
        }
        cur_sym->AddSymbol(array->id, val);
    }
    else {
        AST_Var *var = (AST_Var*) st;
        Constant val;
        if (var->val)
            val = Expression::CalcExp(cur_sym, &fsym, var->val);
        if (cur_sym->IsSymbolDefined(var->id)) {
            cerr << "Error in IntrVar: symbol " << var->id << " has been defined" << endl;
            exit(0);
        }
        cur_sym->AddSymbol(var->id, val);
    }
}

void Interpreter::IntrFunc(AST_Func* func) {
    fsym.AddSymbol(func->id, func);
    // vector<Command*> vc;
    // vc.push_back(CommNewFuncSymbolTable());
    // vc.push_back(CommDelFuncSymbolTable());
}
