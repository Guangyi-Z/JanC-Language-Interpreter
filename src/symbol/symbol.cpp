#include "symbol.h"

/*********************
 * FuncTable
 */

void* FuncTable::LookupSymbol(string name) {
    if (fsym.find(name) != fsym.end())
        return fsym[name];
    else return NULL;
}
bool FuncTable::IsSymbolDefined(string name) {
    if (fsym.find(name) != fsym.end())
        return true;
    else return false;
}
void FuncTable::AddSymbol(string name, void *f) {
    if (fsym.find(name) != fsym.end()) {
        cerr << "Error in AddSymbol: function symbol \"" << name << "\" has been defined" << endl;
        exit(0);
    }
    fsym[name] = f;
}

/*********************
 * Symboltable
 */


bool SymbolTable::IsSymbolDefinedRecursively(string name) {
    SymbolTable *p = this;
    while(p) {
        if (p->sym.find(name) != p->sym.end())
            return true;
        p = p->GetParent();
    }
    return false;
}
bool SymbolTable::IsSymbolDefined(string name) {
    if (sym.find(name) != sym.end())
        return true;
    return false;
}

SymbolTable* SymbolTable::GetParent() { return parent;}

Constant* SymbolTable::LookupSymbol(string name) {
    SymbolTable *p = this;
    while(p) {
        if (p->sym.find(name) != p->sym.end())
            return p->sym[name];
        p = p->GetParent();
    }
    return NULL;
}

void SymbolTable::AddSymbol(string name, Constant* con) {
    sym[name] = con;
}

void SymbolTable::ChangeSymbol(string name, Constant* con) {
    SymbolTable *p = this;
    bool is_defined = false;
    while(p) {
        if (p->sym.find(name) != p->sym.end()) {
            p->sym[name] = con;
            is_defined = true;
            break;
        }
        p = p->GetParent();
    }
    if (!is_defined)
        cerr << "Error in ChangeSymbol: symbol not defined- " << name << endl;
}
