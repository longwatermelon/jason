#pragma once
#include "token.h"
#include <string>

class Lexer
{
public:
    Lexer(const std::string &contents);
    ~Lexer();

    void advance();

    std::string collect_str();
    std::string collect_int();

    Token next_tok();

private:
    char m_ch{ 0 };
    size_t m_index{ 0 };

    std::string m_contents;
    size_t m_line{ 1 };
};
