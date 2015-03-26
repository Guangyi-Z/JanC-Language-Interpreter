#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "lexer/token.h"
#include "operand.h"
#include "ast.h"

class Parser {
public:
    /* constructor */
    Parser(){};
    Parser(std::string path_to_file) {
        Load(path_to_file);
    }
    ~Parser() {};
    void Load(std::string path_to_file) {
        lexer.Load(path_to_file);
        lexer.GetNextToken();
    }

    /* Parsing Interfaces */
    AST_Statement* ParseStatement();
private:
    /* parser fucntions */
    AST_Block* ParseBlock();
    AST_Func* ParseFunc();
    AST_Statement* ParseVar();
    AST_Array* ParseArray(string name);
    AST_Var* ParseSingleVar(string name);
    AST_If* ParseIf();
    AST_While* ParseWhile();

    /* Parsing Expresion */
    AST_Expression* ParseExpression();
    AST_Expression* ParseExpressionHelper(AST_Expression* e1, OP op);
    OP GetNextOP();
    AST_Expression* GetNextExpression();
    bool IsTheEndOfExp(TOKEN t);
    vector<OP> FindPrefixOP();
    vector<OP> FindSuffixOP();
    Literal* FindLiteral();
    Reference* FindReference();

    /* Util */
    bool EatToken(TOKEN t);

    Lexer lexer;
    OpProperty pp;
};

#endif


