#include "operand.h"

Constant* Operand::DoPrefixAssignableOP(Constant *corder) {
    Constant *res = corder;
    for (OP op: GetPrefixOP()) {
        if (OpProperty::IsPrefixAssignableOP(op))
        res = res->Transform(op);
    }
    return res;
}
Constant* Operand::DoPrefixUnassignableOP(Constant *corder) {
    Constant *res = corder;
    for (OP op: GetPrefixOP()) {
        if (!OpProperty::IsPrefixAssignableOP(op))
            res = res->Transform(op);
    }
    return res;
}
Constant* Operand::DoSuffixAssignableOP(Constant* corder) {
    Constant *res = corder;
    for (OP op: GetSuffixOP())
        res = res->Transform(op);
    return res;
}
