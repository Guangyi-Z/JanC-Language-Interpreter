#include "parser.h"
using std::cout;
using std::cerr;
using std::endl;

bool Parser::EatToken(TOKEN t) {
    if (t != lexer.GetCurToken()) {
        std::cerr << "Error: EatToken(" << t << "), but actually " << lexer.GetCurToken() << std::endl;
        return false;
    }
    lexer.GetNextToken();
    return true;
}

void Parser::FindPrefixOP(Operand &o) {
    while (lexer.GetCurToken() == TOK_OP) {
        OP op = lexer.GetCurOP();
        if (pp.IsPrefixOP(op))
            o.AddPrefixOP(op);
        else {
            std::cerr << "Error in FindPrefixOP: prefix OP " << op << std::endl;
            exit(0);
        }
        EatToken(TOK_OP);
    }
}

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

void Parser::FindSuffixOP(Operand &o) {
    while (lexer.GetCurToken() == TOK_OP &&
            pp.IsSuffixOP(lexer.GetCurOP())
            ) {
        const TOKEN t_nxt = lexer.LookaheadOneToken();
        if (IsTheEndOfExp(t_nxt)) {
            o.AddSuffixOP(lexer.GetCurOP());
            return;
        }
        if (t_nxt == TOK_OP)
            o.AddSuffixOP(lexer.GetCurOP());
        else {
            lexer.RewindOneToken();
            lexer.GetNextToken();
            break;
        }
        EatToken(TOK_OP);
    }
}

AST_Expression* Parser::GetNextOperand() {
    Operand o;
    // get prefix operators
    FindPrefixOP(o);
    // get operand entity
    switch (lexer.GetCurToken()) {
        case TOK_PAREN_LEFT:
            {
            EatToken(TOK_PAREN_LEFT);
                AST_Expression *e = ParseExpression();   // (..) has no unary op outside
            EatToken (TOK_PAREN_RIGHT);
            return e;
            }
            break;
        case TOK_INT:
            o.SetOperand(std::stoi(lexer.GetCurLexem()));
            EatToken(TOK_INT);
            break;
        case TOK_DOUBLE:
            o.SetOperand(std::stod(lexer.GetCurLexem()));
            EatToken(TOK_DOUBLE);
            break;
        case TOK_ID:
            {
                string name = lexer.GetCurLexem();
                EatToken(TOK_ID);
                if (lexer.GetCurToken() == TOK_PAREN_LEFT){  // func
                    EatToken(TOK_PAREN_LEFT);
                    vector<void*> vpara;
                    while (lexer.GetCurToken() != TOK_PAREN_RIGHT) {
                        AST_Expression *para = ParseExpression();
                        vpara.push_back(para);
                        if (lexer.GetCurToken() == TOK_COMMA)
                            EatToken(TOK_COMMA);
                    }
                    EatToken(TOK_PAREN_RIGHT);
                    o.SetOperand(name, vpara);
                }
                else if (lexer.GetCurToken() == TOK_BRACE_LEFT) {   // array
                    EatToken(TOK_BRACE_LEFT);
                    AST_Expression *para = ParseExpression();
                    o.SetOperand(name, {(void*)para});
                    EatToken(TOK_BRACE_RIGHT);
                }
                else {  // var
                    o.SetOperand(name, {});
                }
            }
            break;
        default:
            std::cerr << "Error: ParseExpression switch default- " << lexer.GetCurToken() << std::endl;
            exit(0);
    }
    // get suffix operators
    FindSuffixOP(o);
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
    AST_Expression* e2 = GetNextOperand();
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
    AST_Expression *e1 = GetNextOperand();
    const OP op = GetNextOP();
    if (op == OP_NONE)
        return e1;
    else
        return ParseExpressionHelper(e1, op);
}

AST_Var* Parser::ParseVar() {
    EatToken(TOK_VAR);
    string name = lexer.GetCurLexem();
    bool is_array = false;
    int sz_array = -1;
    EatToken(TOK_ID);
    // test array var
    if (lexer.GetCurToken() == TOK_BRACE_LEFT) {
        is_array = true;
        EatToken(TOK_BRACE_LEFT);
        sz_array = std::stoi(lexer.GetCurLexem());
        EatToken(TOK_BRACE_RIGHT);
    }
    vector<double> vd;
    // test initialization
    vector<AST_Expression*> ve;
    if (lexer.GetCurToken() == TOK_OP && lexer.GetCurOP() == OP_ASSIGN) {
        EatToken(TOK_OP);
        if (is_array) {
            ve.push_back(ParseExpression());
        }
        else {
            EatToken(TOK_CURLY_BRACE_LEFT);
            while(lexer.GetCurToken() != TOK_CURLY_BRACE_RIGHT)
                ve.push_back(ParseExpression());
            EatToken(TOK_CURLY_BRACE_RIGHT);
        }
        // if (is_array) {
        //     EatToken(TOK_CURLY_BRACE_LEFT);
        //     bool is_double = false;
        //     while(lexer.GetCurToken() != TOK_CURLY_BRACE_RIGHT) {
        //         switch(lexer.GetCurToken()) {
        //         case TOK_INT:
        //             EatToken(TOK_INT);
        //             vd.push_back(std::stoi(lexer.GetCurLexem()));
        //             break;
        //         case TOK_DOUBLE:
        //             EatToken(TOK_DOUBLE);
        //             is_double = true;
        //             vd.push_back(std::stod(lexer.GetCurLexem()));
        //             break;
        //         default: ;
        //         }
        //         if (TOK_COMMA == lexer.GetNextToken())
        //             EatToken(TOK_COMMA);
        //     }
        //     EatToken(TOK_CURLY_BRACE_RIGHT);
        //     if (is_double) {
        //         con.SetValue(vd, sz_array);
        //     }
        //     else {
        //         vector<int> vi;
        //         for (double d : vd)
        //             vi.push_back((int)d);
        //         con.SetValue(vi, sz_array);
        //     }
        // }
        // else {
        //     switch(lexer.GetCurToken()) {
        //     case TOK_INT:
        //         con.SetValue(std::stoi(lexer.GetCurLexem()));
        //         EatToken(TOK_INT);
        //         break;
        //     case TOK_DOUBLE:
        //         con.SetValue(std::stod(lexer.GetCurLexem()));
        //         EatToken(TOK_DOUBLE);
        //         break;
        //     default: ;
        //     }
        // }
    }
    EatToken(TOK_SEMI);
    return new AST_Var(name, ve);
}

AST_Func* Parser::ParseFunc() {
    EatToken(TOK_FUNC);
    string name = lexer.GetCurLexem();
    EatToken(TOK_ID);
    // parse the function's parameters
    EatToken(TOK_PAREN_LEFT);
    std::vector<string> paras;
    while (lexer.GetCurToken() == TOK_ID) {
        paras.push_back(lexer.GetCurLexem());
        EatToken(TOK_ID);
        if (TOK_COMMA == lexer.GetCurToken())
            EatToken(TOK_COMMA);
    }
    EatToken(TOK_PAREN_RIGHT);
    AST_Func *func = new AST_Func(name, paras);
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
        AST_Expression* e = ParseExpression();
        EatToken(TOK_SEMI);
        return e;
    }
    else {
        std::cerr << "Error: ParseStatement with TOK- " << t << std::endl;
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
