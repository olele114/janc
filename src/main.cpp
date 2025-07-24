#include "data.hpp"
#include "scan.cpp"
#include <vector>
#include <iostream>

using namespace std;

static void init(Scanner s) {
	s.data.line = 1;
	s.data.putBack = '\n';
}

static void usage(string prog) {
	throw runtime_error("Usage: " + prog + "infile\n");
}

vector<string> tokStr = {"+", "-", "*", "/", "intLit"};

static void scan_file(Scanner s) {
	while (s.scan()) {
		cout << format("Token {}", tokStr.at(s.data.token.type));
		if (s.data.token.type == TokenType::IntLit) {
			cout << format(", value {}", s.data.token.intValue) << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		usage(argv[0]);
	}

	Data d(argv[1]);
	Scanner s(d);

	init(s);

	scan_file(s);
	return 0;
}
