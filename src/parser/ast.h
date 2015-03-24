#ifndef AST_H
#define AST_H
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cerr;
using std::endl;

enum ST {
    ST_EMPTY,
    ST_BLOCK,
    ST_VAR,
    ST_ARRAY,
    ST_FUNC,
    ST_EXP
};

class AST_Block;
class AST_Statement;
class AST_Var;
class AST_Array;
class AST_Func;
class AST_Expression;

class AST_Statement {
public:
    AST_Statement(ST _type) : type(_type) {};
    ST GetType() { return type;}

    ST type;
};

class AST_Block : public AST_Statement {
public:
    AST_Block() : AST_Statement(ST_BLOCK) {};
    void AddStatement(AST_Statement* st) {
        statements.push_back(st);
    }

    vector<AST_Statement*> statements;
};

class AST_Var : public AST_Statement {
public:
    AST_Var(string _id) : AST_Statement(ST_VAR), id(_id), val(NULL) {}
    AST_Var(string _id, AST_Expression *_e)
        : AST_Statement(ST_VAR), id(_id), val(_e) {}

    string id;
    AST_Expression *val;
};

class AST_Array : public AST_Statement {
public:
    AST_Array(string _id, int _sz)
        : AST_Statement(ST_ARRAY), id(_id), sz_array(_sz) {}

    void AddElement(AST_Expression *e) {
        if (ve.size() > sz_array) {
            cerr << "Error in AST_Array: too many elements for the array" << endl;
            exit(0);
        }
        ve.push_back(e);
    }

    string id;
    int sz_array;
    vector<AST_Expression*> ve;
};

class AST_Func : public AST_Statement {
public:
    AST_Func(string _id)
        : AST_Statement(ST_FUNC),
          id(_id) {}

    void AddArgument(string arg) {
        vp.push_back(arg);
    }
    void AddFunctionBody(AST_Block *_b) {
        block = _b;
    }

    std::string id;
    std::vector<string> vp;
    AST_Block *block;
};

class AST_Expression : public AST_Statement {
public:
    AST_Expression(Operand *_o)
        : AST_Statement(ST_EXP),
          o(_o),
          is_leaf(true){}
    AST_Expression(AST_Expression* _e1, OP _op, AST_Expression* _e2)
        : AST_Statement(ST_EXP),
          e1(_e1),
          e2(_e2),
          op(_op),
          is_leaf(false){}

    bool IsLeaf() { return is_leaf;}

    AST_Expression *e1, *e2;
    OP op;
    // For the leaf expression
    Operand *o;
    bool is_leaf;
};

#endif
