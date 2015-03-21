#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <queue>
#include "symbol.h"
#include "parser/parser.h"
using std::queue;

class Interpreter {
public:
    Interpreter() {}
    Interpreter(string path_to_file) : Interpreter() { Load(path_to_file);}
    void Load(string path_to_file) {
        parser.Load(path_to_file);
        AST_Statement* st = parser.ParseStatement();
        while(st) {
            qst.push(st);
            st = parser.ParseStatement();
        }
    }

    void Interpret (AST_Statement *st);
    bool HasNextStatement();
    void NextStatement();
    void Continue();

    int ReadVarInt(string name);
    double ReadVarDouble(string name);
    char ReadVarChar(string name);
    string ReadVarString(string name);
    vector<int> ReadArrayInt(string name);
    vector<double> ReadArrayDouble(string name);
    int ReadArraySize(string name);

private:

    queue<AST_Statement*> qst;
    Parser parser;
    SymbolTable sym;
    FuncTable fsym;
};

#endif
