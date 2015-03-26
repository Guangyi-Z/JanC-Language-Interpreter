#include "arithmetic.h"

Arithmetic* String::AddInt(Int* o2) {
    return new String(this->GetString() + std::to_string(o2->GetInt()));
}

Arithmetic* String::AddDouble(Double* o2) {
    return new String(this->GetString() + std::to_string(o2->GetDouble()));
}

Arithmetic* String::AddString(String* o2) {
    return new String(this->GetString() + o2->GetString());
}
