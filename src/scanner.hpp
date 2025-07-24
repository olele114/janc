#pragma once
#include <cctype>
#include <string>
#include <utility>
#include "data.hpp"

class Scanner {
    Data& data;
    
public:
    explicit Scanner(Data& d) : data(d) {}
    
    Token getToken() const { return data.token; }
    
    int getLine() const { return data.line; }
    
    void init() {
        data.line = 1;
        data.putBack = '\n';
    }

    int next() {  
        if (data.putBack) {
            int c = data.putBack;
            data.putBack = 0;
            return c;
        }
        
        int c = data.inFile.get();
        if (c == '\n') {
            data.line++;
        }
        return c;
    }

    void put_back(int c) {
        data.putBack = c;
    }

    int skip() {
        int c;
        while (true) {
            c = next();
            if (c == EOF) return EOF;
            if (!std::isspace(c)) break;
        }
        return c;
    }

    int scan_int(int c) {  
        int val = 0;
        do {
            val = val * 10 + (c - '0');
            c = next();
        } while (std::isdigit(c));
        
        put_back(c);
        return val;
    }

    bool scan() {
        int c = skip();  
        if (c == EOF) return false;

        switch (c) {
            case '+': data.token.type = TokenType::Plus; break;
            case '-': data.token.type = TokenType::Minus; break;
            case '*': data.token.type = TokenType::Star; break;
            case '/': data.token.type = TokenType::Slash; break;
            default:
                if (std::isdigit(c)) {
                    data.token.intValue = scan_int(c);
                    data.token.type = TokenType::IntLit;
                } else {
                    throw std::runtime_error("Unrecognized character on line " + std::to_string(data.line));
                }
        }
        return true;
    }
};
