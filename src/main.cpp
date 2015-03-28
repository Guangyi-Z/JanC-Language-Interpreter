#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "semantic/controller.h"
using std::ifstream;
using std::stringstream;
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
    ifstream in_greet("../doc/greeting.txt");
    stringstream s_greet;
    s_greet << in_greet.rdbuf();
    cout << s_greet.str() << endl;

    string input;
    while(true) {
        cout << ">> ";
        cin >> input;
        if (input == "load") {
            string filename;
            cin >> filename;
            ifstream infile(filename);
            if (infile.good()) {
                infile.close();
                InterpreterController ctrl(filename);
                ctrl.Continue();
            }
            else {
                cout << "<< Source file doesn't exist: " << filename << endl;
            }
        }
        else if (input == "quit") {
            cout << "<< Bye" << endl;
            break;
        }
        else {
            cout << "<< Incorrect input" << endl;
            cout << endl;
            cout << s_greet.str() << endl;
        }
    }

}
