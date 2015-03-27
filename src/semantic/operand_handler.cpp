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
    return l->GetConst();
}

Constant* RefArrayHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    AST_Expression *e = r->GetIndex();
    Constant *cindex = Interpreter::IntrExpression(e, sym, fsym, ret_val);
    if (cindex->GetType() != CONST_INT) {
        cerr << "Error in UnpackVar: array index must be Int- " << cindex->GetType() << endl;
        exit(0);
    }
    int index = ((Int*)cindex)->GetInt();
    return ((Array*)cindex)->At(index);
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
    return res;
}

Constant* ReferenceHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    Constant* con = sym->GetCurSymbolTable()->LookupSymbol(r->GetID());
    if (!con)
        cerr << "Error in IntrOperand: symbol not defined- " << r->GetID() << endl;
    return con;
    /* todo */
    // Ref to array or func
}
