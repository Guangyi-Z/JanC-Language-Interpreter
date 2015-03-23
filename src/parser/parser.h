#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "lexer/token.h"
#include "operand.h"
#include "ast.h"

class Parser {
public:
    Parser(){};
    Parser(std::string path_to_file) {
        Load(path_to_file);
    }
    ~Parser() {};
    void Load(std::string path_to_file) {
        lexer.Load(path_to_file);
        lexer.GetNextToken();
    }
    void Parse();
    AST_Statement* ParseStatement();
    AST_Block* ParseBlock();
    AST_Func* ParseFunc();

    AST_Statement* ParseVar();
    AST_Array* ParseArray(string name);
    AST_Var* ParseSingleVar(string name);

    AST_Expression* ParseExpression();
    AST_Expression* ParseExpressionHelper(AST_Expression* e1, OP op);

private:
    OP GetNextOP();
    AST_Expression* GetNextOperand();
    bool IsTheEndOfExp(TOKEN t);
    void FindPrefixOP(Operand &o);
    void FindSuffixOP(Operand &o);
    bool EatToken(TOKEN t);
    bool IsNextOPEquals(OP op);
    bool IsNextTokenEquals(TOKEN t);

    Lexer lexer;
    OpProperty pp;
};


#endif


