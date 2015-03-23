#ifndef TOKEN_H
    #define TOKEN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <unordered_map>
#include <deque>
#include "op.h"

enum TOKEN {
    /* value */
    TOK_ID,
    TOK_BOOL,
    TOK_INT,
    TOK_DOUBLE,
    TOK_STRING,

    /* flow control */
    TOK_IF, // 5th
    TOK_ELSE,
    TOK_VAR,
    TOK_FUNC,
    TOK_WHILE,
    TOK_BREAK, // 10th
    TOK_CONTINUE,
    TOK_FOR,
    TOK_RETURN,

    /* punctuation */
    TOK_PAREN_LEFT,
    TOK_PAREN_RIGHT, // 15th
    TOK_BRACE_LEFT,
    TOK_BRACE_RIGHT,
    TOK_CURLY_BRACE_LEFT,
    TOK_CURLY_BRACE_RIGHT,
    TOK_SEMI, // 20th
    TOK_COMMA,
    TOK_OP,

    /* helper token */
    TOK_NUMBER_OF_TOKENS,
    TOK_BAD_TOKEN,
    TOK_START, // 25th
    TOK_END
};

/* mapping reserved key words to TOK_ */
const std::pair<std::string, TOKEN> Key_Words[] = {
    {"if", TOK_IF},
    {"else", TOK_ELSE},
    {"var", TOK_VAR},
    {"func", TOK_FUNC},
    {"while", TOK_WHILE},
    {"break", TOK_BREAK},
    {"continue", TOK_CONTINUE},
    {"for", TOK_FOR},
    {"return", TOK_RETURN},
    {"true", TOK_BOOL},
    {"false", TOK_BOOL},
    /* delimeter */
    {",", TOK_COMMA},
    {";", TOK_SEMI},
    {"(", TOK_PAREN_LEFT},
    {")", TOK_PAREN_RIGHT},
    {"[", TOK_BRACE_LEFT},
    {"]", TOK_BRACE_RIGHT},
    {"{", TOK_CURLY_BRACE_LEFT},
    {"}", TOK_CURLY_BRACE_RIGHT}
};

const std::string Delim = ",;()[]{}";

class Lexer {
public:
    Lexer();
    Lexer(std::string path_to_file);
    ~Lexer();
    void Load(std::string path_to_file);
    TOKEN GetNextToken();
    TOKEN GetCurToken();
    TOKEN LookaheadOneToken();
    void RewindOneToken();
    std::string GetCurLexem();
    OP GetCurOP();
    bool IsNextOPEquals(OP op);
    bool IsNextTokenEquals(TOKEN t);

private:
    bool Eat(char c);
    char Next();
    TOKEN NextNum();

    std::ifstream in;
    int cur;
    static const int MAX_LEXEM = 1024;
    char lexem_buf[MAX_LEXEM];
    std::unordered_map<std::string, TOKEN> mkey;
    OPEntry ope;
    TOKEN t = TOK_BAD_TOKEN;
    // for Rewindonetoken()
    std::deque<char> qin;
    // for Lookaheadonetoken()
    bool is_looking_ahead = false;
    std::deque<char> qin2;
};
#endif
