#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <queue>
#include "symbol.h"
#include "exp.h"
#include "parser/parser.h"
using std::queue;
using std::cerr;

class Interpreter {
public:
    /* construtor */
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

    /* interpreter */
    void IntrVar(AST_Statement *st);
    void IntrFunc(AST_Func* func);
    Constant IntrArrayContent(AST_Array *array);

    /* interfaces */
    bool HasNextStatement();
    void IntrStatement ();
    void AddStatement(AST_Statement *st);
    void Continue();

    /* symbol reader */
    // Constant ReadVar(string name);
    // AST_Func* ReadFunc(string name);
    // Literal type
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
