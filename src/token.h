#pragma once
#include <string>

enum class TokenType
{
    STRING,
    INT,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    COLON,
    COMMA,
    EOF_
};

struct Token
{
    Token() = default;
    Token(TokenType type, std::string value, size_t line)
        : type(type), value(value), line(line) {}

    TokenType type{ TokenType::EOF_ };
    std::string value;
    size_t line{ 0 };
};
