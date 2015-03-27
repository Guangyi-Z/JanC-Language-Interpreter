#ifndef SYMBOL_H
#define SYMBOL_H
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include "type/constant.h"
using std::vector;
using std::unordered_map;
using std::cerr;
using std::endl;
using std::string;

class FuncTable {
public:
    FuncTable() {}

    void* LookupSymbol(string name);
    bool IsSymbolDefined(string name);
    void AddSymbol(string name, void *f);
private:
    unordered_map<string, void*> fsym;
};

class SymbolTable {
public:
    SymbolTable() : parent(NULL) {}
    SymbolTable(SymbolTable *p) : parent(p) {}

    bool IsSymbolDefinedRecursively(string name);
    bool IsSymbolDefined(string name);
    SymbolTable* GetParent();
    Constant* LookupSymbol(string name);
    void AddSymbol(string name, Constant* con);
    void ChangeSymbol(string name, Constant* con);
private:
    unordered_map<string, Constant*> sym;
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
