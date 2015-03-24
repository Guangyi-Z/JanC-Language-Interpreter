#ifndef READER_H
#define READER_H
#include "symbol.h"

class SymbolReader {
public:
    SymbolReader(SymbolTable *_sym) : sym(_sym) {}

    /* interfaces */
    int ReadVarInt(string name);
    double ReadVarDouble(string name);
    char ReadVarChar(string name);
    string ReadVarString(string name);
    vector<int> ReadArrayInt(string name);
    vector<double> ReadArrayDouble(string name);
    int ReadArraySize(string name);

private:
    SymbolTable *sym;
};

#endif
