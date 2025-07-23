#include <fstream>
#include <string>

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

static class Data {
	public:
	int line;
	int putBack;
	std::ifstream inFile;
	std::string fileName;
	Token token;

	Data(std::string fileName) {
		this.fileName = fileName;
	}
}
