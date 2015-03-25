#include "interpreter.h"

/* Interpreter Start Point */
vector<Command*> Interpreter::IntrStatement (AST_Statement *st) {
    switch(st->type) {
    case ST_EMPTY:
        return {};
    case ST_BLOCK:
        return IntrBlock((AST_Block*)st);
    case ST_EXP:
        {
        Constant con = Expression::CalcExp(cur_sym, &fsym, (AST_Expression*)st);
        con.Print();
        }
        return {};
    case ST_FUNC:
        IntrFunc((AST_Func *)st);
        return {};
    case ST_VAR:
    case ST_ARRAY:
        IntrVar(st);
        return {};
    default:
        cout << "Error in IntrStatement: wrong type for default" << endl;
        exit(0);
    };
}

vector<Command*> Interpreter::IntrBlock(AST_Block* block) {
    vector<Command*> vc;
    vc.push_back(new CommNewSymbolTable());
    for (AST_Statement *st : block->statements) {
        vc.push_back(new CommInterprete(st));
    }
    vc.push_back(new CommDelSymbolTable());
    return vc;
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


/********************************************
 * Command
 *******************************************/
vector<Command*> CommInterprete::Execute(Interpreter &intr) {
    return intr.IntrStatement(st);
}

vector<Command*> CommNewSymbolTable::Execute(Interpreter &intr) {
    intr.NewSymbolTable();
    return {};
}

vector<Command*> CommDelSymbolTable::Execute(Interpreter &intr) {
    intr.DelSymbolTable();
    return {};
}

vector<Command*> CommNewFuncSymbolTable::Execute(Interpreter &intr) {
    intr.NewFuncSymbolTable();
    return {};
}

vector<Command*> CommDelFuncSymbolTable::Execute(Interpreter &intr) {
    intr.DelFuncSymbolTable();
    return {};
}
