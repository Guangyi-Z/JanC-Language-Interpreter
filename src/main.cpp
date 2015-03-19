#include <iostream>
#include "lexer/token.h"
using namespace std;

int main() {
    cout << "Hello, world." << endl;

    std::stringstream ss;
    ss << "ccc" << 1 << 1.5;
    cout << ss.str() << endl;

    int c = '\t';
    cout << isspace(c) << endl;
    c = '\n';
    cout << isspace(c) << endl;
    c = ' ';
    cout << isspace(c) << endl;

    string s(10, '\0');
    cout << s << endl;
    s[0] = 'a';
    s[1] = 'b';
    cout << s << endl;
    s[1] = '\0';
    cout << s << endl;

    cout << endl;

    switch (1) {
        case 1:
            // int a = 1;
            break;
        case 2:
            {
                int b = 2;
            }
            break;
        default:
            break;
    }

    int oa = 1;
    cout << oa+++1 << endl;
    oa = - --oa;
    cout << oa << endl;

    // unordered_map
}
