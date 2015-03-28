#ifndef OPERAND_H
#define OPERAND_H

#include "op/op.h"
#include "type/arithmetic.h"

class AST_Expression;
class AST_Func;
class AST_Var;

enum OPRD_T {
    OPRD_LITERAL,
    OPRD_REFARRAY,
    OPRD_REFFUNC,
    OPRD_REF
};

class Operand {
public:
    Operand (OPRD_T t) : type(t) {}

    OPRD_T GetType()               { return type;}

    void AddPrefixOP(OP op)  { prefix.push_back(op);}
    void AddSuffixOP(OP op)  { suffix.push_back(op);}
    vector<OP> GetPrefixOP() { return prefix;}
    vector<OP> GetSuffixOP() { return suffix;}
    Constant* DoPrefixAssignableOP(Constant *corder);
    Constant* DoPrefixUnassignableOP(Constant *corder);
    Constant* DoSuffixAssignableOP(Constant* corder);
private:

    OPRD_T type;
    std::vector<OP> prefix, suffix;
};

class Literal : public Operand {
public:
    Literal () : Operand(OPRD_LITERAL) { }
    Literal (Constant* _con) : Literal() { SetConst(_con);}

    void SetConst (Constant* _con)   { con = _con;}
    Constant* GetConst()             { return con;}
    CONST_T GetLiteralType()        { return con->GetType();}
private:
    Constant* con;
};

class Reference : public Operand {
public:
    Reference (string _id) : Operand(OPRD_REF) { id = _id;}
    Reference (OPRD_T _t, string _id) : Operand(_t) { id = _id;}

    string GetID()                          { return id;}
private:
    string id;
};

class RefArray : public Reference {
public:
    RefArray (string _id) : Reference(OPRD_REFARRAY, _id) {}

    void SetIndex(AST_Expression* e) { eindex = e;}
    AST_Expression* GetIndex()       { return eindex;}
private:
    string id;
    AST_Expression* eindex;
};

class RefFunc : public Reference {
public:
    RefFunc (string _id) : Reference(OPRD_REFFUNC, _id) {}

    void AddParameter(AST_Expression *e)    { vp.push_back(e);}
    bool IsEmptyParameter()                 { return vp.empty();}
    int GetNumOfParameter()                 { return vp.size();}
    vector<AST_Expression*> GetParameters() { return vp;}
private:
    string id;
    vector<AST_Expression*> vp;
};

#endif
