#include "token.h"
using namespace std;

Lexer::Lexer() {
    for (auto p : Key_Words) {
        mkey.insert(p);
    }
}

Lexer::Lexer(string path_to_file) : Lexer() {
    in.open(path_to_file);
    cur = Next();
}

Lexer::~Lexer() {
    in.close();
}

void Lexer::Load(std::string path_to_file) {
    in.open(path_to_file);
    cur = Next();
}

bool Lexer::IsNextOPEquals(OP op) {
    if (t == TOK_OP && ope.op == op)
        return true;
    return false;
}

bool Lexer::IsNextTokenEquals(TOKEN _t) {
    if (t == _t)
        return true;
    return false;
}

OP Lexer::GetCurOP() {
    return ope.op;
}

TOKEN Lexer::GetCurToken() {
    return t;
}

TOKEN Lexer::GetNextToken() {
    lexem_buf[0] = '\0';
    while(cur != EOF && isspace(cur)) cur = Next();
    if (cur == EOF) return t = TOK_END;

    t = TOK_START;
    int op_table_index = 0;
    int ibuf = 0;

    while(true) {
        if (cur == EOF) goto done;

        switch(t) {
        case TOK_START: /* start state */
            if (isdigit(cur))
                t = TOK_INT;
            else if (cur == '.')
                t = TOK_DOUBLE;
            else if (isalpha(cur) || cur == '_')
                t = TOK_ID;
            else if (Delim.find(cur) != string::npos) {
                lexem_buf[ibuf++] = cur;
                cur = Next();
                goto key_word;
            }
            else if (cur == '"') {
                t = TOK_STRING;
                cur = Next();
                continue;
            }
            else if (strchr(OP_Char_Set, cur)) {
                t = TOK_OP;
                for (OPEntry e : OP_Action_Table[op_table_index]) {
                    if (e.c == OPEntry::EMPTY_OP) break;
                    if (cur == e.c) {
                        ope = e;
                        break;
                    }
                }
                op_table_index++;
            }
            else ;
            break;
        case TOK_ID:
            if (isdigit(cur) || isalpha(cur) || cur == '_')
                ;
            else if (isspace(cur) ||
                    Delim.find(cur) != string::npos ||
                    strchr(OP_Char_Set, cur))
                goto key_word;
            else goto bad_syntax;
            break;
        case TOK_INT:
            if (cur == '.')
                t = TOK_DOUBLE;
            else if (isdigit(cur))
                ;
            else if (isspace(cur) ||
                    Delim.find(cur) != string::npos ||
                    strchr(OP_Char_Set, cur))
                goto done;
            else goto bad_syntax;
            break;
        case TOK_DOUBLE:
            if (isdigit(cur))
                ;
            else if (isspace(cur) ||
                    Delim.find(cur) != string::npos ||
                    strchr(OP_Char_Set, cur))
                goto done;
            else goto bad_syntax;
            break;
        case TOK_STRING:
            if (cur == '\\') { // For escape characters
                cur = Next();
                lexem_buf[ibuf++] = cur;
                cur = Next();
                continue;
            }
            else if (cur == '"') {
                cur = Next(); // eat the ending '"'
                goto done;
            }
            else ;
            break;
        case TOK_OP:
            {
                bool is_match = false;
                for (int ind : ope.nxt) {
                    OPEntry e = OP_Action_Table[op_table_index][ind];
                    if (e.c == OPEntry::EMPTY_OP) break;
                    if (cur == e.c) {
                        ope = e;
                        is_match = true;
                        break;
                    }
                }
                if (is_match && ope.op != OP_NONE && ope.nxt.empty()) {
                    lexem_buf[ibuf++] = cur;
                    cur = Next(); // don't forget to eat the op char
                    goto done;
                }
                else if (ope.op != OP_NONE && !is_match)
                    goto done;
                else if (!ope.nxt.empty() && is_match)
                    op_table_index++;
                else
                    goto bad_syntax;
            }
            break;
        default: break;
        }
        lexem_buf[ibuf++] = cur;
        cur = Next();
    }

done:
    lexem_buf[ibuf] = '\0';
    return t;
key_word:
    lexem_buf[ibuf] = '\0';
    if (mkey.find(lexem_buf) != mkey.end()) {
        t = mkey[lexem_buf];
    }
    return t;
bad_syntax:
    lexem_buf[ibuf] = '\0';
    cout << "bad syntax in state " << t << " : " << (char)cur << endl;
    return TOK_BAD_TOKEN;
}

string Lexer::GetCurLexem() {
    return string(lexem_buf);
}

TOKEN Lexer::NextNum() {
    static const char *deli = " \t\n";
    TOKEN t = TOK_INT;
    int ibuf = 0;
    while(NULL != strchr(deli, cur)) {
        if (cur == '.')
            t = TOK_DOUBLE;
        lexem_buf[ibuf++] = cur;
        cur = Next();
    }

    return t;
}

TOKEN Lexer::LookaheadOneToken() {
    is_looking_ahead = true;
    char cur_bak = cur;
    string lexem_bak(lexem_buf);
    OPEntry ope_bak = ope;
    TOKEN t_bak = t;
    TOKEN res = GetNextToken();

    is_looking_ahead = false;
    cur = cur_bak;
    int ib = 0;
    for (char _c : lexem_bak)
        lexem_buf[ib++] = _c;
    lexem_buf[ib] = '\0';
    ope = ope_bak;
    t = t_bak;
    while(!qin2.empty()) {
        qin.push_front(qin2.back());
        qin2.pop_back();
    }
    return res;
}

/*
 * put back the current token,
 * and add a space before the last char of lexem_buf
 */
void Lexer::RewindOneToken() {
    int len = strlen(lexem_buf);
    qin.push_front(cur);
    qin.push_front(lexem_buf[len-1]);
    qin.push_front(' ');
    for (int i = len-2; i>0; i--)
        qin.push_front(lexem_buf[i]);
    cur = lexem_buf[0];
}

bool Lexer::Eat(char c) {
    if (c == cur)
        cur = Next();

    return false;
}

char Lexer::Next() {
    char c;
    if (qin.empty())
        c = in.get();
    else {
        c = qin.front();
        qin.pop_front();
    }
    // in LookaheadOneToken()
    if (is_looking_ahead) {
        qin2.push_back(c);
    }
    return c;
}
