#include "arithmetic.h"

Array::Array(int _sz) : Constant(CONST_ARRAY) {
    sz_array = _sz;
    for (int i= 0; i<sz_array; i++)
        vc.push_back(new Int(0));
}

Constant* Array::At(int index) {
    return vc[index];
}

void Array::SetElement(int index, Constant* _c) {
    if (index >= sz_array) {
        cerr << "Error in SetElement: index out of boundary- " << index << " out of " << sz_array << endl;
        exit(0);
    }
    vc[index] = _c;
}

/* Printer */
void Array::Print() {
    cout << "[";
    for (Constant *c : vc) {
        c->Print();
        cout << ", ";
    }
    cout << "]";
}
