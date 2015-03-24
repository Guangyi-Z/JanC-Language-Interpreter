#ifndef SYMBOL_H
#define SYMBOL_H
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include "parser/parser.h"
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;
using std::string;

class FuncTable {
public:
    FuncTable() {}
    AST_Func* LookupSymbol(string name) {
        if (fsym.find(name) != fsym.end())
            return fsym[name];
        else return NULL;
    }
    bool IsSymbolDefined(string name) {
        if (fsym.find(name) != fsym.end())
            return true;
        else return false;
    }
    void AddSymbol(string name, AST_Func *f) {
        if (fsym.find(name) != fsym.end()) {
            cout << "Error in AddSymbol: function symbol \"" << name << "\" has been defined" << endl;
            exit(0);
        }
        fsym[name] = f;
    }
private:
    unordered_map<string, AST_Func*> fsym;
};

class SymbolTable {
public:
    SymbolTable() : parent(NULL) {}
    SymbolTable(SymbolTable *p) : parent(p) {}

    bool IsSymbolDefined(string name) {
        SymbolTable *p = this;
        while(p) {
            if (p->sym.find(name) != p->sym.end())
                return true;
            p = p->GetParent();
        }
        return false;
    }
    SymbolTable* GetParent() { return parent;}
    Constant LookupSymbol(string name) {
        SymbolTable *p = this;
        while(p) {
            if (p->sym.find(name) != p->sym.end())
                return p->sym[name];
            p = p->GetParent();
        }
        return Constant();
    }
    void AddSymbol(string name, Constant con) {
        sym[name] = con;
    }

private:
    unordered_map<string, Constant> sym;
    SymbolTable *parent;
};

#endif
