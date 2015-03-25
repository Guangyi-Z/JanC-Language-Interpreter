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

    bool IsSymbolDefinedRecursively(string name) {
        SymbolTable *p = this;
        while(p) {
            if (p->sym.find(name) != p->sym.end())
                return true;
            p = p->GetParent();
        }
        return false;
    }
    bool IsSymbolDefined(string name) {
        if (sym.find(name) != sym.end())
            return true;
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
    void ChangeSymbol(string name, Constant con) {
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

private:
    unordered_map<string, Constant> sym;
    SymbolTable *parent;
};

class NestedSymbolTable {
public:
    NestedSymbolTable() { cur_sym = &g_sym;}

    /* nested symtable interfaces */
    SymbolTable* GetCurSymbolTable() { return cur_sym;}
    void NewSymbolTable()     { cur_sym = new SymbolTable(cur_sym);}
    void DelSymbolTable()     { cur_sym = cur_sym->GetParent();}
    void NewFuncSymbolTable() { bak_sym = cur_sym; cur_sym = new SymbolTable(&g_sym);}
    void DelFuncSymbolTable() { cur_sym = bak_sym;}
private:
    SymbolTable *cur_sym, *bak_sym;
    SymbolTable g_sym;  // global symbol table
};

#endif
