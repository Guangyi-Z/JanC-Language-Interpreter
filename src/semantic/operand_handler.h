#ifndef OPERAND_HANDLER
#define OPERAND_HANDLER
#include "ast/ast.h"
#include "interpreter.h"

class OperandHandler;

class OperandHandlerFactory {
public:
    static OperandHandler* GetOperandHandler(Operand *o);
private:
    OperandHandlerFactory(){}
};

class OperandHandler {
public:
    OperandHandler() {}

    virtual Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) = 0;
private:
    ;
};

class LiteralHandler : public OperandHandler {
public:
    LiteralHandler(Literal* _l) : l(_l) {}

    Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val);
private:

    Literal *l;
};

class RefArrayHandler : public OperandHandler {
public:
    RefArrayHandler(RefArray* _r) : r(_r) {}

    Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val);
private:

    RefArray *r;
};

class RefFuncHandler : public OperandHandler {
public:
    RefFuncHandler(RefFunc* _r) : r(_r) {}

    Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val);
private:

    RefFunc *r;
};

class ReferenceHandler : public OperandHandler {
public:
    ReferenceHandler(Reference* _r) : r(_r) {}

    Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val);
private:

    Reference *r;
};

#endif
