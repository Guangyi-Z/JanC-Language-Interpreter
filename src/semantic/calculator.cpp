#include "calculator.h"

/********************************************
 * Interfaces
 *******************************************/
void Calculator::ExecStatement(AST_Statement* st) {
    qt.push_back(st);
}

void Calculator::ExecNext() {
    if(HasNext())
        IntrStatement();
}

bool Calculator::HasNext() {
    if (qt.empty())
        return false;
    while(!qt.empty()) {
        Task task = qt.front();
        switch(task.type) {
        case TASK_ST:
            return true;
        case TASK_RM_SYMBOL_TABLE:
            cur_sym = cur_sym->GetParent();
            qt.pop_front();
            break;
        default: ;
        }
    }
    return false;
}

void Calculator::Continue() {
    while(HasNext())
        IntrStatement();
}

/********************************************
 * Interpreter Methods
 *******************************************/

AST_Statement* Calculator::Next() {
    if (HasNext()) {
        AST_Statement *st = (AST_Statement*)(qt.front().p);
        qt.pop_front();
        return st;
    }
    return NULL;
}

/* Interpreter Start Point */
void Calculator::IntrStatement () {
    AST_Statement *st = Next();
    switch(st->type) {
    case ST_EMPTY:
        break;
    case ST_BLOCK:
        {
            IntrBlock((AST_Block*)st);
        }
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

void Calculator::IntrBlock(AST_Block* block) {
    cur_sym = new SymbolTable(cur_sym);
    qt.push_front(Task(TASK_RM_SYMBOL_TABLE));
    for (auto it = block->statements.rbegin(); it!=block->statements.rend(); it++) {
        qt.push_front(*it);
    }
    IntrStatement();
}

Constant Calculator::IntrArrayContent(AST_Array *array) {
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

void Calculator::IntrVar(AST_Statement *st) {
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

void Calculator::IntrFunc(AST_Func* func) {
    fsym.AddSymbol(func->id, func);
}

