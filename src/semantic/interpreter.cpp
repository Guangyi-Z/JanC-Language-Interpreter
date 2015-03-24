#include "interpreter.h"

/********************************************
 * Interfaces
 *******************************************/
void Interpreter::AddStatement(AST_Statement *st) {
    qst.push_back(Task(st));
}

bool Interpreter::HasNextStatement() {
    if (qst.empty())
        return false;
    while(!qst.empty()) {
        Task task = qst.front();
        switch(task.type) {
        case TASK_ST:
            return true;
        case TASK_RM_SYMBOL_TABLE:
            cur_sym = cur_sym->GetParent();
            qst.pop_front();
            break;
        default: ;
        }
    }
    return false;
}

AST_Statement* Interpreter::NextStatement() {
    if (HasNextStatement()) {
        Task task = qst.front();
        qst.pop_front();
        return (AST_Statement*)(task.p);
    }
    return NULL;
}

void Interpreter::Continue() {
    while(HasNextStatement())
        IntrStatement();
}

/* Interpreter Start Point */
void Interpreter::IntrStatement () {
    AST_Statement *st = NextStatement();
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

/********************************************
 * Interpreter Methods
 *******************************************/
void Interpreter::IntrBlock(AST_Block* block) {
    cur_sym = new SymbolTable(cur_sym);
    qst.push_front(Task(TASK_RM_SYMBOL_TABLE));
    for (auto it = block->statements.rbegin(); it!=block->statements.rend(); it++) {
        qst.push_front(*it);
    }
    IntrStatement();
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
}

