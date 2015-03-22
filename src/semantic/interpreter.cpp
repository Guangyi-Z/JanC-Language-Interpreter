#include "interpreter.h"

void Interpreter::Interpret (AST_Statement *st) {
    qst.push(st);
}

bool Interpreter::HasNextStatement() {
    if (qst.empty())
        return false;
    return true;
}

void Interpreter::NextStatement() {
    AST_Statement *st = qst.front(); qst.pop();
    switch(st->type) {
    case ST_EMPTY:
        break;
    case ST_BLOCK:
        break;
    case ST_EXP:
        break;
    case ST_FUNC:
        break;
    case ST_VAR:
        {
            AST_Var *var = (AST_Var*)st;
            sym.AddSymbol(var->id, var->con);
        }
        break;
    default:
        cout << "Error in NextStatement: wrong type for default" << endl;
        exit(0);
    };
}

void Interpreter::Continue() {
    while(HasNextStatement())
        NextStatement();
}

AST_Func* Interpreter::ReadFunc(string name) {
    return sym.LookupSymbol(name);
}

AST_Expression* Interpreter::ReadVar(string name) {
    return fsym.LookupSymbol(name);
}

int            Interpreter::ReadVarInt(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_INT)
        return con.GetInt();
    else {
        cout << "Error in ReadVarInt" << endl;
        exit(0);
    }
}

double         Interpreter::ReadVarDouble(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_DOUBLE)
        return con.GetDouble();
    else {
        cout << "Error in ReadVarDouble" << endl;
        exit(0);
    }
}

char           Interpreter::ReadVarChar(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_CHAR)
        return con.GetChar();
    else {
        cout << "Error in ReadVarChar" << endl;
        exit(0);
    }
}

string         Interpreter::ReadVarString(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_STRING)
        return con.GetString();
    else {
        cout << "Error in ReadVarString" << endl;
        exit(0);
    }
}

vector<int>    Interpreter::ReadArrayInt(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_INT)
        return con.GetArrayInt();
    else {
        cout << "Error in ReadArrayInt" << endl;
        exit(0);
    }
}

vector<double> Interpreter::ReadArrayDouble(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_DOUBLE)
        return con.GetArrayDouble();
    else {
        cout << "Error in ReadArrayDouble" << endl;
        exit(0);
    }
}

int Interpreter::ReadArraySize(string name) {
    Constant con = sym.LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_DOUBLE || con.GetType() == CONST_ARRAY_INT)
        return con.GetArraySize();
    else {
        cout << "Error in ReadArraySize" << endl;
        exit(0);
    }
}
