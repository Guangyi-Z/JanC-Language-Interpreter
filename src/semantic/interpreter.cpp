#include "interpreter.h"

/********************
 * Static Variables
 */
Constant* Interpreter::cBreak = new Int(1);
Constant* Interpreter::cContinue = new Int(1);


/* Interpreter Start Point */
void Interpreter::IntrStatement (AST_Statement *st, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    if (*back != NULL)
        return;
    if (!st)
        return;

    switch(st->type) {
    case ST_BLOCK:
        IntrBlock((AST_Block*)st, sym, fsym, back);
        break;
    case ST_EXP:
        {
            Constant *con = IntrExpression((AST_Expression*)st, sym, fsym, back);
            if (con) {
                // con->Print();
                // cout << endl;
            }
        }
        break;
    case ST_FUNC:
        IntrFunc((AST_Func *)st, sym, fsym);
        break;
    case ST_VAR:
    case ST_ARRAY:
        IntrVar(st, sym, fsym, back);
        break;
    case ST_RETURN:
        *back = IntrExpression(((AST_Return*)st)->e, sym, fsym, back);
        break;
    case ST_IF:
        IntrIf((AST_If*)st, sym, fsym, back);
        break;
    case ST_WHILE:
        IntrWhile((AST_While*)st, sym, fsym, back);
        break;
    case ST_BREAK:
        *back = cBreak;
        break;
    case ST_CONTINUE:
        *back = cContinue;
        break;
    default:
        cerr << "Error in IntrStatement: wrong type for default" << endl;
        exit(0);
    };
}

void Interpreter::IntrBlock(AST_Block* block, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    sym->NewSymbolTable();
    for (AST_Statement *st : block->statements) {
        IntrStatement(st, sym, fsym, back);
    }
    sym->DelSymbolTable();
}

Constant* Interpreter::IntrArrayContent(AST_Array *array, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    if (array->ve.empty())
        return NULL;

    Array *arr = new Array(array->sz_array);
    int index = 0;
    for (AST_Expression* e : array->ve) {
        Constant *_con = IntrExpression(e, sym, fsym, back);
        arr->SetElement(index++, _con);
    }
    return arr;
}

void Interpreter::IntrVar(AST_Statement *st, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    if (st->GetType() == ST_ARRAY) {
        AST_Array *array = (AST_Array*) st;
        Constant* val = IntrArrayContent(array, sym, fsym, back);
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
            val = IntrExpression(var->val, sym, fsym, back);
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

Constant* Interpreter::IntrAssignment(AST_Expression* exp, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    AST_Expression *lv = exp->e1;
    if (!lv->IsLeaf())
        goto unassignable;
    {
    Operand *o = exp->e1->o;
    Constant* rv = IntrExpression(exp->e2, sym, fsym, back);
    switch(o->GetType()) {
    case OPRD_REF:
        {
            Reference *r = (Reference*)(o);
            if (fsym->IsSymbolDefined(r->GetID()))
                goto unassignable;
            sym->GetCurSymbolTable()->ChangeSymbol(r->GetID(), rv);
        }
        break;
    case OPRD_REFARRAY:
        {
            RefArray *r = (RefArray*)(o);
            Constant *cindex = IntrExpression(r->GetIndex(), sym, fsym, back);
            if (cindex->GetType() != CONST_INT) {
                cerr << "Error in IntrAssignment: array index must be Int type" << endl;
                exit(0);
            }
            int index = ((Int*)cindex)->GetInt();
            Array* arr = (Array*)(sym->GetCurSymbolTable()->LookupSymbol(r->GetID()));
            arr->SetElement(index, rv);
        }
        break;
    default:
        goto unassignable;
    }
    return rv;
    }
unassignable:
    cerr << "Error in IntrAssignment: l-value must be assignable" << endl;
    exit(0);
}

Constant* Interpreter::IntrExpression(AST_Expression* exp, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    if (exp->IsLeaf()) {
        return IntrOperand(exp->o, sym, fsym, back);
    }
    // For assgiment
    if (exp->op == OP_ASSIGN)
        return IntrAssignment(exp, sym, fsym, back);
    // Normal recursive process
    Constant* con1 = IntrExpression(exp->e1, sym, fsym, back);
    Constant* con2 = IntrExpression(exp->e2, sym, fsym, back);
    return DoBinaryOP(con1, con2, exp->op);
}

Constant* Interpreter::IntrOperand(Operand *o, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    OperandHandler *handler = OperandHandlerFactory::GetOperandHandler(o);
    return handler->IntrOperand(sym, fsym, back);
}

void Interpreter::IntrIf(AST_If* ifs, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    int cnt = 0;
    for (AST_Expression* cond : ifs->GetConds()) {
        Constant *con = IntrExpression(cond, sym, fsym, back);
        if (con->GetType() != CONST_BOOL) {
            cerr << "Error in IntrIf: cond must be bool expression" << endl;
            exit(0);
        }
        if (((Bool*)con)->GetBool()) {
            IntrStatement(ifs->GetStams()[cnt], sym, fsym, back);
            return;
        }
        cnt++;
    }
    /* else */
    IntrStatement(ifs->GetElse(), sym, fsym, back);
}

void Interpreter::IntrWhile(AST_While* sw, NestedSymbolTable *sym, FuncTable *fsym, Constant **back) {
    while(true) {
        Constant *con = IntrExpression(sw->GetCond(), sym, fsym, back);
        if (con->GetType() != CONST_BOOL) {
            cerr << "Error in IntrWhile: cond must be bool expression" << endl;
            exit(0);
        }
        if (((Bool*)con)->GetBool()) {
            IntrStatement(sw->GetBlock(), sym, fsym, back);
            if (*back == cBreak) {
                *back = NULL;
                break;
            }
            if (*back == cContinue)
                *back = NULL;
        }
        else break;
    }
}

