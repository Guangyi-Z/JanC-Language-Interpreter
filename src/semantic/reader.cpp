#include "reader.h"

int            SymbolReader::ReadVarInt(string name) {
    Constant con = sym->LookupSymbol(name);
    if (con.GetType() == CONST_INT)
        return con.GetInt();
    else {
        cerr << "Error in ReadVarInt" << endl;
        exit(0);
    }
}

double         SymbolReader::ReadVarDouble(string name) {
    Constant con = sym->LookupSymbol(name);
    if (con.GetType() == CONST_DOUBLE)
        return con.GetDouble();
    else {
        cerr << "Error in ReadVarDouble" << endl;
        exit(0);
    }
}

char           SymbolReader::ReadVarChar(string name) {
    Constant con = sym->LookupSymbol(name);
    if (con.GetType() == CONST_CHAR)
        return con.GetChar();
    else {
        cerr << "Error in ReadVarChar" << endl;
        exit(0);
    }
}

string         SymbolReader::ReadVarString(string name) {
    Constant con = sym->LookupSymbol(name);
    if (con.GetType() == CONST_STRING)
        return con.GetString();
    else {
        cerr << "Error in ReadVarString" << endl;
        exit(0);
    }
}

vector<int>    SymbolReader::ReadArrayInt(string name) {
    Constant con = sym->LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_INT)
        return con.GetArrayInt();
    else {
        cerr << "Error in ReadArrayInt" << endl;
        exit(0);
    }
}

vector<double> SymbolReader::ReadArrayDouble(string name) {
    Constant con = sym->LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_DOUBLE)
        return con.GetArrayDouble();
    else {
        cerr << "Error in ReadArrayDouble" << endl;
        exit(0);
    }
}

int SymbolReader::ReadArraySize(string name) {
    Constant con = sym->LookupSymbol(name);
    if (con.GetType() == CONST_ARRAY_DOUBLE || con.GetType() == CONST_ARRAY_INT)
        return con.GetArraySize();
    else {
        cerr << "Error in ReadArraySize" << endl;
        exit(0);
    }
}
