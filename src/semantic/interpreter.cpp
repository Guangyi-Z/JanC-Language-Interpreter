#include "interpreter.h"

/* Interpreter Start Point */
void Interpreter::IntrStatement (AST_Statement *st, NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    if (*ret_val != NULL)
        return;

    if (!st)
        return;
    switch(st->type) {
    case ST_BLOCK:
        IntrBlock((AST_Block*)st, sym, fsym, ret_val);
        break;
    case ST_EXP:
        {
            Constant *con = IntrExpression((AST_Expression*)st, sym, fsym, ret_val);
            if (con) {
                con->Print();
                cout << endl;
            }
        }
        break;
    case ST_FUNC:
        IntrFunc((AST_Func *)st, sym, fsym);
        break;
    case ST_VAR:
    case ST_ARRAY:
        IntrVar(st, sym, fsym, ret_val);
        break;
    case ST_RETURN:
        *ret_val = IntrExpression(((AST_Return*)st)->e, sym, fsym, ret_val);
        break;
    default:
        cout << "Error in IntrStatement: wrong type for default" << endl;
        exit(0);
    };
}

void Interpreter::IntrBlock(AST_Block* block, NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    sym->NewSymbolTable();
    for (AST_Statement *st : block->statements) {
        IntrStatement(st, sym, fsym, ret_val);
    }
    sym->DelSymbolTable();
}

Constant* Interpreter::IntrArrayContent(AST_Array *array, NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    if (array->ve.empty())
        return NULL;

    Array *arr = new Array(array->sz_array);
    for (AST_Expression* e : array->ve) {
        Constant *_con = IntrExpression(e, sym, fsym, ret_val);
        arr->AddElement(_con);
    }
    return arr;
}

void Interpreter::IntrVar(AST_Statement *st, NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    if (st->GetType() == ST_ARRAY) {
        AST_Array *array = (AST_Array*) st;
        Constant* val = IntrArrayContent(array, sym, fsym, ret_val);
        if (sym->GetCurSymbolTable()->IsSymbolDefined(array->id)) {
            cerr << "Error in IntrVar: symbol " << array->id << " has been defined" << endl;
            exit(0);
        }
        sym->GetCurSymbolTable()->AddSymbol(array->id, val);
    }
    else {
        AST_Var *var = (AST_Var*) st;
        if (sym->GetCurSymbolTable()->IsSymbolDefined(var->id)) {
            cerr << "Error in IntrVar: symbol " << var->id << " has been defined" << endl;
            exit(0);
        }
        Constant *val = NULL;
        if (var->val) {
            val = IntrExpression(var->val, sym, fsym, ret_val);
        }
        else {
            cerr << "Error in IntrVar: symbol " << var->id << " not initialized" << endl;
            exit(0);
        }
        sym->GetCurSymbolTable()->AddSymbol(var->id, val);
    }
}

void Interpreter::IntrFunc(AST_Func* func, NestedSymbolTable *sym, FuncTable *fsym) {
    fsym->AddSymbol(func->id, func);
}

Constant* Interpreter::DoBinaryOP(Constant* con1, Constant *con2, OP op) {
    switch(op) {
    /* arithmetic */
    case OP_ADD:
        return ((Arithmetic*)con1)->Add((Arithmetic*)con2);
    case OP_SUB:
        return ((Arithmetic*)con1)->Sub((Arithmetic*)con2);
    case OP_MUL:
        return ((Arithmetic*)con1)->Mul((Arithmetic*)con2);
    case OP_DIV:
        return ((Arithmetic*)con1)->Div((Arithmetic*)con2);
    /* relational */
    case OP_EQ:
        return ((Arithmetic*)con1)->EQ((Arithmetic*)con2);
    case OP_NOT_EQ:
        return ((Arithmetic*)con1)->NEQ((Arithmetic*)con2);
    case OP_GT:
        return ((Arithmetic*)con1)->GT((Arithmetic*)con2);
    case OP_LT:
        return ((Arithmetic*)con1)->LT((Arithmetic*)con2);
    case OP_GT_EQ:
        return ((Arithmetic*)con1)->GTEQ((Arithmetic*)con2);
    case OP_LT_EQ:
        return ((Arithmetic*)con1)->LTEQ((Arithmetic*)con2);
    /* logical */
    case OP_AND:
        return ((Bool*)con1)->And((Bool*)con2);
    case OP_OR:
        return ((Bool*)con1)->Or((Bool*)con2);
    default: ;
    }
    return NULL;
}

Constant* Interpreter::IntrExpression(AST_Expression* exp, NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    if (exp->IsLeaf()) {
        return IntrOperand(exp->o, sym, fsym, ret_val);
    }
    // For assgiment
    if (exp->op == OP_ASSIGN) {
        AST_Expression *lv = exp->e1;
        if (!lv->IsLeaf() || lv->o->GetType() != OPRD_REF) {
            cerr << "Error in IntrExpression: l-value must be assignable" << endl;
            exit(0);
        }
        Reference *r = (Reference*)(lv->o);
        Constant* rv = IntrExpression(exp->e2, sym, fsym, ret_val);
        sym->GetCurSymbolTable()->ChangeSymbol(r->GetID(), rv);
        return rv;
    }
    // Normal recursive process
    Constant* con1 = IntrExpression(exp->e1, sym, fsym, ret_val);
    Constant* con2 = IntrExpression(exp->e2, sym, fsym, ret_val);
    return DoBinaryOP(con1, con2, exp->op);
}

Constant* Interpreter::IntrOperand(Operand *o, NestedSymbolTable *sym, FuncTable *fsym, Constant **ret_val) {
    OperandHandler *handler = OperandHandlerFactory::GetOperandHandler(o);
    return handler->IntrOperand(sym, fsym, ret_val);
}

