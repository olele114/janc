#pragma once
#include <cctype>
#include <string>
#include <utility>
#include "data.hpp"

class Scanner {
    Data& data;
    
public:
    explicit Scanner(Data& d) : data(d) {}
    
    char next() {
        if (data.putBack) {
            char c = static_cast<char>(data.putBack);
            data.putBack = 0;
            return c;
        }
        
        char c = data.inFile.get();
        if (c == '\n') {
            data.line++;
        }
        return c;
    }

    void put_back(char c) {
        data.putBack = c;
    }

    char skip() {
        char c;
        while (true) {
            c = next();
            if (data.inFile.eof()) return EOF;
            if (!std::isspace(static_cast<unsigned char>(c))) break;
        }
        return c;
    }

    int scan_int(char c) {
        int val = 0;
        do {
            val = val * 10 + (c - '0');
            c = next();
        } while (std::isdigit(static_cast<unsigned char>(c)));
        
        put_back(c);
        return val;
    }

    bool scan() {
        char c = skip();
        if (c == EOF) return false;

        switch (c) {
            case '+': data.token.type = TokenType::Plus; break;
            case '-': data.token.type = TokenType::Minus; break;
            case '*': data.token.type = TokenType::Star; break;
            case '/': data.token.type = TokenType::Slash; break;
            default:
                if (std::isdigit(static_cast<unsigned char>(c))) {
                    data.token.intValue = scan_int(c);
                    data.token.type = TokenType::IntLit;
                } else {
                    throw std::runtime_error("Unrecognized character on line " + std::to_string(data.line));
                }
        }
        return true;
    }
};
