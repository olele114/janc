#include "data.hpp"
#include "scanner.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

static void usage(const string& prog) {
    cerr << "Usage: " << prog << " infile\n";
    exit(1);
}

vector<string> tokStr = {"Plus", "Minus", "Star", "Slash", "IntLit"};

static void scan_file(Scanner& s) {
    while (s.scan()) {
        Token token = s.getToken();
        cout << "Token " << tokStr[static_cast<int>(token.type)];
        
        if (token.type == TokenType::IntLit) {
            cout << ", value " << token.intValue;
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            usage(argv[0]);
        }

        Data d(argv[1]);
        Scanner s(d);

        s.init();

        scan_file(s);
        
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
