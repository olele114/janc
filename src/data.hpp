#pragma once
#include <fstream>
#include <string>

enum class TokenType {
    Plus,
    Minus,
    Star,
    Slash,
    IntLit
};

struct Token {
    TokenType type;
    int intValue = 0;
};

class Data {
public:
    int line = 1;
    int putBack = 0;
    std::ifstream inFile;
    Token token;

    explicit Data(const std::string& fileName) {
        inFile.open(fileName);
        if (!inFile.is_open()) {
            throw std::runtime_error("Unable to open file: " + fileName);
        }
    }
    
    ~Data() {
        if (inFile.is_open()) {
            inFile.close();
        }
    }
};
