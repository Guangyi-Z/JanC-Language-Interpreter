#ifndef EXP_H
#define EXP_H
#include "lexer/op.h"
#include <utility>

/*
 * operations associativity map
 */
enum ASSOCIATE {
    ASS_LEFT,
    ASS_RIGHT
};
const std::pair<OP, ASSOCIATE> OP_Associativity[] {
    {OP_INC, ASS_LEFT},   // ++
    {OP_DEC, ASS_LEFT},   // --
    {OP_NOT, ASS_LEFT},   // !

    {OP_MUL, ASS_LEFT},   // *
    {OP_DIV, ASS_LEFT},   // /
    {OP_MOD, ASS_LEFT},   // %

    {OP_ADD, ASS_LEFT},   // +
    {OP_SUB, ASS_LEFT},   // -

    {OP_EQ,     ASS_LEFT},// ==
    {OP_NOT_EQ, ASS_LEFT},// !=
    {OP_GT,     ASS_LEFT},// >
    {OP_LT,     ASS_LEFT},// <
    {OP_GT_EQ,  ASS_LEFT},// >=
    {OP_LT_EQ,  ASS_LEFT},// <=

    {OP_AND, ASS_LEFT},   // &&
    {OP_OR,  ASS_LEFT},   // ||

    {OP_ASSIGN, ASS_LEFT} // =
};

#endif
