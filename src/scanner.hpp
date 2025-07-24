#pragma once
#include <cctype>
#include <string>
#include <utility>
#include "data.hpp"

class Scanner {
    Data& data;
    
public:
    explicit Scanner(Data& d) : data(d) {}
    
    // 添加公有接口获取当前token
    Token getToken() const { return data.token; }
    
    // 添加公有接口获取行号
    int getLine() const { return data.line; }
    
    // 添加公有初始化方法
    void init() {
        data.line = 1;
        data.putBack = '\n';
    }

    int next() {  // 返回类型改为int以处理EOF
        if (data.putBack) {
            int c = data.putBack;
            data.putBack = 0;
            return c;
        }
        
        int c = data.inFile.get();  // 使用int存储字符，以正确处理EOF(-1)
        if (c == '\n') {
            data.line++;
        }
        return c;
    }

    void put_back(int c) {  // 参数类型改为int
        data.putBack = c;
    }

    int skip() {  // 返回类型改为int
        int c;
        while (true) {
            c = next();
            if (c == EOF) return EOF;  // 现在类型匹配了
            if (!std::isspace(c)) break;
        }
        return c;
    }

    int scan_int(int c) {  // 参数类型改为int
        int val = 0;
        do {
            val = val * 10 + (c - '0');
            c = next();
        } while (std::isdigit(c));
        
        put_back(c);
        return val;
    }

    bool scan() {
        int c = skip();  // 使用int存储字符
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
