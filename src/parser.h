#pragma once
#include "lexer.h"
#include "node.h"
#include "token.h"

namespace jason::impl
{
    class Parser
    {
    public:
        Parser(const std::string &contents);
        ~Parser();

        void expect(TokenType type);

        std::unique_ptr<Node> parse();
        std::unique_ptr<Node> parse_pair();

        std::unique_ptr<Node> parse_value();
        std::unique_ptr<Node> parse_str();
        std::unique_ptr<Node> parse_int();
        std::unique_ptr<Node> parse_list();
        std::unique_ptr<Node> parse_map();

    private:
        Lexer m_lexer;
        Token m_curr, m_prev;
    };
}
