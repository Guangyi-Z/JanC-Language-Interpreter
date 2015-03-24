#include "interpreter.h"

/********************************************
 * Interfaces
 *******************************************/
void Interpreter::AddStatement(AST_Statement *st) {
    qst.push(st);
}

bool Interpreter::HasNextStatement() {
    if (qst.empty())
        return false;
    return true;
}

void Interpreter::Continue() {
    while(HasNextStatement())
        IntrStatement();
}

/* Interpreter Start Point */
void Interpreter::IntrStatement () {
    AST_Statement *st = qst.front(); qst.pop();
    switch(st->type) {
    case ST_EMPTY:
        break;
    case ST_BLOCK:
        break;
    case ST_EXP:
        {
        Constant con = Expression::CalcExp(sym, fsym, (AST_Expression*)st);
        con.Print();
        }
        break;
    case ST_FUNC:
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
Constant Interpreter::IntrArrayContent(AST_Array *array) {
    if (array->ve.empty())
        return Constant();  // not initialized

    bool is_double = false;
    vector<Constant> vc;
    for (AST_Expression* e : array->ve) {
        Constant _con = Expression::CalcExp(sym, fsym, e);
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
        sym.AddSymbol(array->id, val);
    }
    else {
        AST_Var *var = (AST_Var*) st;
        Constant val;
        if (var->val)
            val = Expression::CalcExp(sym, fsym, var->val);
        sym.AddSymbol(var->id, val);
    }
}

void Interpreter::IntrFunc(AST_Func* func) {
    /* todo */
}


/********************************************
 * Symbol Reader
 *******************************************/

// AST_Func* Interpreter::ReadFunc(string name) {
//     return fsym.LookupSymbol(name);
// }
//
// Constant Interpreter::ReadVar(string name) {
//     return sym.LookupSymbol(name);
// }

int            Interpreter::ReadVarInt(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_INT)
        return con.GetInt();
    else {
        cerr << "Error in ReadVarInt" << endl;
        exit(0);
    }
}

double         Interpreter::ReadVarDouble(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_DOUBLE)
        return con.GetDouble();
    else {
        cerr << "Error in ReadVarDouble" << endl;
        exit(0);
    }
}

char           Interpreter::ReadVarChar(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_CHAR)
        return con.GetChar();
    else {
        cerr << "Error in ReadVarChar" << endl;
        exit(0);
    }
}

string         Interpreter::ReadVarString(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_STRING)
        return con.GetString();
    else {
        cerr << "Error in ReadVarString" << endl;
        exit(0);
    }
}

vector<int>    Interpreter::ReadArrayInt(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_INT)
        return con.GetArrayInt();
    else {
        cerr << "Error in ReadArrayInt" << endl;
        exit(0);
    }
}

vector<double> Interpreter::ReadArrayDouble(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_DOUBLE)
        return con.GetArrayDouble();
    else {
        cerr << "Error in ReadArrayDouble" << endl;
        exit(0);
    }
}

int Interpreter::ReadArraySize(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_DOUBLE || con.GetType() == CONST_ARRAY_INT)
        return con.GetArraySize();
    else {
        cerr << "Error in ReadArraySize" << endl;
        exit(0);
    }
}
