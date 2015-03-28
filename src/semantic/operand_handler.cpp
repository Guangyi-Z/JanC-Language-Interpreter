#include "operand_handler.h"

/**********************
 * OperandHandlerFactory
 */

OperandHandler* OperandHandlerFactory::GetOperandHandler(Operand *o) {
    switch(o->GetType()) {
    case OPRD_LITERAL:
        return new LiteralHandler((Literal*)o);
    case OPRD_REFARRAY:
        return new RefArrayHandler((RefArray*)o);
    case OPRD_REFFUNC:
        return new RefFuncHandler((RefFunc*)o);
    case OPRD_REF:
        return new ReferenceHandler((Reference*)o);
    default: return NULL;
    }
    return NULL;
}

/**********************
 * OperandHandler
 */

Constant* LiteralHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    Constant *res = l->DoPrefixAssignableOP(l->GetConst());
    /* Literal type has no suffix unary OP,
     * if has, let error happens. */
    l->DoSuffixAssignableOP(res);
    res = l->DoPrefixUnassignableOP(l->GetConst());
    return res;
}

Constant* RefArrayHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    AST_Expression *e = r->GetIndex();
    Constant *cindex = Interpreter::IntrExpression(e, sym, fsym, ret_val);
    if (cindex->GetType() != CONST_INT) {
        cerr << "Error in UnpackVar: array index must be Int- " << cindex->GetType() << endl;
        exit(0);
    }
    int index = ((Int*)cindex)->GetInt();
    Constant *res = ((Array*)cindex)->At(index);
    /* deal with unary OP */
    res = r->DoPrefixAssignableOP(res);
    ((Array*)cindex)->SetElement(index, r->DoSuffixAssignableOP(res));
    res = r->DoPrefixUnassignableOP(res);
    return res;
}

Constant* RefFuncHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    if (!fsym->IsSymbolDefined(r->GetID())) {
        cerr << "Error in IntrOperand: symbol " << r->GetID() << " not defined" << endl;
        exit(0);
    }
    sym->NewFuncSymbolTable();
    AST_Func *func = (AST_Func*)(fsym->LookupSymbol(r->GetID()));
    for (AST_Statement *st : func->block->statements) {
        Interpreter::IntrStatement(st, sym, fsym, ret_val);
    }
    sym->DelFuncSymbolTable();
    Constant *res = *ret_val;
    *ret_val = NULL;
    /* Function return type has no unary OP,
     * if has, let error happens. */
    res = r->DoPrefixAssignableOP(res);
    r->DoSuffixAssignableOP(res);
    res = r->DoPrefixUnassignableOP(res);
    return res;
}

Constant* ReferenceHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    Constant* con = sym->GetCurSymbolTable()->LookupSymbol(r->GetID());
    if (!con)
        cerr << "Error in IntrOperand: symbol not defined- " << r->GetID() << endl;
    /* single var */
    /* deal with unary OP */
    Constant *res = con;
    res = r->DoPrefixAssignableOP(res);
    sym->GetCurSymbolTable()->ChangeSymbol(r->GetID(), r->DoSuffixAssignableOP(res));
    res = r->DoPrefixUnassignableOP(res);
    return res;

    /* todo */
    // Ref to array or func
}
