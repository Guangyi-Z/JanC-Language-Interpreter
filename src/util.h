#ifndef UTIL_H
#define UTIL_H
#include <iostream>
using std::cerr;
using std::endl;

void Panic (string msg) {
    cerr << "Error: " << msg << endl;
    exit(0);
}

#endif
