#include "data.hpp"
#include "scanner.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

static void init(Scanner& s) {
    s.data.line = 1;
    s.data.putBack = '\n';
}

static void usage(const string& prog) {
    cerr << "Usage: " << prog << " infile\n";
    exit(1);
}

vector<string> tokStr = {"Plus", "Minus", "Star", "Slash", "IntLit"};

static void scan_file(Scanner& s) {
    while (s.scan()) {
        cout << "Token " << tokStr[static_cast<int>(s.data.token.type)];
        
        if (s.data.token.type == TokenType::IntLit) {
            cout << ", value " << s.data.token.intValue;
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

        init(s);
        scan_file(s);
        
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
