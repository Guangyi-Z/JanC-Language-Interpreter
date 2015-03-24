#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <deque>
#include "symbol.h"
#include "exp.h"
#include "parser/parser.h"
using std::deque;
using std::cerr;

enum TASK_T {
    TASK_ST,
    TASK_RM_SYMBOL_TABLE
};

class Task {
public:
    Task(TASK_T t) : type(t), p(NULL) {}
    Task(AST_Statement* st) : type(TASK_ST), p(st) {}

    TASK_T type;
    void *p;
};

class Interpreter {
public:
    /* construtor */
    Interpreter() {
        cur_sym = &sym;
    }
    Interpreter(string path_to_file) : Interpreter() { Load(path_to_file);}
    void Load(string path_to_file) {
        parser.Load(path_to_file);
        AST_Statement* st = parser.ParseStatement();
        while(st) {
            qst.push_back(st);
            st = parser.ParseStatement();
        }
    }

    /* interpreter */
    void IntrVar(AST_Statement *st);
    void IntrFunc(AST_Func* func);
    Constant IntrArrayContent(AST_Array *array);
    void IntrBlock(AST_Block* block);

    /* interfaces */
    bool HasNextStatement();
    AST_Statement* NextStatement();
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

    deque<Task> qst;
    Parser parser;
    SymbolTable sym;  // global symbol table
    SymbolTable *cur_sym;
    FuncTable fsym;
};

#endif
