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

Constant* LiteralHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym) {
    return l->GetConst();
}

Constant* RefArrayHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym) {
    AST_Expression *e = r->GetIndex();
    Constant *cindex = Interpreter::IntrExpression(e, sym, fsym);
    if (cindex->GetType() != CONST_INT) {
        cerr << "Error in UnpackVar: array index must be Int- " << cindex->GetType() << endl;
        exit(0);
    }
    int index = ((Int*)cindex)->GetInt();
    return ((Array*)cindex)->At(index);
}

Constant* RefFuncHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym) {
    if (!fsym->IsSymbolDefined(r->GetID())) {
        cerr << "Error in UnpackFunc: symbol " << r->GetID() << " not defined" << endl;
        exit(0);
    }
    sym->NewFuncSymbolTable();
    Constant *res = NULL;
    AST_Func *func = (AST_Func*)(fsym->LookupSymbol(r->GetID()));
    for (AST_Statement *st : func->block->statements) {
        if (st->GetType() != ST_RETURN) {
            Interpreter::IntrStatement(st, sym, fsym);
            continue;
        }
        // return
        AST_Return *rt = (AST_Return*)st;
        res = Interpreter::IntrExpression(rt->e, sym, fsym);
        break;
    }
    sym->DelFuncSymbolTable();
    return res;
}

Constant* ReferenceHandler::IntrOperand(NestedSymbolTable *sym, FuncTable *fsym) {
    Constant* con = sym->GetCurSymbolTable()->LookupSymbol(r->GetID());
    if (!con)
        cerr << "Error in IntrOperand: symbol not defined- " << r->GetID() << endl;
    return con;
    /* todo */
    // Ref to array or func
}
