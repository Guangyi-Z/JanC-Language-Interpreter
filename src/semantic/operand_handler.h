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

    virtual Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym) = 0;
private:
    virtual void DoPrefixOP() = 0;
    virtual void DoSuffixOP() = 0;
};

class LiteralHandler : public OperandHandler {
public:
    LiteralHandler(Literal* _l) : l(_l) {}

    Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym);
private:
    void DoPrefixOP() {}
    void DoSuffixOP() {}

    Literal *l;
};

class RefArrayHandler : public OperandHandler {
public:
    RefArrayHandler(RefArray* _r) : r(_r) {}

    Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym);
private:
    void DoPrefixOP() {}
    void DoSuffixOP() {}

    RefArray *r;
};

class RefFuncHandler : public OperandHandler {
public:
    RefFuncHandler(RefFunc* _r) : r(_r) {}

    Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym);
private:
    void DoPrefixOP() {}
    void DoSuffixOP() {}

    RefFunc *r;
};

class ReferenceHandler : public OperandHandler {
public:
    ReferenceHandler(Reference* _r) : r(_r) {}

    Constant* IntrOperand(NestedSymbolTable *sym, FuncTable *fsym);
private:
    void DoPrefixOP() {}
    void DoSuffixOP() {}

    Reference *r;
};

// void Interpreter::DoPrefixOP(Operand *o) {
//     if (o->GetPrefix().empty())
//         return;
//     for (OP op : o->GetPrefix()) {
//         switch(op) {
//             case OP_ADD:
//                 /* empty */
//                 break;
//             case OP_SUB:
//                 o->ToNegative();
//                 break;
//             case OP_INC:
//                 o->ToInc();
//                 break;
//             case OP_DEC:
//                 o->ToDec();
//                 break;
//             case OP_NOT:
//                 /* to do */
//                 break;
//             default: ;
//         }
//     }
// }
//
// void Interpreter::DoSuffixOP(Operand *o) {
//     if (o->GetSuffix().empty())
//         return;
//     for (OP op : o->GetSuffix()) {
//         switch(op) {
//             case OP_INC:
//                 o->ToInc();
//                 break;
//             case OP_DEC:
//                 o->ToDec();
//                 break;
//             default: ;
//         }
//     }
// }
#endif
