#include "parser.h"
using std::cout;
using std::endl;

bool Parser::EatToken(TOKEN t) {
    if (t != lexer.GetCurToken()) {
        std::cout << "Error: EatToken(" << t << "), but actually " << lexer.GetCurToken() << std::endl;
        return false;
    }
    lexer.GetNextToken();
    return true;
}

AST_ExpressionOperand Parser::GetNextOperand() {
    TOKEN t = lexer.GetCurToken();
    AST_ExpressionOperand o;
    // get prefix operators
    while (t == TOK_OP) {
        OP op = lexer.GetCurOP();
        if (pp.IsPrefixOP(op))
            o.AddPrefixOP(op);
        else {
            std::cout << "Error in GetNextOperand: prefix OP " << op << std::endl;
            exit(0);
        }
        t = lexer.GetNextToken();
    }
    // get operand entity
    switch (t) {
        case TOK_PAREN_LEFT:
            EatToken(TOK_PAREN_LEFT);
            o.SetOperand(EXP_EXP, ParseExpression());
            // TOK_PAREN_RIGHT is ate by GetNextOP()
            break;
        case TOK_INT:
            o.SetOperand(EXP_INT, std::stoi(lexer.GetCurLexem()));
            EatToken(t);
            break;
        case TOK_DOUBLE:
            o.SetOperand(EXP_DOUBLE, std::stod(lexer.GetCurLexem()));
            EatToken(t);
            break;
        case TOK_ID:
            /* todo */
            break;
        default:
            std::cout << "Error: ParseExpression switch default- " << t << std::endl;
            exit(0);
    }
    // get suffix operators
    t = lexer.GetCurToken();
    while (t == TOK_OP) {
        OP op = lexer.GetCurOP();
        if (!pp.IsSuffixOP(op))
            break;
        TOKEN t_nxt = lexer.LookaheadOneToken();
        if (t_nxt == TOK_OP ||
                t_nxt == TOK_SEMI ||
                t_nxt == TOK_PAREN_RIGHT ||
                t_nxt == TOK_COMMA ||
                t_nxt == TOK_CURLY_BRACE_RIGHT) {
            o.AddSuffixOP(op);
        }
        else {
            lexer.RewindOneToken();
            lexer.GetNextToken();
            break;
        }
        t = lexer.GetNextToken();
    }
    return o;
}

OP Parser::GetNextOP() {
    OP op;
    TOKEN t = lexer.GetCurToken();
    if (t != TOK_OP || mOP.find(lexer.GetCurOP()) == mOP.end()) {
        if (t == TOK_PAREN_RIGHT)
            EatToken(TOK_PAREN_RIGHT);
        if (t == TOK_SEMI)
            EatToken(TOK_SEMI); // expression ends with semi
        return OP_NONE;
    }
    else {
        op = lexer.GetCurOP();
        EatToken(t);
    }
    return op;
}

AST_Expression* Parser::ParseExpressionHelper(AST_ExpressionOperand o1, OP op) {
    AST_ExpressionOperand o2 = GetNextOperand();
    OP op_nxt = GetNextOP();
    if (op_nxt == OP_NONE)
        return new AST_Expression(o1, op, o2);
    int prio_op = mOP[op],
        prio_op_nxt = mOP[op_nxt];
    if (prio_op >= prio_op_nxt) {
        AST_ExpressionOperand o1_new;
        o1_new.SetOperand(EXP_EXP, new AST_Expression(o1, op, o2));
        return ParseExpressionHelper(o1_new, op_nxt);
    }
    else {
        AST_ExpressionOperand o2_new;
        o2_new.SetOperand(EXP_EXP, ParseExpressionHelper(o2, op_nxt));
        return new AST_Expression(o1, op, o2_new);
    }
}

AST_Expression* Parser::ParseExpression() {
    AST_ExpressionOperand o1 = GetNextOperand();
    OP op = GetNextOP();
    if (op == OP_NONE)
        return new AST_Expression(o1);
    else
        return ParseExpressionHelper(o1, op);
}

AST_Var* Parser::ParseVar() {
    EatToken(TOK_VAR);
    AST_Var *var = new AST_Var(ST_VAR, lexer.GetCurLexem());
    EatToken(TOK_ID);
    TOKEN t = lexer.GetCurToken();
    if (t == TOK_BRACE_LEFT) {  // array var
        var->is_array = true;
        EatToken(TOK_BRACE_LEFT);
        var->sz_array = std::stoi(lexer.GetCurLexem());
        EatToken(TOK_BRACE_RIGHT);
    }
    EatToken(TOK_SEMI);
    return var;
}

AST_Func* Parser::ParseFunc() {
    EatToken(TOK_FUNC);
    AST_Func *func = new AST_Func(ST_FUNC, lexer.GetCurLexem());
    EatToken(TOK_ID);
    // Parse the function's parameters
    EatToken(TOK_PAREN_LEFT);
    TOKEN t = lexer.GetCurToken();
    std::vector<AST_Var*> paras;
    while (t == TOK_ID) {
        paras.push_back(new AST_Var(ST_VAR, lexer.GetCurLexem()));
        EatToken(TOK_ID);
        t = lexer.GetCurToken();
        if (TOK_COMMA == t) {
            EatToken(TOK_COMMA);
            t = lexer.GetCurToken();
        }
    }
    func->paras = paras;
    EatToken(TOK_PAREN_RIGHT);
    // Functions end with either ';' or {...}
    if (TOK_SEMI == lexer.GetCurToken())
        EatToken(TOK_SEMI);
    else
        func->block = ParseBlock();
    return func;
}

AST_Statement* Parser::ParseStatement() {
    TOKEN t = lexer.GetCurToken();
    if (t == TOK_END)
        return NULL;
    else if (t == TOK_FUNC)
        return ParseFunc();
    else if (t == TOK_VAR)
        return ParseVar();
    else if (t == TOK_SEMI) {
        EatToken(TOK_SEMI);
        return new AST_Statement(ST_EMPTY, NULL);
    }
    else if (t == TOK_CURLY_BRACE_LEFT)
        return new AST_Statement(ST_BLOCK, ParseBlock());
    else if(t == TOK_INT ||
            t == TOK_DOUBLE ||
            t == TOK_ID ||
            t == TOK_PAREN_LEFT ||
            t == TOK_OP) {  // expression
        return ParseExpression();
    }
    else {
        std::cout << "Error: ParseStatement with TOK- " << t << std::endl;
        exit(0);
    }
}

AST_Block* Parser::ParseBlock() {
    TOKEN t = lexer.GetCurToken();
    if (t == TOK_CURLY_BRACE_LEFT) {
        AST_Block *block = new AST_Block();
        EatToken(TOK_CURLY_BRACE_LEFT);
        while (true) {
            t = lexer.GetCurToken();
            if (t == TOK_CURLY_BRACE_RIGHT)
                break;
            block->AddStatement(ParseStatement());
        }
        EatToken(TOK_CURLY_BRACE_RIGHT);
        return block;
    }
    else return NULL;
}

void Parser::Parse() {
    ParseStatement();
}
