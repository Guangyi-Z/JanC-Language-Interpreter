#include "parser.h"

bool Parser::EatToken(TOKEN t) {
    if (t != lexer.GetCurToken()) {
        std::cout << "Error: EatToken(" << t << "), but actually " << lexer.GetCurToken() << std::endl;
        return false;
    }
    lexer.GetNextToken();
    return true;
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
    else
        return new AST_Statement(ST_BLOCK, ParseBlock());
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
