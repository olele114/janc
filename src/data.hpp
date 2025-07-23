#include <fstream>

enum class TokenType {
	Plus,
	Minus,
	Star,
	Slash,
	IntLit,
}

struct Token {
	TokenType type;
	int intValue;
}

public class Data {
	int line;
	int putBack;
	std::ifstream inFile;
	Token token;
}
