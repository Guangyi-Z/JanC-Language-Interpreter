#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <deque>
#include "symbol.h"
#include "reader.h"
#include "calculator.h"
#include "parser/parser.h"
using std::deque;
using std::cerr;

class Interpreter {
public:
    /* construtor */
    Interpreter() {
        is_debug = false;
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

    /* interfaces */
    bool HasNextStatement();
    void NextStatement();
    void AddStatement(AST_Statement *st);
    void Continue();

    /* debug */
    void SetDebugMode(bool b) { is_debug = b;}
    bool IsEndOfCommand() { return !calc.HasNext();}
    void NextCommand() { calc.ExecNext();}
    void ContinueCommand() { calc.Continue();}

    /* reader */
    SymbolReader GetSymbolReader() { return calc.GetSymbolReader();}

private:

    bool is_debug;
    Calculator calc;
    deque<AST_Statement*> qst;
    Parser parser;
};

#endif
