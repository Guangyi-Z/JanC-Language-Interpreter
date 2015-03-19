#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "lexer/token.h"
#include "exp.h"

class AST_Block;
class AST_Statement;
class AST_Var;
class AST_Func;
class AST_Expression;
class AST_ExpressionOperand;

enum ST {
    ST_EMPTY,
    ST_BLOCK,
    ST_VAR,
    ST_FUNC,
    ST_EXP
};

class AST_Statement {
public:
    AST_Statement(ST _type, AST_Block *_block) : type(_type), block(_block) {};

    ST type;
    AST_Block *block;
};

class AST_Block {
public:
    AST_Block(){};
    void AddStatement(AST_Statement* st) {
        statements.push_back(st);
    }

    std::vector<AST_Statement*> statements;
};

class AST_Var : public AST_Statement {
public:
    AST_Var(ST _type, std::string _id, bool _is_array = false, int _sz_array = -1)
        : AST_Statement(_type, NULL), id(_id), is_array(_is_array), sz_array(_sz_array) {}

    std::string id;
    bool is_array;
    int sz_array;
};

class AST_Func : public AST_Statement {
public:
    AST_Func(ST _type, std::string _id, std::vector<AST_Var*> _paras = {})
        : AST_Statement(_type, NULL), id(_id), paras(_paras) {}

    std::string id;
    std::vector<AST_Var*> paras;
};

enum EXP_T {
    EXP_INT,
    EXP_DOUBLE,
    EXP_EXP
};

class AST_ExpressionOperand {
public:
    AST_ExpressionOperand() {}

    void SetOperand(EXP_T _type, int iv) {
        type = _type;
        val.iv = iv;
    }
    void SetOperand(EXP_T _type, double dv) {
        type = _type;
        val.dv = dv;
    }
    void SetOperand(EXP_T _type, AST_Expression* ev) {
        type = _type;
        val.ev = ev;
    }
    void AddPrefixOP(OP op) {
        prefix.push_back(op);
    }
    void AddSuffixOP(OP op) {
        suffix.push_back(op);
    }

    EXP_T type;
    union v {
        int iv;
        double dv;
        AST_Expression *ev;
    } val;
    std::vector<OP> prefix, suffix;
};

class AST_Expression : public AST_Statement {
public:
    AST_Expression() : AST_Statement(ST_EXP, NULL), op(OP_NONE) {}
    AST_Expression(AST_ExpressionOperand _o1)
        : AST_Statement(ST_EXP, NULL),
          o1(_o1),
          op(OP_NONE),
          is_leaf(true){}
    AST_Expression(AST_ExpressionOperand _o1, OP _op, AST_ExpressionOperand _o2)
        : AST_Statement(ST_EXP, NULL),
          o1(_o1),
          o2(_o2),
          op(_op),
          is_leaf(false){}

    AST_ExpressionOperand o1, o2;
    OP op;
    bool is_leaf;
};

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
        for (auto op : OP_Precedence) {
            mOP.insert(op);
        }
    }
    void Parse();
    AST_Statement* ParseStatement();
    AST_Block* ParseBlock();
    AST_Var* ParseVar();
    AST_Func* ParseFunc();

    AST_Expression* ParseExpression();
    OP GetNextOP();
    AST_ExpressionOperand GetNextOperand();
    AST_Expression* ParseExpressionHelper(AST_ExpressionOperand o1, OP op);

private:
    bool EatToken(TOKEN t);

    std::map<OP, int> mOP;
    Lexer lexer;
    OpProperty pp;
};


#endif


