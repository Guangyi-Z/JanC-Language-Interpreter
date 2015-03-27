#include "parser.h"
using std::cout;
using std::cerr;
using std::endl;

/********************************************
 * Parsing Util
 *******************************************/
bool Parser::EatToken(TOKEN t) {
    if (t != lexer.GetCurToken()) {
        std::cerr << "Error: EatToken(" << t << "), but actually " << lexer.GetCurToken() << std::endl;
        return false;
    }
    lexer.GetNextToken();
    return true;
}

/********************************************
 * Parsing Expression
 *******************************************/
bool Parser::IsTheEndOfExp(TOKEN t) {
    static const std::set<TOKEN> se = {
        TOK_COMMA,
        TOK_SEMI,
        TOK_BRACE_RIGHT,
        TOK_PAREN_RIGHT
    };
    if (se.find(t) == se.end())
        return false;
    return true;
}

vector<OP> Parser::FindPrefixOP() {
    vector<OP> vo;
    while (lexer.GetCurToken() == TOK_OP) {
        OP op = lexer.GetCurOP();
        if (pp.IsPrefixOP(op))
            vo.push_back(op);
        else {
            std::cerr << "Error in FindPrefixOP: prefix OP " << op << std::endl;
            exit(0);
        }
        EatToken(TOK_OP);
    }
    return vo;
}

vector<OP> Parser::FindSuffixOP() {
    vector<OP> vo;
    while (lexer.IsNextTokenEquals(TOK_OP) &&
            pp.IsSuffixOP(lexer.GetCurOP())
            ) {
        const TOKEN t_nxt = lexer.LookaheadOneToken();
        if (t_nxt == TOK_OP || IsTheEndOfExp(t_nxt)) {
            vo.push_back(lexer.GetCurOP());
            if (IsTheEndOfExp(t_nxt))
                break;
        }
        else {
            lexer.RewindOneToken();
            lexer.GetNextToken();
            break;
        }
        EatToken(TOK_OP);
    }
    return vo;
}

Reference* Parser::FindReferenceFunc(string name) {
    EatToken(TOK_PAREN_LEFT);
    RefFunc *r = new RefFunc(name);
    while (!lexer.IsNextTokenEquals(TOK_PAREN_RIGHT)) {
        r->AddParameter(ParseExpression());
        if (lexer.IsNextTokenEquals(TOK_COMMA))
            EatToken(TOK_COMMA);
    }
    EatToken(TOK_PAREN_RIGHT);
    return r;
}

Reference* Parser::FindReferenceArray(string name) {
    EatToken(TOK_BRACE_LEFT);
    RefArray *r = new RefArray(name);
    r->SetIndex(ParseExpression());
    EatToken(TOK_BRACE_RIGHT);
    return r;
}

Reference* Parser::FindReference() {
    string name = lexer.GetCurLexem();
    EatToken(TOK_ID);
    switch(lexer.GetCurToken()) {
        case TOK_PAREN_LEFT:
            return FindReferenceFunc(name);
        case TOK_BRACE_LEFT:
            return FindReferenceArray(name);
        default:
            // var or direct reference to func and array
            return new Reference(name);
    }
    return NULL;
}

Literal* Parser::FindLiteral() {
    Constant* con = NULL;
    switch (lexer.GetCurToken()) {
        case TOK_TRUE:
            con = new Bool(true);
            EatToken(TOK_TRUE);
            break;
        case TOK_FALSE:
            con = new Bool(false);
            EatToken(TOK_FALSE);
            break;
        case TOK_INT:
            con = new Int(std::stoi(lexer.GetCurLexem()));
            EatToken(TOK_INT);
            break;
        case TOK_DOUBLE:
            con = new Double(std::stod(lexer.GetCurLexem()));
            EatToken(TOK_DOUBLE);
            break;
        case TOK_STRING:
            con = new String(lexer.GetCurLexem());
            EatToken(TOK_STRING);
            break;
        default: /* never been here */;
    }
    return new Literal(con);
}

AST_Expression* Parser::GetNextExpression() {
    Operand *o = NULL;
    // get prefix operators
    vector<OP> prefix = FindPrefixOP();
    // get operand entity
    switch (lexer.GetCurToken()) {
        case TOK_PAREN_LEFT:
            {
            EatToken(TOK_PAREN_LEFT);
            AST_Expression *e = ParseExpression();
            EatToken (TOK_PAREN_RIGHT);
            return e;   // (..) has no unary op outside
            }
            break;
        case TOK_TRUE:
        case TOK_FALSE:
        case TOK_INT:
        case TOK_DOUBLE:
        case TOK_STRING:
            o = FindLiteral();
            break;
        case TOK_ID:
            o = FindReference();
            break;
        default:
            std::cerr << "Error in ParseExpression: switch default- " << lexer.GetCurToken() << std::endl;
            exit(0);
    }
    // get suffix operators
    vector<OP> suffix = FindSuffixOP();
    // fill operand
    for (OP op : prefix)
        o->AddPrefixOP(op);
    for (OP op : suffix)
        o->AddSuffixOP(op);
    return new AST_Expression(o);
}

OP Parser::GetNextOP() {
    if (lexer.GetCurToken() != TOK_OP)
        return OP_NONE;
    if (OpProperty::OP_NOT_EXIST == pp.GetOPPrecedence(lexer.GetCurOP()))
        return OP_NONE;

    OP op = lexer.GetCurOP();
    EatToken(TOK_OP);
    return op;
}

AST_Expression* Parser::ParseExpressionHelper(AST_Expression *e1, OP op) {
    AST_Expression* e2 = GetNextExpression();
    const OP op_nxt = GetNextOP();
    if (op_nxt == OP_NONE)
        return new AST_Expression(e1, op, e2);
    const int prio_op = pp.GetOPPrecedence(op),
              prio_op_nxt = pp.GetOPPrecedence(op_nxt);
    if (prio_op >= prio_op_nxt)
        return ParseExpressionHelper(new AST_Expression(e1, op, e2), op_nxt);
    else
        return new AST_Expression(e1, op, ParseExpressionHelper(e2, op_nxt));
}

AST_Expression* Parser::ParseExpression() {
    AST_Expression *e1 = GetNextExpression();
    const OP op = GetNextOP();
    if (op == OP_NONE)
        return e1;
    else
        return ParseExpressionHelper(e1, op);
}


/********************************************
 * Parsing Var
 *******************************************/
AST_Var* Parser::ParseSingleVar(string name) {
    AST_Var *res = NULL;
    if (lexer.IsNextOPEquals(OP_ASSIGN)) {    // initialization
        EatToken(TOK_OP);
        res = new AST_Var(name, ParseExpression());
    }
    else res = new AST_Var(name);
    EatToken(TOK_SEMI);
    return res;
}

AST_Array* Parser::ParseArray(string name) {
    EatToken(TOK_BRACE_LEFT);
    const int sz_array = std::stoi(lexer.GetCurLexem());
    AST_Array *res = new AST_Array(name, sz_array);
    EatToken(TOK_INT);
    EatToken(TOK_BRACE_RIGHT);
    /* initialization */
    if (lexer.IsNextOPEquals(OP_ASSIGN)) {
        EatToken(TOK_OP);
        EatToken(TOK_CURLY_BRACE_LEFT);
        while(! lexer.IsNextTokenEquals(TOK_CURLY_BRACE_RIGHT)) {
            res->AddElement(ParseExpression());
            if (lexer.IsNextTokenEquals(TOK_COMMA))
                EatToken(TOK_COMMA);
        }
        EatToken(TOK_CURLY_BRACE_RIGHT);
    }
    EatToken(TOK_SEMI);
    return res;
}

AST_Statement* Parser::ParseVar() {
    EatToken(TOK_VAR);
    string name = lexer.GetCurLexem();
    EatToken(TOK_ID);
    if (lexer.GetCurToken() == TOK_BRACE_LEFT)
        return ParseArray(name);
    else
        return ParseSingleVar(name);
}


/********************************************
 * Parseing Function
 *******************************************/
AST_Func* Parser::ParseFunc() {
    EatToken(TOK_FUNC);
    string name = lexer.GetCurLexem();
    EatToken(TOK_ID);
    AST_Func *func = new AST_Func(name);

    // function's parameters
    EatToken(TOK_PAREN_LEFT);
    while (lexer.IsNextTokenEquals(TOK_ID)) {
        func->AddArgument(lexer.GetCurLexem());
        EatToken(TOK_ID);
        if (lexer.IsNextTokenEquals(TOK_COMMA))
            EatToken(TOK_COMMA);
    }
    EatToken(TOK_PAREN_RIGHT);

    // Functions end with either ';' or {...}
    if (lexer.IsNextTokenEquals(TOK_SEMI))
        EatToken(TOK_SEMI);
    else
        func->AddFunctionBody(ParseBlock());
    return func;
}


/********************************************
 * Parseing Block
 *******************************************/
AST_Block* Parser::ParseBlock() {
    EatToken(TOK_CURLY_BRACE_LEFT);
    AST_Block *block = new AST_Block();
    while (true) {
        if (lexer.IsNextTokenEquals(TOK_CURLY_BRACE_RIGHT))
            break;
        block->AddStatement(ParseStatement());
    }
    EatToken(TOK_CURLY_BRACE_RIGHT);
    return block;
}

/********************************************
 * Parsing If
 *******************************************/
AST_If* Parser::ParseIf() {
    EatToken(TOK_IF);
    AST_Expression *cond = ParseExpression();
    AST_Statement *stam = ParseStatement();
    AST_If *ifs = new AST_If(cond, stam);
    if (lexer.IsNextTokenEquals(TOK_ELSEIF)) {
        EatToken(TOK_ELSEIF);
        AST_Expression *cond = ParseExpression();
        AST_Statement *stam = ParseStatement();
        ifs->AddElseIf(cond, stam);
    }
    if (lexer.IsNextTokenEquals(TOK_ELSE)) {
        EatToken(TOK_ELSE);
        ifs->AddElse(ParseStatement());
    }
    return ifs;
}

/********************************************
 * Parsing While
 *******************************************/
AST_While* Parser::ParseWhile() {
    EatToken(TOK_WHILE);
    AST_Expression *cond = ParseExpression();
    AST_Statement *block = ParseStatement();
    return new AST_While(cond, block);
}

/********************************************
 * Parsing Start Point
 *******************************************/
AST_Statement* Parser::ParseStatement() {
    const TOKEN t = lexer.GetCurToken();
    switch(t) {
    case TOK_END:
        return NULL;
    case TOK_FUNC:
        return ParseFunc();
    case TOK_VAR:
        return ParseVar();
    case TOK_SEMI:
        EatToken(TOK_SEMI);
        return NULL;
    case TOK_CURLY_BRACE_LEFT:
        return ParseBlock();
    case TOK_INT:
    case TOK_DOUBLE:
    case TOK_ID:
    case TOK_PAREN_LEFT:
    case TOK_OP:
        {
            AST_Expression* e = ParseExpression();
            EatToken(TOK_SEMI);
            return e;
        }
    case TOK_RETURN:
        {
            EatToken(TOK_RETURN);
            AST_Expression* e = ParseExpression();
            EatToken(TOK_SEMI);
            return new AST_Return(e);
        }
    case TOK_IF:
        return ParseIf();
    case TOK_WHILE:
        return ParseWhile();
    default:
        std::cerr << "Error: ParseStatement with TOK- " << t << std::endl;
        exit(0);
    }
    return NULL;    /* never been here */
}
