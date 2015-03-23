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
    SymbolTable(){
        unordered_map<string, Constant> m;
        lsym.push_back(m);  // global symbol table
    }
    void CreateNewFrame() {
        unordered_map<string, Constant> m;
        lsym.push_back(m);
    }
    void RemoveCurFrame() {
        if (lsym.empty()) {
            cout << "Error in RemoveCurFrame(): lsym is empty" << endl;
            exit(0);
        }
        lsym.pop_back();
    }
    Constant LookupSymbol(string name) {
        for (auto it = lsym.rbegin(); it!=lsym.rend(); it++) {
            if (it->find(name) != it->end()) {
                return (*it)[name];
            }
        }
        return Constant();
    }
    void AddSymbol(string name, Constant con) {
        unordered_map<string, Constant> &m = lsym.back();
        if (m.find(name) != m.end()) {
            cout << "Error in AddSymbol: symbol \"" << name << "\" has been defined" << endl;
            exit(0);
        }
        m[name] = con;
    }

private:
    vector<unordered_map<string, Constant> > lsym;
};

#endif
